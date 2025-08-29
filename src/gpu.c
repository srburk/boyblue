
// gpu.c

#include "gpu.h"

#include <stdlib.h>

struct GPU_t{
	
	uint8_t vram[VRAM_SIZE];
	
};

GPU_t *create_gpu(void) {
	GPU_t *gpu = malloc(sizeof(GPU_t));
    if (!gpu) return NULL;
    return gpu;
}

void write_vram(GPU_t* gpu, uint8_t n, uint16_t address) {
	gpu->vram[address] = n;
	
	if (address >= 0x1800) { return; } // return if not tile set data
	
	const uint16_t even_address_first_byte = 0xFFFE;
	
	uint16_t normalized_address = address & even_address_first_byte;
}