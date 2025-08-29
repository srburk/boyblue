
// mmu.c

#include "mmu.h"
#include "cpu.h"
#include "log.h"

#include <stdio.h>
#include <stdint.h>

struct MMU_t{
	GPU_t *gpu;
};

MMU_t *create_MMU(GPU_t *gpu) {
	if (!gpu) {
		log_event(LOG_ERROR, LOG_MMU, "gpu pointer is NULL");
		return NULL;
	}
	MMU_t *mmu = malloc(sizeof(MMU_t));
	if (!mmu) return NULL;
	mmu->gpu = gpu;
	return mmu;
}

void loadMemory(uint8_t *ptr, uint16_t size, uint16_t start) {
	// load 1 byte blocks into memory
	for (uint16_t i = 0; i < size; i++) {
		memory[start + i] = *(ptr + i);
	}
}

void loadFileToMemory(const char *filename, uint16_t start) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
		log_event(LOG_ERROR, LOG_MMU, "Failed to open ROM: %s", filename);
    }
    
    if (fseek(fp, 0, SEEK_END) != 0) {
		log_event(LOG_ERROR, LOG_MMU, "Failed to seek to end of ROM: %s", filename);
		fclose(fp);
	}

    long int file_size = ftell(fp);
    if (file_size < 0) {
		log_event(LOG_ERROR, LOG_MMU, "Failed to get ROM size: %s", filename);
        fclose(fp);
    }
    rewind(fp); // go back to beginning of file
    
	log_event(LOG_INFO, LOG_MMU, "Size is %ld bytes ", file_size);

    const size_t read_bytes = fread(memory + start, sizeof memory[0], (size_t)file_size, fp);
    
    if (read_bytes != (size_t)file_size) {
        if (feof(fp)) {
			log_event( LOG_ERROR, LOG_MMU, "Unexpected end of file for file %s ", filename);
        }
        else if (ferror(fp)) {
			log_event(LOG_ERROR, LOG_MMU, "Failed to read file %s ", filename);
        }
    }
    
    fclose(fp);
}

void dumpMemoryToFile(const char *filename, uint16_t start, uint16_t end) {
    // if (start >= MEMORY_SIZE || end >= MEMORY_SIZE || start > end) {
//         fprintf(stderr, "dumpMemoryToFile: invalid range 0x%04X-0x%04X", start, end);
//         return;
//     }

    FILE *f = fopen(filename, "wb");
    if (!f) {
		log_event(LOG_ERROR, LOG_MMU, "Failed to open file for memory dump: %s", filename);
        return;
    }
    fwrite(&memory[start], 1, end - start + 1, f);
    fclose(f);
	log_event(LOG_INFO, LOG_MMU, "Memory dumped to %s (0x%04X - 0x%04X)", filename, start, end);
}

// dump stack count each way
void dumpStack(uint8_t count) {
	for (int i = regs.sp - count; i < regs.sp + count; i++) {
		if (i == regs.sp) {
			printf("  v  ");
		} else {
			printf("     ");
		}
	}
	printf("");

	for (int i = regs.sp - count; i < regs.sp + count; i++) {
		printf("0x%.2X ", memory[i]);
	}
	printf("");
}

uint8_t* getByte(uint16_t address) {
	// check memory map here
	return &memory[address];
}

void setByte(MMU_t *mmu, uint8_t n, uint16_t address) {
    if (address <= 0x7FFF) {
        // ROM
        log_event(LOG_ERROR, LOG_MMU, "Attempt to write 0x%02X to ROM at 0x%04X INGORED", n, address);
        return;
    } else if (address >= 0x8000 && address <= 0x9FFF) {
        // VRAM
		write_vram(mmu->gpu, n, address);
    } else if (address >= 0xA000 && address <= 0xBFFF) {
        // External RAM
        memory[address] = n;
    } else if (address >= 0xC000 && address <= 0xDFFF) {
        // Work RAM
        memory[address] = n;
    } else if (address >= 0xE000 && address <= 0xFDFF) {
        // Echo RAM → mirror of 0xC000–0xDDFF
        memory[address] = n;
        memory[address - 0x2000] = n;
    } else if (address >= 0xFE00 && address <= 0xFE9F) {
        // OAM
        memory[address] = n;
    } else if (address >= 0xFEA0 && address <= 0xFEFF) {
        // Unusable memory
		log_event(LOG_ERROR, LOG_MMU, "Attempt to write 0x%02X to unsuable memory at 0x%04X INGORED", n, address);
    } else if (address >= 0xFF00 && address <= 0xFF7F) {
        // I/O registers
        memory[address] = n;
        // Optionally handle LCDC, STAT, SCY, SCX, etc. here
		log_event(LOG_ERROR, LOG_MMU, "Attempt to write 0x%02X to special location at 0x%04X INGORED", n, address);
    } else if (address >= 0xFF80 && address <= 0xFFFE) {
        // HRAM
        memory[address] = n;
    } else if (address == 0xFFFF) {
        // Interrupt Enable
        memory[address] = n;
    }
}