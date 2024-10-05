
// mmu.h

#ifndef MMU_H_INCLUDED
#define MMU_H_INCLUDED

#include <stdint.h>

static uint8_t memory[0xFFFF];

void initMMU();

void loadMemory(uint8_t *ptr, uint16_t size, uint16_t start);
void dumpStack(uint8_t count);

uint8_t* getByte(uint16_t address);
void setByte(uint8_t n, uint16_t address);

#endif