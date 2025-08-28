
// mmu.h

#ifndef MMU_H_INCLUDED
#define MMU_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>

static uint8_t memory[0xFFFF];

void initMMU();

void loadMemory(uint8_t *ptr, uint16_t count, uint16_t start);
void loadRomFile(const char *filename);

void dumpMemoryToFile(const char *filename, uint16_t start, uint16_t end);
void dumpStack(uint8_t count);

uint8_t* getByte(uint16_t address);
void setByte(uint8_t n, uint16_t address);

#endif