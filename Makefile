# Name of the executable
TARGET = atreus.exe
BUILD_DIR = build

SOURCES = $(shell find ./code/ -name \*.cpp)
BASE = $(foreach f, $(SOURCES), $(notdir $(basename $(f))))
OBJECTS = $(foreach f, $(BASE), $(BUILD_DIR)/$(f).o)
FOLDERS = $(BUILD_DIR)
CXXFLAGS=-O3 -std=c++11 -Wall -Wextra

LIBS1 = $(shell echo $(LD_LIBRARY_PATH1)| xargs --no-run-if-empty echo)
LIBS2 = $(shell echo $(LD_LIBRARY_PATH2)| xargs --no-run-if-empty echo)
ifeq ($(LIBS1),)
	LINKS=-lsfml-graphics -lsfml-window -lsfml-system
else
	LINKS=-I $(LIBS1) -L $(LIBS2) -lsfml-graphics -lsfml-window -lsfml-system
endif

CXX=g++

.PHONY: all
all: $(FOLDERS) $(BUILD_DIR)/$(TARGET)
	@echo $(TARGET) built

.PHONY: clean
clean:
	rm build/*

$(FOLDERS):
	@mkdir $@

.SECONDEXPANSION:
src = $$(shell find  ./code/ -name  $$(notdir $$(basename $$@)).cpp)
header = $$(shell find  ./code/ -name  $$(notdir $$(basename $$@)).h)
%.o: $(src) $(header)
	@$(CXX) $(CXXFLAGS) -g -c $< -o $@ $(LINKS)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $^ $(LINKS)
