# Name of the executable
TARGET = atreus.exe
BUILD_DIR = build

SOURCES = $(shell find ./code/ -name \*.cpp)
BASE = $(foreach f, $(SOURCES), $(notdir $(basename $(f))))
OBJECTS = $(foreach f, $(BASE), $(BUILD_DIR)/$(f).o)
FOLDERS = $(BUILD_DIR)

CXXFLAGS=-O3 -std=c++0x -Wall -Wextra
LINKS=-lsfml-graphics -lsfml-window -lsfml-system
CXX=g++

.PHONY: all clean

all: $(FOLDERS) $(BUILD_DIR)/$(TARGET)
	@echo $(TARGET) built

clean:
	rm build/*

$(FOLDERS):
	@mkdir $@

.SECONDEXPANSION:
%.o: $$(shell find  ./code/ -name  $$(notdir $$(basename $$@)).cpp)
	@$(CXX) $(CXXFLAGS) -g -c $< -o $@ $(LINKS)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $^ $(LINKS)
