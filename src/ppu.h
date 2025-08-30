// ppu.h

#ifndef PPU_H_INCLUDED
#define PPU_H_INCLUDED

#include <stdint.h>
#include <SDL3/SDL.h>

#include "mmu.h"

extern MMU_t *mmu;
extern uint8_t memory[0xFFFF];

typedef struct PPU_t PPU_t;

PPU_t *create_ppu(SDL_Renderer *renderer, MMU_t *mmu);
// void render_tile(PPU_t *ppu, uint16_t tile_addr, int x, int y);
void render_frame(PPU_t *ppu);
void step_ppu(PPU_t *ppu);

// VRAM
// void write_vram(PPU_t* ppu, uint8_t n, uint16_t address);

#endif