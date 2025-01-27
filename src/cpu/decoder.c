
// decoder.c

#include <stdio.h>

#include "decoder.h"
#include "cpu.h"
#include "../mmu/mmu.h"

uint8_t getNextOperand() {
	// get next operand 
	// TODO: Increment PC?
	regs.pc += 1;
	printf("Next requested operand is: 0x%.2X \n", *getByte(regs.pc));
	return *getByte(regs.pc);
}

uint16_t getNextLargeOperand() {
	uint16_t value;
	regs.pc += 1;
	value = *getByte(regs.pc) << 8;
	regs.pc += 1;
	value |= *getByte(regs.pc);
	printf("Next requested operand is: 0x%.4X at addresses 0x%.2X and 0x%.2X \n", value, regs.pc - 2, regs.pc - 1);
	return value;
}

static uint8_t immediate8; // used for storing 8-bit immediate values

int decode(uint8_t opcode) {
		
	if (opcode == 0xCB) { // check leading bits
		printf("CB00\n");
	} else {
		switch (opcode & 0xF0) { // match higher level
			case 0x00:
				printf("Matched case 0x00\n");
				switch (opcode & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: SET_BC(getNextLargeOperand()); break;
					case 0x2: STR(BC_REG); break;
					case 0x3: INC_BC(1); break;
					case 0x4: INC(&regs.b); break;
					case 0x5: DEC(&regs.b); break;
					case 0x6: immediate8 = getNextOperand(); LD(&regs.b, &immediate8); break;
					case 0x7: RLCA(); break;
					case 0x8: regs.sp = getNextLargeOperand(); break;
					case 0x9: ADD_HL(BC_REG); break;
					case 0xA: STR(*getByte(BC_REG)); break;
					case 0xB: INC_BC(-1); break;
					case 0xC: INC(&regs.c); break;
					case 0xD: DEC(&regs.c); break;
					case 0xE: immediate8 = getNextOperand(); LD(&regs.c, &immediate8); break;
					case 0xF: RRCA(); break;
				}
				break;
			case 0x10:
				printf("Matched case 0x10\n");
				switch (opcode & 0x0F) {
					case 0x0: printf("Sub-case 0x00\n"); break;
					case 0x1: SET_DE(getNextLargeOperand()); break;
					case 0x2: STR(DE_REG); break;
					case 0x3: INC_DE(1); break;
					case 0x4: INC(&regs.d); break;
					case 0x5: DEC(&regs.d); break;
					case 0x6: immediate8 = getNextOperand(); LD(&regs.d, &immediate8); break;
					case 0x7: RLA(); break;
					case 0x8: JR(getNextOperand()); break;
					case 0x9: ADD_HL(DE_REG); break;
					case 0xA: STR(*getByte(DE_REG)); break;
					case 0xB: INC_DE(-1); break;
					case 0xC: INC(&regs.e); break;
					case 0xD: DEC(&regs.e); break;
					case 0xE: immediate8 = getNextOperand(); LD(&regs.e, &immediate8); break;
					case 0xF: RRA(); break;
				}
				break;
			case 0x20:
				printf("Matched case 0x20\n");
				switch (opcode & 0x0F) {
					case 0x0: JR_CC(NZ, getNextOperand()); break;
					case 0x1: SET_HL(getNextLargeOperand()); break;
					case 0x2: LD(getByte(HL_REG), &regs.a); SET_HL(HL_REG + 1); break;
					case 0x3: INC_HL(1); break;
					case 0x4: INC(&regs.h); break;
					case 0x5: DEC(&regs.h); break;
					case 0x6: immediate8 = getNextOperand(); LD(getByte(HL_REG), &immediate8); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: JR_CC(Z, getNextOperand()); break;
					case 0x9: ADD_HL(HL_REG); break;
					case 0xA: STR(*getByte(HL_REG)); SET_HL(HL_REG + 1); break;
					case 0xB: INC_HL(-1); break;
					case 0xC: INC(&regs.l); break;
					case 0xD: DEC(&regs.l); break;
					case 0xE: immediate8 = getNextOperand(); LD(&regs.l, &immediate8); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0x30:
				printf("Matched case 0x30\n");
				switch (opcode & 0x0F) {
					case 0x0: JR_CC(NC, getNextOperand()); break;
					case 0x1: regs.sp = getNextLargeOperand(); break;
					case 0x2: LD(getByte(HL_REG), &regs.a); SET_HL(HL_REG - 1); break;
					case 0x3: INC_SP(1); break;
					case 0x4: INC(getByte(HL_REG)); break;
					case 0x5: DEC(getByte(HL_REG)); break;
					case 0x6: printf("Sub-case 0x06\n"); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: JR_CC(C, getNextOperand()); break;
					case 0x9: ADD_HL(regs.sp); break;
					case 0xA: STR(*getByte(HL_REG)); SET_HL(HL_REG - 1); break;
					case 0xB: INC_SP(-1); break;
					case 0xC: INC(&regs.a); break;
					case 0xD: DEC(&regs.a); break;
					case 0xE: STR(getNextOperand()); break;
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
					case 0x0: SUB(&regs.b); break;
					case 0x1: SUB(&regs.c); break;
					case 0x2: SUB(&regs.d); break;
					case 0x3: SUB(&regs.e); break;
					case 0x4: SUB(&regs.h); break;
					case 0x5: SUB(&regs.l); break;
					case 0x6: SUB(getByte(HL_REG)); break;
					case 0x7: SUB(&regs.a); break;
					case 0x8: SBC(&regs.b); break;
					case 0x9: SBC(&regs.c); break;
					case 0xA: SBC(&regs.d); break;
					case 0xB: SBC(&regs.e); break;
					case 0xC: SBC(&regs.h); break;
					case 0xD: SBC(&regs.l); break;
					case 0xE: SBC(getByte(HL_REG)); break;
					case 0xF: SBC(&regs.a); break;
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
					case 0x8: CP(&regs.b); break;
					case 0x9: CP(&regs.c); break;
					case 0xA: CP(&regs.d); break;
					case 0xB: CP(&regs.e); break;
					case 0xC: CP(&regs.h); break;
					case 0xD: CP(&regs.l); break;
					case 0xE: CP(getByte(HL_REG)); break;
					case 0xF: CP(&regs.a); break;
				}
				break;
			case 0xC0:
				printf("Matched case 0xC0\n");
				switch (opcode & 0x0F) {
					case 0x0: RET_CC(NZ); break;
					case 0x1: POP(BC); break;
					case 0x2: JP_CC(NZ, getNextLargeOperand()); break;
					case 0x3: JP(getNextLargeOperand()); break;
					case 0x4: CALL_CC(NZ, getNextLargeOperand()); break;
					case 0x5: PUSH(BC_REG); break;
					case 0x6: immediate8 = getNextOperand(); ADD(&immediate8); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: RET_CC(Z); break;
					case 0x9: RET(); break;
					case 0xA: JP_CC(Z, getNextLargeOperand()); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: CALL_CC(Z, getNextLargeOperand()); break;
					case 0xD: CALL(getNextLargeOperand()); break;
					case 0xE: immediate8 = getNextOperand(); ADC(&immediate8); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xD0:
				printf("Matched case 0xD0\n");
				switch (opcode & 0x0F) {
					case 0x0: RET_CC(NC); break;
					case 0x1: POP(DE); break;
					case 0x2: JP_CC(NC, getNextLargeOperand()); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: CALL_CC(NC, getNextLargeOperand()); break;
					case 0x5: PUSH(DE_REG); break;
					case 0x6: immediate8 = getNextOperand(); SUB(&immediate8); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: RET_CC(C); break;
					case 0x9: printf("Sub-case 0x09\n"); break;
					case 0xA: JP_CC(C, getNextLargeOperand()); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: CALL_CC(C, getNextLargeOperand()); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: immediate8 = getNextOperand(); SBC(&immediate8); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xE0:
				printf("Matched case 0xE0\n");
				switch (opcode & 0x0F) {
					case 0x0: LD(getByte(0xFF00 + getNextOperand()), &regs.a); break;
					case 0x1: POP(HL); break;
					case 0x2: LD(getByte(0xFF00 + regs.c), &regs.a); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: PUSH(HL_REG); break;
					case 0x6: immediate8 = getNextOperand(); AND(&immediate8); break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: ADD_SP(getNextOperand()); break;
					case 0x9: JP(HL_REG); break;
					case 0xA: LD(getByte(getNextOperand()), &regs.a); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: immediate8 = getNextOperand(); XOR(&immediate8); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			case 0xF0:
				printf("Matched case 0xF0\n");
				switch (opcode & 0x0F) {
					case 0x0: STR(*getByte(0xFF00 + getNextOperand())); break;
					case 0x1: POP(AF); break;
					case 0x2: STR(*getByte(0xFF00 + regs.c)); break;
					case 0x3: printf("Sub-case 0x03\n"); break;
					case 0x4: printf("Sub-case 0x04\n"); break;
					case 0x5: PUSH(AF_REG); break;
					case 0x6: immediate8 = getNextOperand(); OR(&immediate8);; break;
					case 0x7: printf("Sub-case 0x07\n"); break;
					case 0x8: LDHL(getNextOperand()); break;
					case 0x9: regs.sp = HL_REG; break;
					case 0xA: STR(*getByte(getNextLargeOperand())); break;
					case 0xB: printf("Sub-case 0x0B\n"); break;
					case 0xC: printf("Sub-case 0x0C\n"); break;
					case 0xD: printf("Sub-case 0x0D\n"); break;
					case 0xE: immediate8 = getNextOperand(); CP(&immediate8); break;
					case 0xF: printf("Sub-case 0x0F\n"); break;
				}
				break;
			default:
				printf("No match found\n");
				break;
		}
	}
}