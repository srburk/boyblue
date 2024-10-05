
// cpu.h

#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <stdint.h>

typedef struct {
	uint8_t a, b, c, d, e, f, h, l;
	uint16_t sp, pc;
} Registers;

// FLAG MACROS
#define GET_FLAG(x) ((regs.f & (1 << x)) >> x)
#define SET_FLAG(x, n) (n) ? (regs.f |= (1 << (x))) : (regs.f &= ~(1 << (x))) // set flag x in F to n
#define CARRY 4
#define ZERO 7
#define HALF 5
#define SUBTRACT 6

Registers regs;

void initCPU();

void printRegState();

int execute(uint16_t opcode);

// LOADS
void LD(uint8_t *n, uint8_t *destination);

// ALU
void ADD(uint8_t *destination, uint8_t *n);
void ADC(uint8_t *destination, uint8_t *n);

// BITWISE
void AND(uint8_t *n);
void OR(uint8_t *n);
void XOR(uint8_t *n);

void INC(uint8_t *n);

// EXECUTION
void JP(uint16_t *n);

#endif