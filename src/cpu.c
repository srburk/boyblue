
// cpu.c

#include "cpu.h"
#include "log.h"

#include <string.h>
#include <stdio.h>

static uint16_t *reg16_id_ptr(RegID_t reg_id) {
	switch (reg_id) {
		case REG_AF: return &regs.af;
		case REG_BC: return &regs.bc;
		case REG_DE: return &regs.de;
		case REG_HL: return &regs.hl;
		case REG_SP: return &regs.sp;
		default:
			// anything not a 16 bit register
			log_event(LOG_ERROR, LOG_CPU, "Attempted to get 8 bit register ptr from 16 bit function");
			return NULL;
	}
};

static uint8_t *reg8_id_ptr(RegID_t reg_id) {
	switch (reg_id) {
		case REG_A: return &regs.a;
		case REG_B: return &regs.b;
		case REG_C: return &regs.c;
		case REG_D: return &regs.d;
		case REG_E: return &regs.e;
		case REG_H: return &regs.h;
		case REG_L: return &regs.l;
		case REG_F: return &regs.f;
		default: 
			return NULL;
	}
}

static const char *REG_NAMES[] = {
    [REG_A]  = "A",
    [REG_B]  = "B",
    [REG_C]  = "C",
    [REG_D]  = "D",
    [REG_E]  = "E",
    [REG_H]  = "H",
    [REG_L]  = "L",
    [REG_F]  = "F",
    [REG_AF] = "AF",
    [REG_BC] = "BC",
    [REG_DE] = "DE",
    [REG_HL] = "HL",
    [REG_SP] = "SP",
    [REG_PC] = "PC",
    [NONE] = "NONE"
};

// Temp global MMU reference
MMU_t *mmu;

// TRACER =================================================

static Registers_t *lastRegisterState;

static void captureState() {
	*lastRegisterState = regs;
	
	// 2. get flags
	// 3. get memory changes from a buffer that's triggered from the memory bus (we can intercept mmu requests with a callback or something)
	// 4. compare with some algorithm and output in meaningful format
}

static void outputTrace() { 

	char buf[256];
	int offset = 0;

	#define APPEND_REG_CHANGE(reg) \
		if (lastRegisterState->reg != regs.reg) { \
			offset += snprintf(buf + offset, sizeof(buf) - offset, " " #reg ": 0x%.2X -> 0x%.2X", lastRegisterState->reg, regs.reg); \		
		} \
	
	APPEND_REG_CHANGE(a);
	APPEND_REG_CHANGE(b);
	APPEND_REG_CHANGE(c);
	APPEND_REG_CHANGE(d);
	APPEND_REG_CHANGE(e);
	APPEND_REG_CHANGE(h);
	APPEND_REG_CHANGE(l);
	APPEND_REG_CHANGE(sp);
	
	if (offset > 0) {
    	log_event(LOG_TRACE, LOG_CPU, "\t %s", buf);
	}
    		
}

// ========================================================

void printRegState() {
	printf("----------------------------------- \n");  
	printf("| Register States:                | \n");
	printf("----------------------------------- \n");  
	printf("| A: 0x%.2X       | F: 0x%.2X         | \n", regs.a, regs.f);
	printf("| B: 0x%.2X       | C: 0x%.2X         | \n", regs.b, regs.c);
	printf("| D: 0x%.2X       | E: 0x%.2X         | \n", regs.d, regs.e);
	printf("| H: 0x%.2X       | L: 0x%.2X         | \n", regs.h, regs.l); 
	printf("| - - - - - - - - - - - - - - - - |\n");  
	printf("| SP: 0x%.4X                      | \n", regs.sp);
	printf("| PC: 0x%.4X                      | \n", regs.pc);
	printf("----------------------------------- \n");  
	printf("| Flags (F):                      | \n");
	printf("----------------------------------- \n");  
	printf("| Z: %.1i         | N: %.1i             | \n", GET_FLAG(ZERO), GET_FLAG(SUBTRACT));
	printf("| H: %.1i         | C: %.1i             | \n",  GET_FLAG(HALF), GET_FLAG(CARRY));
	printf("----------------------------------- \n");  
}

void initCPU(MMU_t *mmup) {
	regs.pc = 0x0000;
	regs.sp = 0xFFFE;
	
	lastRegisterState = malloc(sizeof(Registers_t));
	
	if (!mmup) {
		log_event(LOG_ERROR, LOG_CPU, "mmu pointer is NULL\n");
	}
	mmu = mmup;
}

// opcode decoder (returns cycle count)
int execute(uint8_t opcode) {

	Instruction_t *instruction = &core_instructions[opcode];

	// construct operands
	Operands_t operands;
	operands.reg_src = instruction->reg_src;
	operands.reg_dst = instruction->reg_dst;
		
	if (instruction->byte_length == 2) {
		operands.n8 = memory[regs.pc + 1];		
	} else if (instruction->byte_length == 3) {
		operands.n16 = memory[regs.pc + 1] | ((uint16_t)memory[regs.pc + 2] << 8);
	}
	
	log_event(LOG_TRACE, LOG_CPU, "PC = 0x%.2X | Opcode = 0x%.2X | %s", regs.pc, opcode, instruction->name);
	
	instruction->execute(&operands);
	
	regs.pc += instruction->byte_length;
	return instruction->cycles;
}

// instruction primitives:

void instr_NOP(Operands_t *operands) {
	return;
}

// ADD ===================================

void instr_ADD_HL(Operands_t *operands) {
    uint16_t initial = regs.hl;
    uint16_t *reg_src_ptr = reg16_id_ptr(operands->reg_src);
    uint16_t value = *reg_src_ptr;

    uint32_t full = initial + value;
    regs.hl = (uint16_t)full;

    SET_FLAG(SUBTRACT, 0);
    SET_FLAG(HALF, ((initial & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF);
    SET_FLAG(CARRY, full > 0xFFFF);

    log_event(LOG_TRACE, LOG_CPU,
              "\t HL = HL + %s from 0x%.4X -> 0x%.4X",
              REG_NAMES[operands->reg_src], initial, regs.hl);
}

// Add location from src register in memory to A
void instr_ADD_MEM(Operands_t *operands) {
    uint8_t initial = regs.a;
    uint16_t *reg_src_ptr = reg16_id_ptr(operands->reg_src);
    uint8_t value = *getByte(*reg_src_ptr);

    uint16_t full = initial + value;
    regs.a = (uint8_t)full;

    SET_FLAG(ZERO, regs.a == 0);
    SET_FLAG(SUBTRACT, 0);
    SET_FLAG(HALF, ((initial & 0x0F) + (value & 0x0F)) > 0x0F);
    SET_FLAG(CARRY, full > 0xFF);

    log_event(LOG_TRACE, LOG_CPU,
              "\t A = A + (%s) from 0x%.2X -> 0x%.2X",
              REG_NAMES[operands->reg_src], initial, regs.a);
}

// add src register to A (accumulator)
void instr_ADD_n(Operands_t *operands) {
    uint8_t *n_ptr = reg8_id_ptr(operands->reg_src);
    uint8_t initial = regs.a;
    uint8_t value = *n_ptr;

    uint16_t full = initial + value;
    regs.a = (uint8_t)full;

    SET_FLAG(ZERO, regs.a == 0);
    SET_FLAG(SUBTRACT, 0);
    SET_FLAG(HALF, ((initial & 0x0F) + (value & 0x0F)) > 0x0F);
    SET_FLAG(CARRY, full > 0xFF);

    log_event(LOG_TRACE, LOG_CPU,
              "\t A = A + %s from 0x%.2X -> 0x%.2X",
              REG_NAMES[operands->reg_src], initial, regs.a);
}

// Add value from memory pointed to by reg_src into A + CARRY
void instr_ADC_MEM(Operands_t *operands) {
    uint8_t initial = regs.a;
    uint16_t *reg_src_ptr = reg16_id_ptr(operands->reg_src);
    uint8_t value = *getByte(*reg_src_ptr);  // if getByte returns uint8_t

    uint8_t carry_in = GET_FLAG(CARRY);
    uint16_t full = initial + value + carry_in; // 9-bit safe sum
    regs.a = (uint8_t)full;

    SET_FLAG(ZERO, regs.a == 0);
    SET_FLAG(SUBTRACT, 0);
    SET_FLAG(HALF, ((initial & 0x0F) + (value & 0x0F) + carry_in) > 0x0F);
    SET_FLAG(CARRY, full > 0xFF);

    log_event(LOG_TRACE, LOG_CPU,
              "\t A = A + (%s) + CARRY from 0x%.2X -> 0x%.2X",
              REG_NAMES[operands->reg_src], initial, regs.a);
}

// add src register to A (accumulator)
void instr_ADC_n(Operands_t *operands) {
    uint8_t *n_ptr = reg8_id_ptr(operands->reg_src);
    uint8_t initial = regs.a;
    uint8_t value = *n_ptr;
    uint8_t carry_in = GET_FLAG(CARRY);

    uint16_t full = initial + value + carry_in; // 9-bit safe sum
    regs.a = (uint8_t)full;

    SET_FLAG(ZERO, regs.a == 0);
    SET_FLAG(SUBTRACT, 0);
    SET_FLAG(HALF, ((initial & 0x0F) + (value & 0x0F) + carry_in) > 0x0F);
    SET_FLAG(CARRY, full > 0xFF);

    log_event(LOG_TRACE, LOG_CPU,
              "\t A = A + %s + CARRY from 0x%.2X -> 0x%.2X",
              REG_NAMES[operands->reg_src], initial, regs.a);
}

// SUB ===================================

void instr_SUB_n(Operands_t *operands) {
	uint8_t *n_ptr = reg8_id_ptr(operands->reg_src);
	uint8_t initial = regs.a;
	uint8_t value = *n_ptr;
	regs.a -= value;
	
	SET_FLAG(ZERO, regs.a == 0);
	SET_FLAG(SUBTRACT, 1);
	SET_FLAG(HALF, ((initial & 0x0F) < (value & 0x0F)));
	SET_FLAG(CARRY, (initial < value));
	
	log_event(LOG_TRACE, LOG_CPU, "\t A = A - %s from 0x%.2X -> 0x%.2X", REG_NAMES[operands->reg_src], initial, regs.a);
}

// Subtract value at memory location (reg16) from A
void instr_SUB_MEM(Operands_t *operands) {
    uint8_t initial = regs.a;
    uint16_t *reg_src_ptr = reg16_id_ptr(operands->reg_src);
    uint8_t value = *getByte(*reg_src_ptr);

    regs.a = initial - value;

    SET_FLAG(ZERO, regs.a == 0);
    SET_FLAG(SUBTRACT, 1);
    SET_FLAG(HALF, (initial & 0x0F) < (value & 0x0F));
    SET_FLAG(CARRY, initial < value);

    log_event(LOG_TRACE, LOG_CPU,
              "\t A = A - (%s) from 0x%.2X -> 0x%.2X",
              REG_NAMES[operands->reg_src], initial, regs.a);
}

// Subtract register + carry from A
void instr_SBC_n(Operands_t *operands) {
    uint8_t *n_ptr = reg8_id_ptr(operands->reg_src);
    uint8_t initial = regs.a;
    uint8_t carry = GET_FLAG(CARRY);
    uint8_t value = *n_ptr;

    regs.a = initial - value - carry;

    SET_FLAG(ZERO, regs.a == 0);
    SET_FLAG(SUBTRACT, 1);
    SET_FLAG(HALF, (initial & 0x0F) < ((value & 0x0F) + carry));
    SET_FLAG(CARRY, initial < (value + carry));

    log_event(LOG_TRACE, LOG_CPU,
              "\t A = A - %s - CARRY from 0x%.2X -> 0x%.2X",
              REG_NAMES[operands->reg_src], initial, regs.a);
}

// Subtract memory value + carry from A
void instr_SBC_MEM(Operands_t *operands) {
    uint8_t initial = regs.a;
    uint16_t *reg_src_ptr = reg16_id_ptr(operands->reg_src);
    uint8_t value = *getByte(*reg_src_ptr);
    uint8_t carry = GET_FLAG(CARRY);

    regs.a = initial - value - carry;

    SET_FLAG(ZERO, regs.a == 0);
    SET_FLAG(SUBTRACT, 1);
    SET_FLAG(HALF, (initial & 0x0F) < ((value & 0x0F) + carry));
    SET_FLAG(CARRY, initial < (value + carry));

    log_event(LOG_TRACE, LOG_CPU,
              "\t A = A - (%s) - CARRY from 0x%.2X -> 0x%.2X",
              REG_NAMES[operands->reg_src], initial, regs.a);
}

// STR ====================================

// instructions I made up to write to memory

// store n register to nn register memory address
void instr_STR_n(Operands_t *operands) {
	uint8_t *reg_src_ptr = reg8_id_ptr(operands->reg_src);
	uint16_t *reg_dst_ptr = reg16_id_ptr(operands->reg_dst);
	setByte(mmu, *reg_src_ptr, *reg_dst_ptr);
	log_event(LOG_TRACE, LOG_CPU, "\t Loading %s value 0x%.2X into memory location pointed to by %s which is 0x%.4X", REG_NAMES[operands->reg_src], *reg_src_ptr, REG_NAMES[operands->reg_dst], *reg_dst_ptr);
}

// store nn register to u16 memory address
void instr_STR_u16(Operands_t *operands) {
	uint16_t address = operands->n16;
	uint16_t *reg_src_ptr = reg16_id_ptr(operands->reg_src);
	uint8_t lo = (uint8_t)*reg_src_ptr;
	uint8_t hi = *reg_src_ptr >> 8;
	setByte(mmu, lo, address);
	setByte(mmu, hi, address+1);
	log_event(LOG_TRACE, LOG_CPU, "\t Loading %s value 0x%.4X into memory location 0x%.4X and 0x%.4X", REG_NAMES[operands->reg_src], *reg_src_ptr, address, address+1);
}

// LOADS ====================================

// load src register to dst
void instr_LD_n(Operands_t *operands) {
	uint8_t *reg_src_ptr = reg8_id_ptr(operands->reg_src);
	uint8_t *reg_dst_ptr = reg8_id_ptr(operands->reg_dst);
	*reg_dst_ptr = *reg_src_ptr;
	log_event(LOG_TRACE, LOG_CPU, "\t Loaded 0x%.2X from %s to %s, now  0x%.2X", *reg_src_ptr, REG_NAMES[operands->reg_src], REG_NAMES[operands->reg_dst], *reg_dst_ptr);
}

// load memory location pointed to by src reg to dst reg
void instr_LD_MEM(Operands_t *operands) {
	uint16_t *reg_src_ptr = reg16_id_ptr(operands->reg_src);
	uint8_t *reg_dst_ptr = reg8_id_ptr(operands->reg_dst);
	uint8_t value = *getByte((uint16_t)*reg_src_ptr);
	*reg_dst_ptr = value;
	log_event(LOG_TRACE, LOG_CPU, "\t Got 0x%.2X from memory pointed to by reg %s and put in reg %s", value, REG_NAMES[operands->reg_src], REG_NAMES[operands->reg_dst]);
}

void instr_LD_u8(Operands_t *operands) {
	uint8_t *n_ptr = reg8_id_ptr(operands->reg_dst);
	*n_ptr = operands->n8;
	log_event(LOG_TRACE, LOG_CPU, "\t %s ->  0x%.2X", REG_NAMES[operands->reg_dst], *n_ptr);
}

void instr_LD_u16(Operands_t *operands) {
	uint16_t *reg_dst_ptr = reg16_id_ptr(operands->reg_dst);
	*reg_dst_ptr = operands->n16;
	log_event(LOG_TRACE, LOG_CPU, "\t %s ->  0x%.4X", REG_NAMES[operands->reg_dst], *reg_dst_ptr);
}

// INC/DEC ===================================

void instr_INC_n(Operands_t *operands) {
	uint8_t *n_ptr = reg8_id_ptr(operands->reg_dst);
	uint8_t initial = *n_ptr;
	*n_ptr += 1;
	SET_FLAG(ZERO, *n_ptr == 0);
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(HALF, (initial < 0x10 && *n_ptr >= 0x10)); // check for carry from bit 3
	log_event(LOG_TRACE, LOG_CPU, "\t %s -> 0x%.2X", REG_NAMES[operands->reg_dst], *n_ptr);
}

void instr_DEC_n(Operands_t *operands) {
	uint8_t *n_ptr = reg8_id_ptr(operands->reg_dst);
	uint8_t initial = *n_ptr;
	*n_ptr -= 1;
	SET_FLAG(ZERO, *n_ptr == 0);
	SET_FLAG(SUBTRACT, 1);
	SET_FLAG(HALF, (initial & 0x0F) < (*n_ptr & 0x0F)); // check for borrow from bit 4
	log_event(LOG_TRACE, LOG_CPU, "\t %s -> 0x%.2X", REG_NAMES[operands->reg_dst], *n_ptr);
}

// increment register nn (no flags effected)
void instr_INC_nn(Operands_t *operands) {
	uint16_t *nn_ptr = reg16_id_ptr(operands->reg_dst);
	*nn_ptr += 1;
	log_event(LOG_TRACE, LOG_CPU, "\t %s -> 0x%.4", REG_NAMES[operands->reg_dst], *nn_ptr);
}

void instr_DEC_nn(Operands_t *operands) {
	uint16_t *nn_ptr = reg16_id_ptr(operands->reg_dst);
	*nn_ptr -= 1;
	log_event(LOG_TRACE, LOG_CPU, "\t %s -> 0x%.2X", REG_NAMES[operands->reg_dst], *nn_ptr);
}

// SHIFTS/ROTATES ================================

void instr_RLCA(Operands_t *operands) {
	// rotate A left old bit 7 becomes carry flag
	uint8_t initial = regs.a;
	uint8_t msb = regs.a >> 7; // get MSB
	regs.a = regs.a << 1;
	regs.a += msb;
	SET_FLAG(ZERO, regs.a == 0);
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(HALF, 0);
	SET_FLAG(CARRY, msb);
	log_event(LOG_TRACE, LOG_CPU, "\t A: 0x%.2 -> 0x%.2", initial, regs.a);
}

// ADD:

static void ADD_updateFlags(uint8_t *initial_dest) {
	SET_FLAG(ZERO, (regs.a == 0));
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(CARRY, (regs.a < *initial_dest));
	SET_FLAG(HALF, (*initial_dest < 0x10 && regs.a >= 0x10));
}

void ADD(uint8_t *n) {
	// ADD register to A
	uint8_t initial_dest = regs.a;
	regs.a += *n;
	ADD_updateFlags(&initial_dest);
}

void ADD_HL(uint16_t nn) {
	// add n to HL
	uint16_t initial = regs.hl;
// 	uint16_t value = HL_REG;
// 	value += nn;
// 	regs.h = (uint8_t)(value >> 8);
// 	regs.l = (uint8_t)(value);
	regs.hl += nn;
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(CARRY, (regs.hl < initial));
	SET_FLAG(HALF, (initial < 0x0400 && regs.hl > 0x0400));
}

void ADD_SP(int8_t n) {
	// add one (signed) byte immediate n to SP
	uint16_t initial = regs.sp;
	regs.sp += n;
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(ZERO, 0);
	SET_FLAG(CARRY, (regs.sp < initial)); // TODO: Check this
	SET_FLAG(HALF, (initial < 0x0010 && regs.sp >= 0x0010)); // TODO: Check this
}

void ADC(uint8_t *n) {
	// ADD register to A and add carry flag
	uint8_t initial_dest = regs.a;
	regs.a += *n + GET_FLAG(CARRY);
	ADD_updateFlags(&initial_dest);
}

static void SUB_updateFlags(uint8_t *initial, uint8_t *n) {	
	SET_FLAG(ZERO, (regs.a == 0));
	SET_FLAG(SUBTRACT, 1);
	SET_FLAG(CARRY, (*initial < *n));
	SET_FLAG(HALF, ((*initial & 0x0f) < (*n < 0x0f))); //TODO: FIX THIS
}

void SUB(uint8_t *n) {
	// subtract n from A
	uint8_t initial = regs.a;
	regs.a -= *n;
	SUB_updateFlags(&initial, n);
}

void SBC(uint8_t *n) {
	// subtract n from A and also subtract carry
	uint8_t initial = regs.a;
	regs.a -= (*n + GET_FLAG(CARRY));
	SUB_updateFlags(&initial, n);
}

// BITWISE:

static void BITWISE_updateFlags() {
	SET_FLAG(ZERO, (regs.a == 0));
	SET_FLAG(SUBTRACT, 0);
	// HALF IS DIFFERENT SOMETIMES
	SET_FLAG(CARRY, 0);
}

void AND(uint8_t *n) {
	// AND n with reg a
	regs.a &= *n;
	SET_FLAG(HALF, 1);
	BITWISE_updateFlags();
}

void OR(uint8_t *n) {
	// OR n with reg a
	regs.a |= *n;
	SET_FLAG(HALF, 0);
	BITWISE_updateFlags();
}

void XOR(uint8_t *n) {
	// XOR n with reg a
	regs.a ^= *n;
	SET_FLAG(HALF, 0);
	BITWISE_updateFlags();
}

void CP(uint8_t *n) {
	// compare a with n	
	SET_FLAG(ZERO, (regs.a == *n));
	SET_FLAG(SUBTRACT, 1);
	SET_FLAG(HALF, ((regs.a & 0x0F) < (*n < 0x0F))); //TODO: FIX THIS
	SET_FLAG(CARRY, (regs.a < *n));
}

// MISC ALU:

void INC(uint8_t *n) {
	// increment register n
	uint8_t initial = *n;
	*n += 1;
	if (*n == 0) {
		SET_FLAG(ZERO, 1);
	}
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(HALF, (initial < 0x10 && *n >= 0x10));
}

void INC_16(uint16_t *nn) {
	// increment register nn by n
	*nn += 1;
}

void DEC(uint8_t *n) {
	// decrement register n
	uint8_t initial = *n;
	*n -= 1;
	
	SET_FLAG(ZERO, (*n == 0));
	SET_FLAG(SUBTRACT, 1);
	SET_FLAG(HALF, ((initial & 0x0f) < (*n < 0x0f))); //TODO: FIX THIS
}

void DEC_16(uint16_t *nn) {
	*nn -= 1;
}

// LD:

void STR(uint16_t address) {
	// made up instruction that makes more sense to me
	setByte(mmu, regs.a, address);
}

void LD(uint8_t *r1, uint8_t *r2) {
	// ld r2 into r1
	*r1 = *r2;
}

void LDHL(int8_t n) {
	// put SP + n EA into HL
	uint16_t initial = regs.hl;
	regs.hl = regs.sp + n;
	SET_FLAG(ZERO, 0);
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(CARRY, (regs.hl < initial));
	SET_FLAG(HALF, (initial < 0x0400 && regs.hl > 0x0400));
}

// STACK Manipulation

void PUSH(uint16_t nn) {
	regs.sp--;
	setByte(mmu, (uint8_t)(nn >> 8), regs.sp);
	regs.sp--;
	setByte(mmu, (uint8_t)(nn), regs.sp);
// 	dumpStack(7);
}

static uint16_t POP_PRIM() {
	uint16_t lo = *getByte(regs.sp++);
	uint16_t hi = *getByte(regs.sp++);
	uint16_t value = lo | (hi << 8);
	return value;
}

void POP(uint16_t *nn) {
	// not a great system for right now
	// typedef enum { AF = 0, BC = 1, DE = 2, HL = 3 } RegisterPair;
	uint16_t value = POP_PRIM();
// 	uint16_t* reg_ptr = reg_id_ptr(reg_id);
	*nn = value;
// 	dumpStack(7);
}

void CALL(uint16_t nn) {
	// push next instruction address to stack and jump to address nn
	// setByte(mmu, (uint8_t)(regs.pc >> 8), regs.sp);
// 	setByte(mmu, (uint8_t)(regs.pc), regs.sp - 1);
// 	regs.sp -= 2;
	PUSH(regs.pc);
	regs.pc = nn - 1;
}

void CALL_CC(CC cc, uint16_t nn) {
	// nz if zero = 0, z if zero = 1, nc if c = 0, c if c = 1
	// NZ = 0, Z = 1, NC = 2, C = 3
	switch (cc) {
		case NZ: if (GET_FLAG(ZERO)) return; break;
		case Z: if (!GET_FLAG(ZERO)) return; break;
		case NC: if (GET_FLAG(CARRY)) return; break;
		case C: if (!GET_FLAG(CARRY)) return; break;
		default:
		// something is broken
	}
	CALL(nn);
}

void RET() {
	// pop 2 bytes from the stack and jmp to address
	regs.pc = POP_PRIM();
}

void RET_CC(CC cc) {
// nz if zero = 0, z if zero = 1, nc if c = 0, c if c = 1
	// NZ = 0, Z = 1, NC = 2, C = 3
	switch (cc) {
		case NZ: if (GET_FLAG(ZERO)) return; break;
		case Z: if (!GET_FLAG(ZERO)) return; break;
		case NC: if (GET_FLAG(CARRY)) return; break;
		case C: if (!GET_FLAG(CARRY)) return; break;
		default:
		// something is broken
	}
	RET();
}

// execution control

void JP(uint16_t nn) {
	regs.pc = nn;
}

void JP_CC(CC cc, uint16_t nn) {
	switch (cc) {
		case NZ: if (GET_FLAG(ZERO)) return; break;
		case Z: if (!GET_FLAG(ZERO)) return; break;
		case NC: if (GET_FLAG(CARRY)) return; break;
		case C: if (!GET_FLAG(CARRY)) return; break;
		default:
		// something is broken
	}
	JP(nn);
}

void JR(int8_t n) {
	regs.pc += n;
}
void JR_CC(CC cc, int8_t n) {
	switch (cc) {
		case NZ: if (GET_FLAG(ZERO)) return; break;
		case Z: if (!GET_FLAG(ZERO)) return; break;
		case NC: if (GET_FLAG(CARRY)) return; break;
		case C: if (!GET_FLAG(CARRY)) return; break;
	}
	JR(n);
}

// rotates and shifts

static void SHIFT_updateFlags(uint8_t* n) {
	SET_FLAG(ZERO, *n == 0);
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(HALF, 0);
}

void RLC(uint8_t* n) {
	// rotate reg left old bit 7 becomes carry flag 
	uint8_t msb = *n >> 7; // get MSB
	*n = *n << 1;
	*n += msb;
	SET_FLAG(CARRY, msb);
	SHIFT_updateFlags(n);
}

void RLCA() {
	// rotate A left old bit 7 becomes carry flag 
	uint8_t msb = regs.a >> 7; // get MSB
	regs.a = regs.a << 1;
	regs.a += msb;
	SET_FLAG(CARRY, msb);
	SHIFT_updateFlags(&regs.a);
}

void RLA() {
	// rotate A left through carry flag
	uint8_t msb = regs.a >> 7; // get MSB
	regs.a = regs.a << 1;
	regs.a += GET_FLAG(CARRY);
	SET_FLAG(CARRY, msb);
	SHIFT_updateFlags(&regs.a);
}

void RRCA() {
	// rotate A right old bit 0 becomes carry flag 
	uint8_t lsb = regs.a & 0x01; // get LSB
	regs.a = regs.a >> 1;
	regs.a |= lsb << 7;
	SET_FLAG(CARRY, lsb);
	SHIFT_updateFlags(&regs.a);
}

void RRA() {
	// rotate A right through carry flag
	uint8_t lsb = regs.a & 0x01; // get LSB
	regs.a = regs.a >> 1;
	regs.a |= GET_FLAG(CARRY) << 7;
	SET_FLAG(CARRY, lsb);
	SHIFT_updateFlags(&regs.a);
}

void SLA(uint8_t* n) {
	// shift n left into carry, LSB becomes 0
	SET_FLAG(CARRY, ((*n & (1 << 7)) >> 7));
	*n = *n << 1;
	SHIFT_updateFlags(n);
}
void SRA(uint8_t* n) {
	// shift n rights into carry, MSB unaffected
	SET_FLAG(CARRY, *n);
	*n = *n >> 1;
	if (*n & 0x40) {
    	*n |= 0x80;  // set MSB to next highest level bit
	}	 
	SHIFT_updateFlags(n);
}
void SRL(uint8_t* n) {
	// shift n rights into carry, MSB 0
	SET_FLAG(CARRY, *n);
	*n = *n >> 1;
	SHIFT_updateFlags(n);
}

void BIT(uint8_t b, uint8_t n) {
	// test bit b of n, set Z if bit b of n is 0
	SET_FLAG(ZERO, !((n >> b) & 1));
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(HALF, 1);
}






