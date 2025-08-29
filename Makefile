NAME = boyblue
CC = gcc
C_FLAGS = -O -Wall -Wextra -Wwrite-strings -Wswitch-default
SRCS = 	main.c src/cpu.c src/decoder.c src/mmu.c src/gpu.c

SDL3_PATH = ~/Library/Frameworks

LINKER_FLAGS = -I$(SDL3_PATH)/SDL3.xcframework/macos-arm64/SDL3.framework/Headers -F$(SDL3_PATH)/SDL3.xcframework/macos-arm64 -framework SDL3
BUILD_DIR = ./build

.PHONY: all
all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(NAME): $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(C_FLAGS) $(LINKER_FLAGS) $(SRCS) -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)