
#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

#define SCREEN_SCALE 5

#define WINDOW_WIDTH (SCREEN_WIDTH * SCREEN_SCALE)
#define WINDOW_HEIGHT (SCREEN_HEIGHT * SCREEN_SCALE)

// Memory map

#define VRAM_START 0x8000
#define VRAM_END 0x9FFF
#define VRAM_SIZE (VRAM_END - VRAM_START + 1)

// Clocks
#define CLOCK_SPEED			4194304 // Hz

// Registeers
#define LCD_CONTROL_ADDR 	0xFF40
#define TAC					0xFF07 // timer control
#define TMA					0xFF06 // loaded when TIMA overflows
#define TIMA				0xFF05
#define FY_REG				0xFF44

// TEMP =============================================
typedef enum {
    REG_A,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    REG_F,
    REG_AF,
    REG_BC,
    REG_DE,
    REG_HL,
    REG_SP,
    REG_PC,
	NONE,
} RegID_t;

#endif