CXX := g++
SRC_DIR := src
BUILD_DIR := build
LIB_DIR := lib

# Assuming all your parser files are in src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

CXXFLAGS := -std=c++11 -Wall -Iinclude

.PHONY: all clean

all: $(LIB_DIR)/libxmlparser.a

$(LIB_DIR)/libxmlparser.a: $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)
