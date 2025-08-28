NAME = boyblue
CC = gcc
C_FLAGS = -O -Wall -Wextra -Wwrite-strings -Wswitch-default
SRCS = 	main.c src/cpu.c src/decoder.c src/mmu.c
BUILD_DIR = ./build

.PHONY: all
all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(NAME): $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(C_FLAGS) $(SRCS) -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)