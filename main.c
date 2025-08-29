
// main.c

#include "src/cpu.h"
#include "src/mmu.h"
#include "src/gpu.h"
#include "src/constants.h"

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
	
	initCPU();
	initMMU();
	
	loadFileToMemory("../dmg_boot.bin", 0x0);
	loadFileToMemory("../logo.gb", 0x0104);
	dumpMemoryToFile("initial.bin", 0x0, 0xFFFF);

	setupSDL();
	GPU_t *gpu = create_gpu(renderer);
	
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
	
// 	printf("Reached end of program...\n");
// 	
// 	regs.a = 0b10010001;
// 	SET_FLAG(CARRY, 1);
// 	RRA();
// 	printf("Number: 0x%.2X\n", regs.a);
// 	printRegState();
	
//	execute(0x80);
// 	execute(0x87); // add a, a
// 	execute(0x81); // add a, c
// 	execute(0xB0); // OR a, b
// 	
// 	execute(0x41); // ld c into b
// 	
// 	execute(0x70); // ld B into (HL)
// 	execute(0x6E); // load (HL) into L
// 	
// 	execute(0x09); // add bc to hl
// 	
// 	execute(0x90); // subtract b from a

}