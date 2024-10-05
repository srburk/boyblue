
// mmu.c

#include "mmu.h"
#include "../cpu/cpu.h"
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

// dump stack count each way
void dumpStack(uint8_t count) {
	for (int i = regs.sp - count; i < regs.sp + count; i++) {
		if (i == regs.sp) {
			printf("  v  ");
		} else {
			printf("     ");
		}
	}
	printf("\n");

	for (int i = regs.sp - count; i < regs.sp + count; i++) {
		printf("0x%.2X ", memory[i]);
	}
	printf("\n");
}

uint8_t* getByte(uint16_t address) {
	// check memory map here
	return &memory[address];
}

void setByte(uint8_t n, uint16_t address) {
	// check memory map here
	memory[address] = n;
}