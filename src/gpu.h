// gpu.h

#ifndef GPU_H_INCLUDED
#define GPU_H_INCLUDED

#include <stdint.h>
#include <SDL3/SDL.h>

#include "mmu.h"

extern MMU_t *mmu;
extern uint8_t memory[0xFFFF];

typedef struct GPU_t GPU_t;

GPU_t *create_gpu(SDL_Renderer *renderer, MMU_t *mmu);
// void render_tile(GPU_t *gpu, uint16_t tile_addr, int x, int y);
void render_frame(GPU_t *gpu);
void step_gpu(GPU_t *gpu);

// VRAM
// void write_vram(GPU_t* gpu, uint8_t n, uint16_t address);

#endif