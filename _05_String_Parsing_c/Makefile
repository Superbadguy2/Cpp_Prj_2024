CC = gcc
# 移除-Werror
CFLAGS = -O2 -g -Wall -Wextra -ggdb -I/usr/include/readline

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

TARGET = $(BUILD_DIR)/elf

all: $(TARGET)

# Linking
$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ -lreadline

#  Compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)	#确保构建目录存在
	$(CC) $(CFLAGS) -c $< -o $@

#clean TARGET
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET) 

.PHONY:all clean
