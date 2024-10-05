
// main.c

#include "src/cpu/cpu.h"
#include "src/mmu/mmu.h"

int main(int argc, char **argv) {
	
	initCPU();
	initMMU();
	
	execute(0x80);
	execute(0x87); // add a, a
	execute(0x81); // add a, c
	execute(0xB0); // OR a, b
	
	execute(0x41); // ld c into b
	
	execute(0x70); // ld B into HL
	execute(0x6E); // load HL into L

}