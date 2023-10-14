CXX := g++
SRC_DIR := ./
BUILD_DIR := build
TARGET := PrintVisitorDemo

LIB_DIR := ../../lib/ # Adjust this path to point to your XML parser library directory
INCLUDE_DIR := ../../src # Adjust this path to point to your XML parser include directory

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

CXXFLAGS := -std=c++11 -Wall -I$(INCLUDE_DIR)
LDFLAGS :=
LIBS := -L$(LIB_DIR) -lxmlparser

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# copy over the xml files
	cp *.xml $(BUILD_DIR)/

clean:
	rm -rf $(BUILD_DIR)
