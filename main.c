
// main.c

#include "src/cpu.h"
#include "src/mmu.h"
#include "src/ppu.h"
#include "src/constants.h"
#include "src/log.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Event event;

int running;

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
// 	set_log_level(LOG_ERROR | LOG_INFO);
// 	set_log_subsystems(LOG_CPU);

	setupSDL();
	MMU_t *mmu = create_MMU();
	PPU_t *ppu = create_ppu(renderer, mmu);
	
	initCPU(mmu);
	
// 	loadFileToMemory("../dmg_boot.bin", 0x0);
// 	loadFileToMemory("../logo.bin", 0x0104);
// 	dumpMemoryToFile("initial.bin", 0x0, 0xFFFF);
	
// 	loadRomFile("cpu_instrs.gb");
		
// 	int cycles = 0;
	
	uint8_t program[] = {
        0x00,       // NOP
       	0x01, 0x43, 0x51, // load 0x5143 into BC (little endian)
       	0x03,			  // inc BC
       	0x02, 			  // load from BC into A
       	0x04,			  // increment B
       	0x05,			  // decrement B
       	0x11, 0x43, 0x51, // load 0x5143 into DE (little endian)
       	0x21, 0x43, 0x51, // load 0x5143 into HL (little endian)
       	0x31, 0x43, 0x51, // load 0x5143 into SP (little endian)
        0xD3, // custom stop code
    };

	loadMemory(program, sizeof(program), 0x0000);

	running = 1;
	int cycles = 0;
	
	uint8_t opcode;
	while (running) {
		opcode = *getByte(regs.pc);
		if (opcode == 0xD3) { // custom stop code
			running = 0;
			break;
		}
		cycles += execute(opcode);
	}
	
	printRegState();
	printf("Finsihed in %i cycles\n", cycles);
	
// 	dumpMemoryToFile("final.bin", 0x0, 0xFFFF);
	
// 	uint32_t lastTime = SDL_GetTicks();
// 	while (1) {
//         SDL_PollEvent(&event);
//         if (event.type == SDL_EVENT_QUIT) {
//             break;
//         }
//         
//         uint32_t currentTime = SDL_GetTicks();
// 		if (currentTime - lastTime >= 16) {
// // 			render_tile(ppu);
// 			render_frame(ppu);
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