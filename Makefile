TARGET = boyblue
CC = gcc
CFLAGS = -O -Wall -Wextra -Wwrite-strings -Wswitch-default
SRCS = $(shell find . -name "*.c")
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
	
.PHONY: all clean

#build:  main.c
# 	$(CC) $(CFLAGS) $(SRCS) $(LD_FLAGS) -o $(BUILD_DIR)/$(TARGET)
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