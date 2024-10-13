# 指定编译器
CXX = g++

# 设置编译选项
CXXFLAGS = -I./include -O2 -g -Wall -Werror -std=c++11

# 源文件夹
SRC_DIR = src
LIB_DIR = lib

# 源文件
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# 目标文件目录
BUILD_DIR = build

# 目标文件
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# 可执行文件名
TARGET = $(BUILD_DIR)/main

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJS)
#	$(CXX) -o $@ $^ -L$(LIB_DIR) -lmylib  # 如果需要链接库，替换"mylib"为库的名称
#	不需要链接库 
	$(CXX) -o $@ $^

# 编译源文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# mkdir -p $(BUILD_DIR)  # 确保build目录存在
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理目标
clean:
# 只删除目标文件	
	rm -rf $(OBJS)

.PHONY: all clean

