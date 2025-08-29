
// decoder.c

#include <stdio.h>

#include "decoder.h"
#include "cpu.h"
#include "mmu.h"

uint8_t getNextOperand() {
	// get next operand 
	// TODO: Increment PC?
	regs.pc += 1;
// 	printf("Next requested operand is: 0x%.2X \n", *getByte(regs.pc));
	return *getByte(regs.pc);
}

uint16_t getNextLargeOperand() {
	uint16_t value;
	regs.pc += 1;
    uint8_t low = *getByte(regs.pc);
    regs.pc += 1;
    uint8_t high = *getByte(regs.pc);
    value = low | (high << 8);  
	printf("Next requested operand is: 0x%.4X at addresses 0x%.2X and 0x%.2X \n", value, regs.pc - 2, regs.pc - 1);
	return value;
}

static uint8_t immediate8; // used for storing 8-bit immediate values

int decode(uint8_t opcode) {
		
	if (opcode == 0xCB) { // check leading bits
		regs.pc++;
		opcode = *getByte(regs.pc);
		
		printf("Opcode: 0xCB%x \n", opcode);
		
		switch (opcode & 0xF0) {
			case 0x00:
				switch (opcode & 0x0F) { // match higher level 0x00
					case 0x0: RLC(&regs.b); break;
					case 0x1: RLC(&regs.c); break;
					case 0x2: RLC(&regs.d); break;
					case 0x3: RLC(&regs.e); break;
					case 0x4: RLC(&regs.h); break;
					case 0x5: RLC(&regs.l); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB06\n"); break;
					case 0x7: RLC(&regs.a); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB08\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB09\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB0A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB0B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB0C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB0D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB0E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB0F\n"); break;
				}
			break;
			case 0x10:
				switch (opcode & 0x0F) { // match higher level 0x10
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB10\n"); break;
					case 0x1: RLC(&regs.c); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB12\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB13\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB14\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB15\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB16\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB17\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB18\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB19\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB1A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB1B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB1C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB1D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB1E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB1F\n"); break;
				}
			break;
			case 0x20:
				switch (opcode & 0x0F) { // match higher level 0x20
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB20\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB21\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB22\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB23\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB24\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB25\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB26\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB27\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB28\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB29\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB2A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB2B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB2C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB2D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB2E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB2F\n"); break;
				}
				break;
			case 0x30:
				switch (opcode & 0x0F) { // match higher level 0x30
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB30\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB31\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB32\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB33\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB34\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB35\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB36\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB37\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB38\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB39\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB3A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB3B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB3C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB3D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB3E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB3F\n"); break;
				}
				break;
			case 0x40:
				switch (opcode & 0x0F) { // match higher level 0x40
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB40\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB41\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB42\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB43\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB44\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB45\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB46\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB47\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB48\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB49\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB4A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB4B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB4C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB4D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB4E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB4F\n"); break;
				}
				break;
			case 0x50:
				switch (opcode & 0x0F) { // match higher level 0x50
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB50\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB51\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB52\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB53\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB54\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB55\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB56\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB57\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB58\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB59\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB5A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB5B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB5C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB5D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB5E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB5F\n"); break;
			}
			case 0x60:
				switch (opcode & 0x0F) { // match higher level 0x60
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB60\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB61\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB62\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB63\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB64\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB65\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB66\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB67\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB68\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB69\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB6A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB6B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB6C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB6D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB6E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB6F\n"); break;
				}
				break;
			case 0x70:
				switch (opcode & 0x0F) { // match higher level 0x70
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB70\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB71\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB72\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB73\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB74\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB75\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB76\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB77\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB78\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB79\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB7A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB7B\n"); break;
					case 0xC: BIT(7, regs.h); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB7D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB7E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB7F\n"); break;
				}
				break;
			case 0x80:
				switch (opcode & 0x0F) { // match higher level 0x80
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB80\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB81\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB82\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB83\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB84\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB85\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB86\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB87\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB88\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB89\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB8A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB8B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB8C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB8D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB8E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB8F\n"); break;
				}
				break;
			case 0x90:
				switch (opcode & 0x0F) { // match higher level 0x90
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB90\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB91\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB92\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB93\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB94\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB95\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB96\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB97\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB98\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB99\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB9A\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB9B\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB9C\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB9D\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB9E\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCB9F\n"); break;
				}
				break;
			case 0xA0:
				switch (opcode & 0x0F) { // match higher level 0xA0
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA0\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA1\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA2\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA3\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA4\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA5\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA6\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA7\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA8\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBA9\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBAA\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBAB\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBAC\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBAD\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBAE\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBAF\n"); break;
				}
				break;
			case 0xB0:
				switch (opcode & 0x0F) { // match higher level 0xB0
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB0\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB1\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB2\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB3\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB4\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB5\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB6\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB7\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB8\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBB9\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBBA\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBBB\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBBC\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBBD\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBBE\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBBF\n"); break;
				}
				break;
			case 0xC0:
				switch (opcode & 0x0F) { // match higher level 0xC0
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC0\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC1\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC2\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC3\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC4\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC5\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC6\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC7\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC8\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBC9\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBCA\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBCB\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBCC\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBCD\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBCE\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBCF\n"); break;
				}
				break;
			case 0xD0:
				switch (opcode & 0x0F) { // match higher level 0xD0
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD0\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD1\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD2\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD3\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD4\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD5\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD6\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD7\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD8\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBD9\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBDA\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBDB\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBDC\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBDD\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBDE\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBDF\n"); break;
				}
				break;
			case 0xE0:
				switch (opcode & 0x0F) { // match higher level 0xE0
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE0\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE1\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE2\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE3\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE4\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE5\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE6\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE7\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE8\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBE9\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBEA\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBEB\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBEC\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBED\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBEE\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBEF\n"); break;
				}
				break;
			case 0xF0:
				switch (opcode & 0x0F) { // match higher level 0xF0
					case 0x0: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF0\n"); break;
					case 0x1: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF1\n"); break;
					case 0x2: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF2\n"); break;
					case 0x3: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF3\n"); break;
					case 0x4: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF4\n"); break;
					case 0x5: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF5\n"); break;
					case 0x6: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF6\n"); break;
					case 0x7: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF7\n"); break;
					case 0x8: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF8\n"); break;
					case 0x9: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBF9\n"); break;
					case 0xA: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBFA\n"); break;
					case 0xB: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBFB\n"); break;
					case 0xC: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBFC\n"); break;
					case 0xD: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBFD\n"); break;
					case 0xE: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBFE\n"); break;
					case 0xF: fprintf(stderr, "UNIMPLEMENTED: Opcode 0xCBFF\n"); break;
				}
				break;
			}
	} else {
	
		printf("Opcode: 0x%.2X \n", opcode);
	
		switch (opcode & 0xF0) { // match higher level
			case 0x00:
				switch (opcode & 0x0F) {
					case 0x0: printf("NOP\n"); break;
					case 0x1: regs.bc = getNextLargeOperand(); break;
					case 0x2: STR(regs.bc); break;
					case 0x3: INC_16(&regs.bc); break;
					case 0x4: INC(&regs.b); break;
					case 0x5: DEC(&regs.b); break;
					case 0x6: immediate8 = getNextOperand(); LD(&regs.b, &immediate8); break;
					case 0x7: RLC(&regs.a); break;
					case 0x8: regs.sp = getNextLargeOperand(); break;
					case 0x9: ADD_HL(regs.bc); break;
					case 0xA: LD(&regs.a, getByte(regs.bc)); break;
					case 0xB: DEC_16(&regs.bc); break;
					case 0xC: INC(&regs.c); break;
					case 0xD: DEC(&regs.c); break;
					case 0xE: immediate8 = getNextOperand(); LD(&regs.c, &immediate8); break;
					case 0xF: RRCA(); break;
				}
				break;
			case 0x10:
				switch (opcode & 0x0F) {
					case 0x0: printf("Sub-case 0x10\n"); break;
					case 0x1: regs.de = getNextLargeOperand(); break;
					case 0x2: STR(regs.de); break;
					case 0x3: INC_16(&regs.de); break;
					case 0x4: INC(&regs.d); break;
					case 0x5: DEC(&regs.d); break;
					case 0x6: immediate8 = getNextOperand(); LD(&regs.d, &immediate8); break;
					case 0x7: RLC(&regs.a); break;
					case 0x8: JR(getNextOperand()); break;
					case 0x9: ADD_HL(regs.de); break;
					case 0xA: LD(&regs.a, getByte(regs.de)); break;
					case 0xB: DEC_16(&regs.de); break;
					case 0xC: INC(&regs.e); break;
					case 0xD: DEC(&regs.e); break;
					case 0xE: immediate8 = getNextOperand(); LD(&regs.e, &immediate8); break;
					case 0xF: RRA(); break;
				}
				break;
			case 0x20:
				switch (opcode & 0x0F) {
					case 0x0: JR_CC(NZ, getNextOperand()); break;
					case 0x1: regs.hl = getNextLargeOperand(); break;
					case 0x2: LD(getByte(regs.hl), &regs.a); regs.hl += 1; break;
					case 0x3: INC_16(&regs.hl); break;
					case 0x4: INC(&regs.h); break;
					case 0x5: DEC(&regs.h); break;
					case 0x6: immediate8 = getNextOperand(); LD(getByte(regs.hl), &immediate8); break;
					case 0x7: printf("Sub-case 0x27\n"); break;
					case 0x8: JR_CC(Z, getNextOperand()); break;
					case 0x9: ADD_HL(regs.hl); break;
					case 0xA: STR(*getByte(regs.hl)); regs.hl += 1; break;
					case 0xB: DEC_16(&regs.hl); break;
					case 0xC: INC(&regs.l); break;
					case 0xD: DEC(&regs.l); break;
					case 0xE: immediate8 = getNextOperand(); LD(&regs.l, &immediate8); break;
					case 0xF: printf("Sub-case 0x2F\n"); break;
				}
				break;
			case 0x30:
				switch (opcode & 0x0F) {
					case 0x0: JR_CC(NC, getNextOperand()); break;
					case 0x1: regs.sp = getNextLargeOperand(); break;
					case 0x2: setByte(regs.a, regs.hl); regs.hl -= 1; break;
					case 0x3: INC_16(&regs.sp); break;
					case 0x4: INC(getByte(regs.hl)); break;
					case 0x5: DEC(getByte(regs.hl)); break;
					case 0x6: printf("Sub-case 0x36\n"); break;
					case 0x7: printf("Sub-case 0x37\n"); break;
					case 0x8: JR_CC(C, getNextOperand()); break;
					case 0x9: ADD_HL(regs.sp); break;
					case 0xA: STR(*getByte(regs.hl)); regs.hl -= 1; break;
					case 0xB: DEC_16(&regs.sp); break;
					case 0xC: INC(&regs.a); break;
					case 0xD: DEC(&regs.a); break;
					case 0xE: immediate8 = getNextOperand(); LD(&regs.a, &immediate8); break;
					case 0xF: printf("Sub-case 0x3F\n"); break;
				}
				break;
			case 0x40:
				switch (opcode & 0x0F) {
					case 0x0: LD(&regs.b, &regs.b); break;
					case 0x1: LD(&regs.b, &regs.c); break;
					case 0x2: LD(&regs.b, &regs.d); break;
					case 0x3: LD(&regs.b, &regs.e); break;
					case 0x4: LD(&regs.b, &regs.h); break;
					case 0x5: LD(&regs.b, &regs.l); break;
					case 0x6: LD(&regs.b, getByte(regs.hl)); break;
					case 0x7: LD(&regs.b, &regs.a); break;
					case 0x8: LD(&regs.c, &regs.b); break;
					case 0x9: LD(&regs.c, &regs.c); break;
					case 0xA: LD(&regs.c, &regs.d); break;
					case 0xB: LD(&regs.c, &regs.e); break;
					case 0xC: LD(&regs.c, &regs.h); break;
					case 0xD: LD(&regs.c, &regs.l); break;
					case 0xE: LD(&regs.c, getByte(regs.hl)); break;
					case 0xF: LD(&regs.c, &regs.a); break;
				}
				break;
			case 0x50:
				switch (opcode & 0x0F) {
					case 0x0: LD(&regs.d, &regs.b); break;
					case 0x1: LD(&regs.d, &regs.c); break;
					case 0x2: LD(&regs.d, &regs.d); break;
					case 0x3: LD(&regs.d, &regs.e); break;
					case 0x4: LD(&regs.d, &regs.h); break;
					case 0x5: LD(&regs.d, &regs.l); break;
					case 0x6: LD(&regs.d, getByte(regs.hl)); break;
					case 0x7: LD(&regs.d, &regs.a); break;
					case 0x8: LD(&regs.e, &regs.b); break;
					case 0x9: LD(&regs.e, &regs.c); break;
					case 0xA: LD(&regs.e, &regs.d); break;
					case 0xB: LD(&regs.e, &regs.e); break;
					case 0xC: LD(&regs.e, &regs.h); break;
					case 0xD: LD(&regs.e, &regs.l); break;
					case 0xE: LD(&regs.e, getByte(regs.hl)); break;
					case 0xF: LD(&regs.e, &regs.a); break;
				}
				break;
			case 0x60:
				switch (opcode & 0x0F) {
					case 0x0: LD(&regs.h, &regs.b); break;
					case 0x1: LD(&regs.h, &regs.c); break;
					case 0x2: LD(&regs.h, &regs.d); break;
					case 0x3: LD(&regs.h, &regs.e); break;
					case 0x4: LD(&regs.h, &regs.h); break;
					case 0x5: LD(&regs.h, &regs.l); break;
					case 0x6: LD(&regs.h, getByte(regs.hl)); break;
					case 0x7: LD(&regs.h, &regs.a); break;
					case 0x8: LD(&regs.l, &regs.b); break;
					case 0x9: LD(&regs.l, &regs.c); break;
					case 0xA: LD(&regs.l, &regs.d); break;
					case 0xB: LD(&regs.l, &regs.e); break;
					case 0xC: LD(&regs.l, &regs.h); break;
					case 0xD: LD(&regs.l, &regs.l); break;
					case 0xE: LD(&regs.l, getByte(regs.hl)); break;
					case 0xF: LD(&regs.l, &regs.a); break;
				}
				break;
			case 0x70:
				switch (opcode & 0x0F) {
					case 0x0: LD(getByte(regs.hl), &regs.b); break;
					case 0x1: LD(getByte(regs.hl), &regs.c); break;
					case 0x2: LD(getByte(regs.hl), &regs.d); break;
					case 0x3: LD(getByte(regs.hl), &regs.e); break;
					case 0x4: LD(getByte(regs.hl), &regs.h); break;
					case 0x5: LD(getByte(regs.hl), &regs.l); break;
					case 0x6: printf("Sub-case 0x76\n"); break;
					case 0x7: LD(getByte(regs.hl), &regs.a); break;
					case 0x8: LD(&regs.a, &regs.b); break;
					case 0x9: LD(&regs.a, &regs.c); break;
					case 0xA: LD(&regs.a, &regs.d); break;
					case 0xB: LD(&regs.a, &regs.e); break;
					case 0xC: LD(&regs.a, &regs.h); break;
					case 0xD: LD(&regs.a, &regs.l); break;
					case 0xE: LD(&regs.a, getByte(regs.hl)); break;
					case 0xF: LD(&regs.a, &regs.a); break;
				}
				break;
			case 0x80:
				switch (opcode & 0x0F) {
					case 0x0: ADD(&regs.b); break;
					case 0x1: ADD(&regs.c); break;
					case 0x2: ADD(&regs.d); break;
					case 0x3: ADD(&regs.e); break;
					case 0x4: ADD(&regs.h); break;
					case 0x5: ADD(&regs.l); break;
					case 0x6: ADD(getByte(regs.hl)); break;
					case 0x7: ADD(&regs.a); break;
					case 0x8: ADC(&regs.b); break;
					case 0x9: ADC(&regs.c); break;
					case 0xA: ADC(&regs.d); break;
					case 0xB: ADC(&regs.e); break;
					case 0xC: ADC(&regs.h); break;
					case 0xD: ADC(&regs.l); break;
					case 0xE: ADC(getByte(regs.hl)); break;
					case 0xF: ADC(&regs.a); break;
				}
				break;
			case 0x90:
				switch (opcode & 0x0F) {
					case 0x0: SUB(&regs.b); break;
					case 0x1: SUB(&regs.c); break;
					case 0x2: SUB(&regs.d); break;
					case 0x3: SUB(&regs.e); break;
					case 0x4: SUB(&regs.h); break;
					case 0x5: SUB(&regs.l); break;
					case 0x6: SUB(getByte(regs.hl)); break;
					case 0x7: SUB(&regs.a); break;
					case 0x8: SBC(&regs.b); break;
					case 0x9: SBC(&regs.c); break;
					case 0xA: SBC(&regs.d); break;
					case 0xB: SBC(&regs.e); break;
					case 0xC: SBC(&regs.h); break;
					case 0xD: SBC(&regs.l); break;
					case 0xE: SBC(getByte(regs.hl)); break;
					case 0xF: SBC(&regs.a); break;
				}
				break;
			case 0xA0:
				switch (opcode & 0x0F) {
					case 0x0: AND(&regs.b); break;
					case 0x1: AND(&regs.c); break;
					case 0x2: AND(&regs.d); break;
					case 0x3: AND(&regs.e); break;
					case 0x4: AND(&regs.h); break;
					case 0x5: AND(&regs.l); break;
					case 0x6: AND(getByte(regs.hl)); break;
					case 0x7: AND(&regs.a); break;
					case 0x8: XOR(&regs.b); break;
					case 0x9: XOR(&regs.c); break;
					case 0xA: XOR(&regs.d); break;
					case 0xB: XOR(&regs.e); break;
					case 0xC: XOR(&regs.h); break;
					case 0xD: XOR(&regs.l); break;
					case 0xE: XOR(getByte(regs.hl)); break;
					case 0xF: XOR(&regs.a); break;
				}
				break;
			case 0xB0:
				switch (opcode & 0x0F) {
					case 0x0: OR(&regs.b); break;
					case 0x1: OR(&regs.c); break;
					case 0x2: OR(&regs.d); break;
					case 0x3: OR(&regs.e); break;
					case 0x4: OR(&regs.h); break;
					case 0x5: OR(&regs.l); break;
					case 0x6: OR(getByte(regs.hl)); break;
					case 0x7: OR(&regs.a); break;
					case 0x8: CP(&regs.b); break;
					case 0x9: CP(&regs.c); break;
					case 0xA: CP(&regs.d); break;
					case 0xB: CP(&regs.e); break;
					case 0xC: CP(&regs.h); break;
					case 0xD: CP(&regs.l); break;
					case 0xE: CP(getByte(regs.hl)); break;
					case 0xF: CP(&regs.a); break;
				}
				break;
			case 0xC0:
				switch (opcode & 0x0F) {
					case 0x0: RET_CC(NZ); break;
					case 0x1: POP(&regs.bc); break;
					case 0x2: JP_CC(NZ, getNextLargeOperand()); break;
					case 0x3: JP(getNextLargeOperand()); break;
					case 0x4: CALL_CC(NZ, getNextLargeOperand()); break;
					case 0x5: PUSH(regs.bc); break;
					case 0x6: immediate8 = getNextOperand(); ADD(&immediate8); break;
					case 0x7: printf("Sub-case 0xC7\n"); break;
					case 0x8: RET_CC(Z); break;
					case 0x9: RET(); break;
					case 0xA: JP_CC(Z, getNextLargeOperand()); break;
					case 0xB: printf("Sub-case 0xCB\n"); break;
					case 0xC: CALL_CC(Z, getNextLargeOperand()); break;
					case 0xD: CALL(getNextLargeOperand()); break;
					case 0xE: immediate8 = getNextOperand(); ADC(&immediate8); break;
					case 0xF: printf("Sub-case 0xCF\n"); break;
				}
				break;
			case 0xD0:
				switch (opcode & 0x0F) {
					case 0x0: RET_CC(NC); break;
					case 0x1: POP(&regs.de); break;
					case 0x2: JP_CC(NC, getNextLargeOperand()); break;
					case 0x3: printf("Sub-case 0xD3\n"); break;
					case 0x4: CALL_CC(NC, getNextLargeOperand()); break;
					case 0x5: PUSH(regs.de); break;
					case 0x6: immediate8 = getNextOperand(); SUB(&immediate8); break;
					case 0x7: printf("Sub-case 0xD7\n"); break;
					case 0x8: RET_CC(C); break;
					case 0x9: printf("Sub-case 0xD9\n"); break;
					case 0xA: JP_CC(C, getNextLargeOperand()); break;
					case 0xB: printf("Sub-case 0xDB\n"); break;
					case 0xC: CALL_CC(C, getNextLargeOperand()); break;
					case 0xD: printf("Sub-case 0xDD\n"); break;
					case 0xE: immediate8 = getNextOperand(); SBC(&immediate8); break;
					case 0xF: printf("Sub-case 0xDF\n"); break;
				}
				break;
			case 0xE0:
				switch (opcode & 0x0F) {
					case 0x0: setByte(regs.a, 0xFF00 + getNextOperand()); break;
					case 0x1: POP(&regs.hl); break;
					case 0x2: setByte(regs.a, 0xFF00 + regs.c); break;
					case 0x3: printf("Sub-case 0xE3\n"); break;
					case 0x4: printf("Sub-case 0xE4\n"); break;
					case 0x5: PUSH(regs.hl); break;
					case 0x6: immediate8 = getNextOperand(); AND(&immediate8); break;
					case 0x7: printf("Sub-case 0xE7\n"); break;
					case 0x8: ADD_SP(getNextOperand()); break;
					case 0x9: JP(regs.hl); break;
					case 0xA: LD(getByte(getNextOperand()), &regs.a); break;
					case 0xB: printf("Sub-case 0xEB\n"); break;
					case 0xC: printf("Sub-case 0xEC\n"); break;
					case 0xD: printf("Sub-case 0xED\n"); break;
					case 0xE: immediate8 = getNextOperand(); XOR(&immediate8); break;
					case 0xF: printf("Sub-case 0xEF\n"); break;
				}
				break;
			case 0xF0:
				switch (opcode & 0x0F) {
					case 0x0: STR(*getByte(0xFF00 + getNextOperand())); break;
					case 0x1: POP(&regs.af); break;
					case 0x2: STR(*getByte(0xFF00 + regs.c)); break;
					case 0x3: printf("Sub-case 0xF3\n"); break;
					case 0x4: printf("Sub-case 0xF4\n"); break;
					case 0x5: PUSH(regs.af); break;
					case 0x6: immediate8 = getNextOperand(); OR(&immediate8);; break;
					case 0x7: printf("Sub-case 0xF7\n"); break;
					case 0x8: LDHL(getNextOperand()); break;
					case 0x9: regs.sp = regs.hl; break;
					case 0xA: LD(&regs.a, getByte(getNextLargeOperand())); break;
					case 0xB: printf("Sub-case 0xFB\n"); break;
					case 0xC: printf("Sub-case 0xFC\n"); break;
					case 0xD: printf("Sub-case 0xFD\n"); break;
					case 0xE: immediate8 = getNextOperand(); CP(&immediate8); break;
					case 0xF: printf("Sub-case 0xFF\n"); break;
				}
				break;
			default:
				printf("No match found\n");
				break;
		}
	}
}