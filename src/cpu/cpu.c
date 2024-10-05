
// cpu.c

#include "cpu.h"
#include "decoder.h"

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

// LD:
void LD(uint8_t *r1, uint8_t *r2) {
	// ld r2 into r1
	*r1 = *r2;
}

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

void ADD_HL(uint16_t n) {
	// add n to HL
	uint16_t initial = HL_REG;
	uint16_t value = HL_REG;
	value += n;
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


