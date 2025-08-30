
#include "decoder.h"

Instruction_t core_instructions[0x100] = {
	//         INSTR 			FUNC				SRC			DEST		Bytes	Cycles
	[0x00] = { "NOP", 			instr_NOP, 			NONE, 		NONE, 		1, 		4 },
	[0x01] = { "LD BC, u16", 	instr_LD_u16, 		NONE, 		REG_BC, 	3, 		12 },
	[0x02] = {"LD (BC), A", 	instr_LD_MEM, 		REG_BC,		REG_A, 		1, 		8 },
	[0x03] = {"INC BC",			instr_INC_nn,		NONE,		REG_BC,		1,		8 },
	[0x04] = {"INC B",			instr_INC_n,		NONE,		REG_B,		1,		4 },
	[0x05] = {"DEC B",			instr_DEC_n,		NONE,		REG_B,		1,		4 },
	[0x11] = { "LD DE, u16", 	instr_LD_u16, 		NONE,		REG_DE, 	3, 		12 },
	[0x12] = {"LD (DE), A", 	instr_LD_MEM, 		REG_DE,		REG_A, 		1, 		8 },
	[0x13] = {"INC DE",			instr_INC_nn,		NONE,		REG_DE,		1,		8 },
	[0x14] = {"INC D",			instr_INC_n,		NONE,		REG_D,		1,		4 },
	[0x15] = {"DEC D",			instr_DEC_n,		NONE,		REG_D,		1,		4 },
	[0x21] = { "LD HL, u16", 	instr_LD_u16, 		NONE,		REG_HL, 	3, 		12 },
	[0x23] = {"INC HL",			instr_INC_nn,		NONE,		REG_HL,		1,		8 },
	[0x24] = {"INC H",			instr_INC_n,		NONE,		REG_H,		1,		4 },
	[0x25] = {"DEC H",			instr_DEC_n,		NONE,		REG_H,		1,		4 },
	[0x31] = { "LD SP, u16", 	instr_LD_u16, 		NONE,		REG_SP, 	3, 		12 },
	[0x33] = {"INC SP",			instr_INC_nn,		NONE,		REG_SP,		1,		8 },
};