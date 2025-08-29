
// mmu.c

#include "mmu.h"
#include "cpu.h"

#include <stdio.h>
#include <stdint.h>

void initMMU() {
	memory[0] = 0x16; // for testing
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
        fprintf(stderr, "Failed to open ROM: %s\n", filename);
    }
    
    if (fseek(fp, 0, SEEK_END) != 0) {
		fprintf(stderr, "Failed to seek to end of ROM: %s\n", filename);
		fclose(fp);
	}

    long int file_size = ftell(fp);
    if (file_size < 0) {
        fprintf(stderr, "Failed to get ROM size: %s\n", filename);
        fclose(fp);
    }
    rewind(fp); // go back to beginning of file
    
    printf("Size is %ld bytes...\n", file_size);

    const size_t read_bytes = fread(memory + start, sizeof memory[0], (size_t)file_size, fp);
    
    if (read_bytes != (size_t)file_size) {
        if (feof(fp))
            printf("Error reading %s: unexpected end of file\n", filename);
        else if (ferror(fp))
            printf("Error reading %s", filename);
    }
    
    fclose(fp);
}

void dumpMemoryToFile(const char *filename, uint16_t start, uint16_t end) {
    // if (start >= MEMORY_SIZE || end >= MEMORY_SIZE || start > end) {
//         fprintf(stderr, "dumpMemoryToFile: invalid range 0x%04X-0x%04X\n", start, end);
//         return;
//     }

    FILE *f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Failed to open file for memory dump: %s\n", filename);
        return;
    }
    fwrite(&memory[start], 1, end - start + 1, f);
    fclose(f);
    printf("Memory dumped to %s (0x%04X - 0x%04X)\n", filename, start, end);
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
	printf("\n");

	for (int i = regs.sp - count; i < regs.sp + count; i++) {
		printf("0x%.2X ", memory[i]);
	}
	printf("\n");
}

uint8_t* getByte(uint16_t address) {
	// check memory map here
	return &memory[address];
}

void setByte(uint8_t n, uint16_t address) {
	printf("Writing 0x%02X to 0x%04X\n", n, address);
    if (address <= 0x7FFF) {
        // ROM
        printf("Attempt to write 0x%02X to ROM at 0x%04X ignored\n", n, address);
        return;
    } else if (address >= 0x8000 && address <= 0x9FFF) {
        // VRAM
        memory[address] = n;
		printf("VRAM WRITE Attempt to write 0x%02X at 0x%04X ignored\n", n, address);
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
        printf("Attempt to write to unusable memory 0x%04X ignored\n", address);
    } else if (address >= 0xFF00 && address <= 0xFF7F) {
        // I/O registers
        memory[address] = n;
        // Optionally handle LCDC, STAT, SCY, SCX, etc. here
        printf("Writing 0x%02X to special location at 0x%04X ignored\n", n, address);
    } else if (address >= 0xFF80 && address <= 0xFFFE) {
        // HRAM
        memory[address] = n;
    } else if (address == 0xFFFF) {
        // Interrupt Enable
        memory[address] = n;
    }
}