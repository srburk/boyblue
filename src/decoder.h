#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include <stdint.h> 

#include "constants.h"

typedef struct {
	union {
		uint8_t n8;
		uint16_t n16;
	};
	RegID_t reg_src;
	RegID_t reg_dst;
} Operands_t;

#include "cpu.h"

typedef struct {
    const char *name;
    void (*execute)(Operands_t *operands);
    RegID_t reg_src;
    RegID_t reg_dst;
    uint8_t byte_length;
    uint8_t cycles;
} Instruction_t;


extern Instruction_t core_instructions[0x100];

#endif