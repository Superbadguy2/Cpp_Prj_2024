# Makefile for IntRegularMatch.c

# 编译器和标志
CC = gcc
CFLAGS = -Wall -g  # 显示警告并启用调试信息

# 源文件和目标文件
SRC = IntRegularMatch.c
OBJ = $(SRC:.c=.o)
EXEC = IntRegularMatch  # 可执行文件名称与源文件名称相同

# 默认目标：编译源文件生成可执行文件
all: $(EXEC)

# 编译目标：编译源文件生成可执行文件
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# 编译源文件生成目标文件
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

# 清理生成的文件
clear:
	rm -f $(OBJ) $(EXEC)

# 伪目标
.PHONY: all clear

