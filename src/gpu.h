// gpu.h

#ifndef GPU_H_INCLUDED
#define GPU_H_INCLUDED

#include <stdint.h>
#include <SDL3/SDL.h>

#define VRAM_START 0x8000
#define VRAM_END 0x9FFF
#define VRAM_SIZE (VRAM_END - VRAM_START + 1)

typedef struct GPU_t GPU_t;

GPU_t *create_gpu(SDL_Renderer *renderer);
void render_tile(GPU_t *gpu);

// VRAM
void write_vram(GPU_t* gpu, uint8_t n, uint16_t address);

#endif