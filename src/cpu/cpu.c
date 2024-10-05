
// cpu.c

#include "cpu.h"
#include "decoder.h"
#include "../mmu/mmu.h"

#include <stdio.h>

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

void initCPU() {
	regs.pc = 0x0100;
	regs.sp = 0xFFFE;
}

// opcode decoder
int execute(uint8_t opcode) {

	printf("Opcode: 0x%x \n", opcode);
	decode(opcode);
	printRegState();
}

// instruction primitives:

// ADD:

static void ADD_updateFlags(uint8_t *initial_dest) {
	if (regs.a == 0) {
		SET_FLAG(ZERO, 1);
	}
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
	uint16_t initial = HL_REG;
	uint16_t value = HL_REG;
	value += nn;
	regs.h = (uint8_t)(value >> 8);
	regs.l = (uint8_t)(value);
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(CARRY, (value < initial));
	SET_FLAG(HALF, (initial < 0x0400 && value > 0x0400));
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
	if (regs.a == 0) {
		SET_FLAG(ZERO, 1);
	}
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
	if (regs.a == 0) {
		SET_FLAG(ZERO, 1);
	}
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
	if (regs.a == *n) {
		SET_FLAG(ZERO, 1);
	}
	SET_FLAG(SUBTRACT, 1);
	SET_FLAG(HALF, ((regs.a & 0x0f) < (*n < 0x0f))); //TODO: FIX THIS
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

// These also function as decrements since no flags are impacted
void INC_BC(int8_t n) {
	uint16_t value = BC_REG + n;
	SET_BC(value);
}
void INC_DE(int8_t n) {
	uint16_t value = DE_REG + n;
	SET_DE(value);
}
void INC_HL(int8_t n) {
	uint16_t value = HL_REG + n;
	SET_HL(value);
}
void INC_SP(int8_t n) {
	regs.sp += n;
}

void DEC(uint8_t *n) {
	// decrement register n
	uint8_t initial = *n;
	*n -= 1;
	if (*n == 0) {
		SET_FLAG(ZERO, 1);
	}
	SET_FLAG(SUBTRACT, 1);
	SET_FLAG(HALF, ((initial & 0x0f) < (*n < 0x0f))); //TODO: FIX THIS
}

// LD:
void LD(uint8_t *r1, uint8_t *r2) {
	// ld r2 into r1
	*r1 = *r2;
}

void LDHL(int8_t n) {
	// put SP + n EA into HL
	uint16_t initial = HL_REG;
	SET_HL(regs.sp + n);
	SET_FLAG(ZERO, 0);
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(CARRY, (HL_REG < initial));
	SET_FLAG(HALF, (initial < 0x0400 && HL_REG > 0x0400));
}

// STACK Manipulation

void PUSH(uint16_t nn) {
	setByte((uint8_t)(nn >> 8), regs.sp--);
	setByte((uint8_t)(nn), regs.sp--);
	dumpStack(7);
}

static uint16_t POP_PRIM() {
	uint16_t value;
	value = (uint16_t)(*getByte(regs.sp++)) << 8;
	value |= *getByte(regs.sp++);
	return value;
}

void POP(VirtualRegister reg) {
	// not a great system for right now
	// typedef enum { AF = 0, BC = 1, DE = 2, HL = 3 } VirtualRegister;
	uint16_t value = POP_PRIM();
		
	switch(reg) {
		case AF: SET_AF(value); break;
		case BC: SET_BC(value); break;
		case DE: SET_DE(value); break;
		case HL: SET_HL(value); break;
	}
	dumpStack(7);
}

void CALL(uint16_t nn) {
	// push next instruction address to stack and jump to address nn
	printf("Saving 0x%.4X to the stack in chunks: 0x%.2X 0x%.2X\n", regs.pc, (uint8_t)(regs.pc >> 8), (uint8_t)(regs.pc));
	setByte((uint8_t)(regs.pc >> 8), regs.sp);
	setByte((uint8_t)(regs.pc), regs.sp - 1);
	regs.sp -= 2;
	regs.pc = nn;
	dumpStack(7);
}

void CALL_CC(CC cc, uint16_t nn) {
	// nz if zero = 0, z if zero = 1, nc if c = 0, c if c = 1
	// NZ = 0, Z = 1, NC = 2, C = 3
	switch (cc) {
		case NZ: if (GET_FLAG(ZERO)) return; break;
		case Z: if (!GET_FLAG(ZERO)) return; break;
		case NC: if (GET_FLAG(CARRY)) return; break;
		case C: if (!GET_FLAG(CARRY)) return; break;
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


