CXX = g++

CXX_ARGS = -c -Wall -Wextra -std=c++17 -Istdlib

BUILD_DIR = output
SRC_DIR = timer

CXX_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OBJ_FILES = $(CXX_FILES:$(SRC_DIR)/%.cpp=output/%_cpp.o)

TARGET = timer.exe

.PHONY: clean

all: $(TARGET)

$(BUILD_DIR)/%_cpp.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_ARGS) $< -o $@

$(TARGET): $(OBJ_FILES)
	$(CXX) -o $(TARGET) $(OBJ_FILES)

clean:
	rm -r output/* $(TARGET)
