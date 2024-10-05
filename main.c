
// main.c

#include "src/cpu/cpu.h"

int main(int argc, char **argv) {
	
	initCPU();
	
	execute(0xCBFE);
	execute(0x8000);
	execute(0x8700); // add a, a
	execute(0x8100); // add a, c
	execute(0xB000); // OR a, b
	
}