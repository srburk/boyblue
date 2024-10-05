
// main.c

#include "src/cpu/cpu.h"
#include "src/mmu/mmu.h"

#include <stdio.h>

int main(int argc, char **argv) {
	
	initCPU();
	initMMU();
	
	uint8_t block[] = {
		0xE9, 0x10, // add FA to SP
		0x04, // inc b
	};
	
	loadMemory(&block, sizeof(block), 0x0100);
		
	printRegState();
	
	while (memory[regs.pc] != 0x0000) {
		execute(memory[regs.pc]);
		regs.pc += 1;
	}
	
	printf("Reached end of program...\n");
	
//	execute(0x80);
// 	execute(0x87); // add a, a
// 	execute(0x81); // add a, c
// 	execute(0xB0); // OR a, b
// 	
// 	execute(0x41); // ld c into b
// 	
// 	execute(0x70); // ld B into (HL)
// 	execute(0x6E); // load (HL) into L
// 	
// 	execute(0x09); // add bc to hl
// 	
// 	execute(0x90); // subtract b from a

}