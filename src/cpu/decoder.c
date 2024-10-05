
// decoder.c

#include <stdio.h>

#include "decoder.h"
#include "cpu.h"
#include "../mmu/mmu.h"

int decode(uint8_t opcode) {
		
	if (opcode == 0xCB) { // check leading bits
		printf("CB00\n");
	} else {
		printf("Opcode prefix: 0x%x\n", opcode);
		switch (opcode & 0xF0) { // match higher level
			case 0x00:
				printf("Matched case 0x00\n");
				switch (opcode & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: INC(&regs.b); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: INC(&regs.c); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x10:
				printf("Matched case 0x10\n");
				switch (opcode & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: INC(&regs.d); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: INC(&regs.e); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x20:
				printf("Matched case 0x20\n");
				switch (opcode & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: printf("Sub-case 0x01\n"); break;
					case 0x2: printf("Sub-case 0x02\n"); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: INC(&regs.h); break;
					case 0x5: printf("Sub-case 0x05\n"); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: printf("Sub-case 0x08\n"); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: printf("Sub-case 0x0A\n"); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: INC(&regs.l); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x30:
				printf("Matched case 0x30\n");
				switch (opcode & 0x0F) {
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
					case 0xC: INC(&regs.a); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: printf("Sub-case 0x0E\n"); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x40:
				printf("Matched case 0x40\n");
				switch (opcode & 0x0F) {
					case 0x0: LD(&regs.b, &regs.b); break;
					case 0x1: LD(&regs.b, &regs.c); break;
					case 0x2: LD(&regs.b, &regs.d); break;
					case 0x3: LD(&regs.b, &regs.e); break;
					case 0x4: LD(&regs.b, &regs.h); break;
					case 0x5: LD(&regs.b, &regs.l); break;
					case 0x6: LD(&regs.b, getByte(HL_REG)); break;
					case 0x7: LD(&regs.b, &regs.a); break;
					case 0x8: LD(&regs.c, &regs.b); break;
					case 0x9: LD(&regs.c, &regs.c); break;
					case 0xA: LD(&regs.c, &regs.d); break;
					case 0xB: LD(&regs.c, &regs.e); break;
					case 0xC: LD(&regs.c, &regs.h); break;
					case 0xD: LD(&regs.c, &regs.l); break;
					case 0xE: LD(&regs.c, getByte(HL_REG)); break;
					case 0xF: LD(&regs.c, &regs.a); break;
				}
				break;
			case 0x50:
				printf("Matched case 0x50\n");
				switch (opcode & 0x0F) {
					case 0x0: LD(&regs.d, &regs.b); break;
					case 0x1: LD(&regs.d, &regs.c); break;
					case 0x2: LD(&regs.d, &regs.d); break;
					case 0x3: LD(&regs.d, &regs.e); break;
					case 0x4: LD(&regs.d, &regs.h); break;
					case 0x5: LD(&regs.d, &regs.l); break;
					case 0x6: LD(&regs.d, getByte(HL_REG)); break;
					case 0x7: LD(&regs.d, &regs.a); break;
					case 0x8: LD(&regs.e, &regs.b); break;
					case 0x9: LD(&regs.e, &regs.c); break;
					case 0xA: LD(&regs.e, &regs.d); break;
					case 0xB: LD(&regs.e, &regs.e); break;
					case 0xC: LD(&regs.e, &regs.h); break;
					case 0xD: LD(&regs.e, &regs.l); break;
					case 0xE: LD(&regs.e, getByte(HL_REG)); break;
					case 0xF: LD(&regs.e, &regs.a); break;
				}
				break;
			case 0x60:
				printf("Matched case 0x60\n");
				switch (opcode & 0x0F) {
					case 0x0: LD(&regs.h, &regs.b); break;
					case 0x1: LD(&regs.h, &regs.c); break;
					case 0x2: LD(&regs.h, &regs.d); break;
					case 0x3: LD(&regs.h, &regs.e); break;
					case 0x4: LD(&regs.h, &regs.h); break;
					case 0x5: LD(&regs.h, &regs.l); break;
					case 0x6: LD(&regs.h, getByte(HL_REG)); break;
					case 0x7: LD(&regs.h, &regs.a); break;
					case 0x8: LD(&regs.l, &regs.b); break;
					case 0x9: LD(&regs.l, &regs.c); break;
					case 0xA: LD(&regs.l, &regs.d); break;
					case 0xB: LD(&regs.l, &regs.e); break;
					case 0xC: LD(&regs.l, &regs.h); break;
					case 0xD: LD(&regs.l, &regs.l); break;
					case 0xE: LD(&regs.l, getByte(HL_REG)); break;
					case 0xF: LD(&regs.l, &regs.a); break;
				}
				break;
			case 0x70:
				printf("Matched case 0x70\n");
				switch (opcode & 0x0F) {
					case 0x0: LD(getByte(HL_REG), &regs.b); break;
					case 0x1: LD(getByte(HL_REG), &regs.c); break;
					case 0x2: LD(getByte(HL_REG), &regs.d); break;
					case 0x3: LD(getByte(HL_REG), &regs.e); break;
					case 0x4: LD(getByte(HL_REG), &regs.h); break;
					case 0x5: LD(getByte(HL_REG), &regs.l); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: LD(getByte(HL_REG), &regs.a); break;
					case 0x8: LD(&regs.a, &regs.b); break;
					case 0x9: LD(&regs.a, &regs.c); break;
					case 0xA: LD(&regs.a, &regs.d); break;
					case 0xB: LD(&regs.a, &regs.e); break;
					case 0xC: LD(&regs.a, &regs.h); break;
					case 0xD: LD(&regs.a, &regs.l); break;
					case 0xE: LD(&regs.a, getByte(HL_REG)); break;
					case 0xF: LD(&regs.a, &regs.a); break;
				}
				break;
			case 0x80:
				printf("Matched case 0x80\n");
				switch (opcode & 0x0F) {
					case 0x0: ADD(&regs.b); break;
					case 0x1: ADD(&regs.c); break;
					case 0x2: ADD(&regs.d); break;
					case 0x3: ADD(&regs.e); break;
					case 0x4: ADD(&regs.h); break;
					case 0x5: ADD(&regs.l); break;
					case 0x6: ADD(getByte(HL_REG)); break;
					case 0x7: ADD(&regs.a); break;
					case 0x8: ADC(&regs.b); break;
					case 0x9: ADC(&regs.c); break;
					case 0xA: ADC(&regs.d); break;
					case 0xB: ADC(&regs.e); break;
					case 0xC: ADC(&regs.h); break;
					case 0xD: ADC(&regs.l); break;
					case 0xE: ADC(getByte(HL_REG)); break;
					case 0xF: ADC(&regs.a); break;
				}
				break;
			case 0x90:
				printf("Matched case 0x90\n");
				switch (opcode & 0x0F) {
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
				switch (opcode & 0x0F) {
					case 0x0: AND(&regs.b); break;
					case 0x1: AND(&regs.c); break;
					case 0x2: AND(&regs.d); break;
					case 0x3: AND(&regs.e); break;
					case 0x4: AND(&regs.h); break;
					case 0x5: AND(&regs.l); break;
					case 0x6: AND(getByte(HL_REG)); break;
					case 0x7: AND(&regs.a); break;
					case 0x8: XOR(&regs.b); break;
					case 0x9: XOR(&regs.c); break;
					case 0xA: XOR(&regs.d); break;
					case 0xB: XOR(&regs.e); break;
					case 0xC: XOR(&regs.h); break;
					case 0xD: XOR(&regs.l); break;
					case 0xE: XOR(getByte(HL_REG)); break;
					case 0xF: XOR(&regs.a); break;
				}
				break;
			case 0xB0:
				printf("Matched case 0xB0\n");
				switch (opcode & 0x0F) {
					case 0x0: OR(&regs.b); break;
					case 0x1: OR(&regs.c); break;
					case 0x2: OR(&regs.d); break;
					case 0x3: OR(&regs.e); break;
					case 0x4: OR(&regs.h); break;
					case 0x5: OR(&regs.l); break;
					case 0x6: OR(getByte(HL_REG)); break;
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
				switch (opcode & 0x0F) {
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
				switch (opcode & 0x0F) {
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
				switch (opcode & 0x0F) {
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
				switch (opcode & 0x0F) {
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