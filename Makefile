TARGET = boyblue
CC = gcc
CFLAGS = -O -Wall -Wextra -Wwrite-strings -Wswitch-default

SRCS = $(shell find . -name "*.c")
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
.PHONY: all

#build:  main.c
# 	$(CC) $(CFLAGS) $(SRCS) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(TARGET)
# 
# debug:
# 	$(CC) $(CFLAGS) -g $(SRCS) -o $(BUILD_DIR)/$(TARGET)_debug

# .PHONY: clean
# clean:
# 	rm -f $(BUILD_DIR)/$(TARGET)
# 
# .PHONY: run
# run: build
# 	$(BUILD_DIR)/$(TARGET)