
// mmu.c

#include "mmu.h"
#include <stdio.h>

void initMMU() {
	memory[0] = 0x16; // for testing
}

void loadMemory(uint8_t *ptr, uint16_t count, uint16_t start) {
	// load 1 byte blocks into memory
	for (uint16_t i = 0; i < count; i++) {
		memory[start + i] = *(ptr + i);
	}
}

uint8_t* getByte(uint16_t address) {
	// check memory map here
	return &memory[address];
}