// gpu.h

#ifndef GPU_H_INCLUDED
#define GPU_H_INCLUDED

#include <stdint.h>
#include <SDL3/SDL.h>

typedef struct GPU_t GPU_t;

GPU_t *create_gpu(SDL_Renderer *renderer);
void render_tile(GPU_t *gpu);

// VRAM
void write_vram(GPU_t* gpu, uint8_t n, uint16_t address);

#endif