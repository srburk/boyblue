
// mmu.c

#include "mmu.h"

void initMMU() {
	memory[0] = 0x16; // for testing
}

uint8_t* getByte(uint16_t address) {
	// check memory map here
	return &memory[address];
}