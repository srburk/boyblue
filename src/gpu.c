
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
// static const Tile_t tile = { 0xFF,0x00, 0x7E,0xFF, 0x85,0x81, 0x89,0x83, 0x93,0x85, 0xA5,0x8B, 0xC9,0x97, 0x7E,0xFF };
// 
// static const Tile_t r_tile = { 0x3C, 0x00, 0x42, 0x00, 0xB9, 0x00, 0xA5, 0x00, 0xB9, 0x00, 0xA5, 0x00, 0x42, 0x00, 0x3C, 0x00};

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

#define WINDOW_TILE_MAP_0_START 0x9800
#define WINDOW_TILE_MAP_0_END 0x9BFF
#define WINDOW_TILE_MAP_1_START 0x9C00
#define WINDOW_TILE_MAP_1_END 0x9FFF

#define TILE_DATA_0_START 0x8800
#define TILE_DATA_0_END 0x97FF
#define TILE_DATA_1_START 0x8000
#define TILE_DATA_1_END 0x8FFF

static void render_tile(GPU_t *gpu, uint16_t tile_addr, int x, int y, uint32_t *buf, int pitch) {
	for (int row = 0; row < 8; row++) {
// 		uint8_t lo = r_tile[row*2];
// 		uint8_t hi = r_tile[row*2 + 1];
		uint8_t lo = memory[tile_addr + row*2];
		uint8_t hi = memory[tile_addr + row*2 + 1];
		for (int col = 0; col < 8; col++) {
			int hiBit = (hi >> (7 - col)) & 1;
        	int loBit = (lo >> (7 - col)) & 1;
			int colorIndex = ((hiBit << 1) | loBit) & 0x3; // leave only last 2 binary 
			
			uint32_t color = COLOR_PALETTE[colorIndex];
			
			int px = x * 8 + col;
			int py = y * 8 + row;
			
			buf[py * (pitch / 4) + px] = color;
		}
	}
}

void render_frame(GPU_t *gpu) {
	// 1. select tile map
	uint8_t LCDC = memory[LCD_CONTROL_ADDR];
// 	printf("LCDC = %i (decimal) \n", LCDC);
	
	uint16_t tile_map_start = ((LCDC >> 6) & 1) ? WINDOW_TILE_MAP_1_START : WINDOW_TILE_MAP_0_START;
	uint16_t tile_map_end = ((LCDC >> 6) & 1) ? WINDOW_TILE_MAP_1_END : WINDOW_TILE_MAP_0_END;
// 	printf("Selected window tile map: %i with start 0x%.4X\n", (LCDC >> 6) & 1, tile_map_start);
	
	uint16_t tile_data_start = ((LCDC >> 4) & 1) ? TILE_DATA_1_START : TILE_DATA_0_START;
	uint16_t tile_data_end = ((LCDC >> 4) & 1) ? TILE_DATA_1_END : TILE_DATA_0_END;
// 	printf("Selected window tile data: %i with start 0x%.4X\n", (LCDC >> 4) & 1, tile_data_start);

	void* pixels;
    int pitch;
    
	SDL_LockTexture(gpu->framebuffer, NULL, &pixels, &pitch);
	uint32_t *buf = (uint32_t *)pixels;
	
	for (int map_y = 0; map_y < 18; map_y++) {
		for (int map_x = 0; map_x < 20; map_x++) {
// 			printf("X: %i Y: %i\n", map_x, map_y);

			uint16_t addr_in_map = tile_map_start + (map_y * 32) + map_x;
			uint8_t tile_index = memory[addr_in_map]; // index into tile map
			uint16_t tile_addr = tile_data_start + (tile_index * 16);
// 			printf("%i (0x%.2X) ", tile_index, tile_addr);
			render_tile(gpu, tile_addr, map_x, map_y, buf, pitch);
		// 	printf("Tile index: %i | Tile address: 0x%.4X:\n", tile_index, tile_addr);
// 			printBinary(memory[tile_addr]);
// 			printf(" ");
// 			printBinary(memory[tile_addr+1]);
// 			printf("\n");
		}
	}
	printf("\n");
	
	SDL_UnlockTexture(gpu->framebuffer);
	SDL_FRect dst = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_RenderTexture(gpu->renderer, gpu->framebuffer, NULL, &dst);

}

// void write_vram(GPU_t* gpu, uint8_t n, uint16_t address) {

// 	gpu->vram[address] = n;
// 
// 	log_event(LOG_TRACE, LOG_GPU, "Writing 0x%02X to VRAM at 0x%04X", n, address);
// }