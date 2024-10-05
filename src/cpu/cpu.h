
// cpu.h

#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <stdint.h>

typedef struct {
	uint8_t a, b, c, d, e, f, h, l;
	uint16_t sp, pc;
} Registers;

// 16-bit macros
#define HL_REG ((uint16_t)(regs.h) << 8) + ((uint16_t)(regs.l))
#define BC_REG ((uint16_t)(regs.b) << 8) + ((uint16_t)(regs.c))
#define DE_REG ((uint16_t)(regs.d) << 8) + ((uint16_t)(regs.e))

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

int execute(uint8_t opcode);

// LOADS
void LD(uint8_t *n, uint8_t *destination);

// ALU
void ADD(uint8_t *n);
void ADD_HL(uint16_t n);
void ADD_SP(int8_t n);
void ADC(uint8_t *n);
void SUB(uint8_t *n);
void SBC(uint8_t *n);

// BITWISE
void AND(uint8_t *n);
void OR(uint8_t *n);
void XOR(uint8_t *n);

void INC(uint8_t *n);
void DEC(uint8_t *n);

void CP(uint8_t *n);

#endif