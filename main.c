
// main.c

#include "src/cpu.h"
#include "src/mmu.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_TEST_CYCLES 30

int main() {
	
	initCPU();
	initMMU();
	
// 	loadRomFile("cpu_instrs.gb");
		
	int cycles = 0;
	
	while (cycles < MAX_TEST_CYCLES) {
		uint8_t opcode = *getByte(regs.pc);
		printf("Opcode: 0x%.2X\n", opcode);
		execute(opcode);
		regs.pc += 1;
		cycles++;
	}
	
// 	printf("Reached end of program...\n");
// 	
// 	regs.a = 0b10010001;
// 	SET_FLAG(CARRY, 1);
// 	RRA();
// 	printf("Number: 0x%.2X\n", regs.a);
// 	printRegState();
	
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