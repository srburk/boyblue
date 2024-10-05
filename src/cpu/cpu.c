
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
	regs.b = 10;
	regs.c = 250;
	
	regs.pc = 0x0100;
	regs.sp = 0xFFFE;
}

// opcode decoder
int execute(uint16_t opcode) {

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

static void ADD_updateFlags(uint8_t *result, uint8_t *initial_dest) {
	if (*result == 0) {
		SET_FLAG(ZERO, 1);
	}
	SET_FLAG(SUBTRACT, 0);
	SET_FLAG(CARRY, (*result < *initial_dest));
	SET_FLAG(HALF, (*initial_dest < 0x10 && *result >= 0x10));
}

void ADD(uint8_t *destination, uint8_t *n) {
	// ADD register to register
	uint8_t initial_dest = *destination;
	*destination += *n;
	ADD_updateFlags(destination, &initial_dest);
}

void ADC(uint8_t *destination, uint8_t *n) {
	// ADD register to register and add carry flag
	uint8_t initial_dest = *destination;
	*destination += *n + GET_FLAG(CARRY);
	ADD_updateFlags(destination, &initial_dest);
}

// BITWISE:

void BITWISE_updateFlags() {
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

// Execution Flow:

void JP(uint16_t *n) {
	regs.pc = *n;
}


