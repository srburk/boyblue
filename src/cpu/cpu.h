
// cpu.h

#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <stdint.h> 

typedef struct {
	uint8_t a, b, c, d, e, f, h, l;
	uint16_t sp, pc;
} Registers;

typedef enum {
	AF = 0, BC = 1, DE = 2, HL = 3
} VirtualRegister;

typedef enum { // nz if zero = 0, z if zero = 1, nc if c = 0, c if c = 1
	NZ = 0, Z = 1, NC = 2, C = 3
} CC;

// 16-bit macros
#define AF_REG ((uint16_t)(regs.a) << 8) + ((uint16_t)(regs.f))
#define HL_REG ((uint16_t)(regs.h) << 8) + ((uint16_t)(regs.l))
#define BC_REG ((uint16_t)(regs.b) << 8) + ((uint16_t)(regs.c))
#define DE_REG ((uint16_t)(regs.d) << 8) + ((uint16_t)(regs.e))

#define SET_AF(value)  {           \
	uint16_t temp = value;         \
 	regs.a = (uint8_t)(temp >> 8); \
	regs.f = (uint8_t)(temp);      \
	}
#define SET_HL(value)  {           \
	uint16_t temp = value;         \
 	regs.h = (uint8_t)(temp >> 8); \
	regs.l = (uint8_t)(temp);      \
	}
#define SET_BC(value) {            \
	uint16_t temp = value;         \
 	regs.b = (uint8_t)(temp >> 8); \
	regs.c = (uint8_t)(temp);      \
	}
#define SET_DE(value)  {           \
	uint16_t temp = value;         \
 	regs.d = (uint8_t)(temp >> 8); \
	regs.e = (uint8_t)(temp);      \
	}

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
void STR(uint16_t address);
void LD(uint8_t *n, uint8_t *destination);
void LDHL(int8_t n);

// ALU
void ADD(uint8_t *n);
void ADD_HL(uint16_t nn);
void ADD_SP(int8_t n);
void ADC(uint8_t *n);
void SUB(uint8_t *n);
void SBC(uint8_t *n);

// BITWISE
void AND(uint8_t *n);
void OR(uint8_t *n);
void XOR(uint8_t *n);

void INC(uint8_t *n);

void INC_BC(int8_t n);
void INC_DE(int8_t n);
void INC_HL(int8_t n);
void INC_SP(int8_t n);

void DEC(uint8_t *n);

void CP(uint8_t *n);

// stack manipulation
void PUSH(uint16_t nn);
void POP(VirtualRegister reg);
void CALL(uint16_t nn);
void CALL_CC(CC cc, uint16_t nn);
void RST(uint8_t n);
void RET();
void RET_CC(CC cc);

// execution control
void JP(uint16_t nn);
void JP_CC(CC cc, uint16_t nn);
void JR(int8_t n);
void JR_CC(CC cc, int8_t n);

// load immediate 16 bit values - These can be implemented in one step in decoder
// void LD_BC(uint16_t n);
// void LD_DE(uint16_t n);
// void LD_HL(uint16_t n);
// void LD_SP(uint16_t n);

#endif