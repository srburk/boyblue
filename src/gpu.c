
// gpu.c

#include "gpu.h"

#include <stdlib.h>
#include <stdio.h>

#include "log.h"
#include "constants.h"

#define TILE_SIZE 16

typedef uint8_t Tile_t[TILE_SIZE];

MMU_t *mmu;

// Test tile
static const Tile_t tile = { 0xFF,0x00, 0x7E,0xFF, 0x85,0x81, 0x89,0x83, 0x93,0x85, 0xA5,0x8B, 0xC9,0x97, 0x7E,0xFF };

static const uint32_t COLOR_PALETTE[4] = {0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000};

struct GPU_t{
	
	uint8_t vram[VRAM_SIZE];
	MMU_t *mmu;
	int cycleCount;
	SDL_Texture *framebuffer;
	SDL_Renderer *renderer;
	
};

GPU_t *create_gpu(SDL_Renderer *renderer, MMU_t *mmu) {
	GPU_t *gpu = malloc(sizeof(GPU_t));
    if (!gpu) return NULL;
    
    gpu->renderer = renderer;
    gpu->framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    SDL_SetTextureScaleMode(gpu->framebuffer, SDL_SCALEMODE_NEAREST);
    
	if (!mmu) {
		log_event(LOG_ERROR, LOG_GPU, "create_gpu() mmu pointer is NULL\n");
		return NULL;
	}
	gpu->mmu = mmu;
	gpu->cycleCount = 0;
    return gpu;
}

void step_gpu(GPU_t *gpu) {
// 	gpu->cycleCount += 8;
	// TODO: FIX TIMING, magic number for now
// 	if (gpu->cycleCount >= 456) {
// 		gpu->cycleCount = 0;
// 		if (memory[FY_REG] < 153) { // keep in VBLANK MODE FOR NOW
// // 			memory[FY_REG] = 0;
// 			memory[FY_REG]++;
// // 			printf("Wrapped FY\n");
// 		}
// 	}
	
// 	memory[FY_REG] = 0x90;
}

void render_tile(GPU_t *gpu) {

	void* pixels;
    int pitch;
    SDL_LockTexture(gpu->framebuffer, NULL, &pixels, &pitch);
	
	uint32_t *buf = (uint32_t *)pixels;
	
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
		buf[i] = COLOR_PALETTE[0];
		
	for (int row = 0; row < (TILE_SIZE / 2); row++) {
		uint8_t lo = tile[row*2];
		uint8_t hi = tile[row*2 + 1];
		for (int col = 0; col < (TILE_SIZE / 2); col++) {
			int hiBit = (hi >> (7 - col)) & 1;
        	int loBit = (lo >> (7 - col)) & 1;
			int colorIndex = ((hiBit << 1) | loBit) & 0x3; // leave only last 2 binary 
			
			uint32_t color = COLOR_PALETTE[colorIndex];
			
			int x = 30 + col;
			int y = 30 + row;
			buf[y * (pitch / 4) + x] = color;
		}
	}

	SDL_UnlockTexture(gpu->framebuffer);
	SDL_FRect dst = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_RenderTexture(gpu->renderer, gpu->framebuffer, NULL, &dst);
}

// void write_vram(GPU_t* gpu, uint8_t n, uint16_t address) {

// 	gpu->vram[address] = n;
// 
// 	log_event(LOG_TRACE, LOG_GPU, "Writing 0x%02X to VRAM at 0x%04X", n, address);
// }