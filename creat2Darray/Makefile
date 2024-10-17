# Makefile for 2Darray.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -O2 -ggdb -Wall -Wextra

# Target executable
TARGET = 2Darray

# Source files
SRCS = 2Darray.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# Compiling
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

