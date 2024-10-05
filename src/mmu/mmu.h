
// mmu.h

#ifndef MMU_H_INCLUDED
#define MMU_H_INCLUDED

#include <stdint.h>

uint8_t memory[0xFFFF];

void initMMU();

uint8_t* getByte(uint16_t address);

#endif