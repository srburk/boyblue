
// mmu.h

#ifndef MMU_H_INCLUDED
#define MMU_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>

typedef struct MMU_t MMU_t;

MMU_t *create_MMU();

static uint8_t memory[0xFFFF];

void loadMemory(uint8_t *ptr, uint16_t count, uint16_t start);
void loadFileToMemory(const char *filename, uint16_t start);

void dumpMemoryToFile(const char *filename, uint16_t start, uint16_t end);
void dumpStack(uint8_t count);

uint8_t* getByte(uint16_t address);
void setByte(MMU_t *mmu, uint8_t n, uint16_t address);

#endif