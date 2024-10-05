
// main.c

#include "src/cpu/cpu.h"
#include "src/mmu/mmu.h"

#include <stdio.h>

int main(int argc, char **argv) {
	
	initCPU();
	initMMU();
	
	uint8_t block[] = {
		0x04, // inc b
		0x33, // inc sp
		0x3B, // decrement sp
		0x23, // inc hl
		0x08, 0x56, 0xf4, // set sp to nn
		0xf8, 0x05, // put sp + n into hl
// 		0xf9, // put hl into sp
// 		0xf5, // push af to stack
  		0xe5, // push hl to stack
 		0xe1, // pop stack to hl
		0xcd, 0x01, 0x10, // if z is 0, call address 0x0120 and push current instruction to stack
	};
	
	loadMemory(&block, sizeof(block), 0x0100);
		
	printRegState();
	
	while (*getByte(regs.pc) != 0x0000) {
		execute(*getByte(regs.pc));
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