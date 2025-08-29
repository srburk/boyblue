
// main.c

#include "src/cpu.h"
#include "src/mmu.h"
#include "src/gpu.h"
#include "src/constants.h"
#include "src/log.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

#define MAX_TEST_CYCLES 100000

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Event event;

void setupSDL() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer("BoyBlue", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    }
}

int main() {	

	set_log_level(LOG_ERROR | LOG_TRACE | LOG_INFO);

	setupSDL();
	GPU_t *gpu = create_gpu(renderer);
	MMU_t *mmu = create_MMU(gpu);
	
	initCPU(mmu);
	
	loadFileToMemory("../dmg_boot.bin", 0x0);
	loadFileToMemory("../logo.gb", 0x0104);
	dumpMemoryToFile("initial.bin", 0x0, 0xFFFF);
	
// 	loadRomFile("cpu_instrs.gb");
		
	int cycles = 0;
	while (cycles < MAX_TEST_CYCLES) {
		uint8_t opcode = *getByte(regs.pc);
		execute(opcode);
		regs.pc += 1;
		cycles++;
	}
	
	dumpMemoryToFile("final.bin", 0x0, 0xFFFF);
	
	// uint32_t lastTime = SDL_GetTicks();
// 	while (1) {
//         SDL_PollEvent(&event);
//         if (event.type == SDL_EVENT_QUIT) {
//             break;
//         }
//         
//         uint32_t currentTime = SDL_GetTicks();
// 		if (currentTime - lastTime >= 16) {
// 			render_tile(gpu);
//         	SDL_RenderPresent(renderer);
// 			lastTime = currentTime;
// 		} else {
// 			SDL_Delay(1); 
// 		}
//     }
// 
//     SDL_DestroyTexture(texture);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
// 
//     SDL_Quit();
	
	return 0;
}