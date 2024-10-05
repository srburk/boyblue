
// decoder.c

#include <stdio.h>

#include "decoder.h"
#include "cpu.h"

int decode(uint16_t opcode) {

	uint8_t opcode_prefix = opcode >> 8;
		
	if (opcode_prefix == 0xCB) { // check leading bits
		printf("CB00\n");
	} else {
		printf("Opcode prefix: 0x%x\n", opcode_prefix);
		switch (opcode_prefix & 0xF0) { // match higher level
			case 0x00:
				printf("Matched case 0x00\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x10:
				printf("Matched case 0x10\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x20:
				printf("Matched case 0x20\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x30:
				printf("Matched case 0x30\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x40:
				printf("Matched case 0x40\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x50:
				printf("Matched case 0x50\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x60:
				printf("Matched case 0x60\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x70:
				printf("Matched case 0x70\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x80:
				printf("Matched case 0x80\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: ADD(&regs.a, &regs.b); break;
					case 0x1: ADD(&regs.a, &regs.c); break;
					case 0x2: ADD(&regs.a, &regs.d); break;
					case 0x3: ADD(&regs.a, &regs.e); break;
					case 0x4: ADD(&regs.a, &regs.h); break;
					case 0x5: ADD(&regs.a, &regs.l); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: ADD(&regs.a, &regs.a); break;
					case 0x8: ADC(&regs.a, &regs.b); break;
					case 0x9: ADC(&regs.a, &regs.c); break;
					case 0xA: ADC(&regs.a, &regs.d); break;
					case 0xB: ADC(&regs.a, &regs.e); break;
					case 0xC: ADC(&regs.a, &regs.h); break;
					case 0xD: ADC(&regs.a, &regs.l); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: ADC(&regs.a, &regs.a); break;
				}
				break;
			case 0x90:
				printf("Matched case 0x90\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xA0:
				printf("Matched case 0xA0\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: AND(&regs.b); break;
					case 0x1: AND(&regs.c); break;
					case 0x2: AND(&regs.d); break;
					case 0x3: AND(&regs.e); break;
					case 0x4: AND(&regs.h); break;
					case 0x5: AND(&regs.l); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: AND(&regs.a); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xB0:
				printf("Matched case 0xB0\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: OR(&regs.b); break;
					case 0x1: OR(&regs.c); break;
					case 0x2: OR(&regs.d); break;
					case 0x3: OR(&regs.e); break;
					case 0x4: OR(&regs.h); break;
					case 0x5: OR(&regs.l); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: OR(&regs.a); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xC0:
				printf("Matched case 0xC0\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xD0:
				printf("Matched case 0xD0\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xE0:
				printf("Matched case 0xE0\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xF0:
				printf("Matched case 0xF0\n");
				switch (opcode_prefix & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			default:
				printf("No match found\n");
				break;
		}
	}
}