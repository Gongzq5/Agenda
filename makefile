# Makefile for Agenda
CC := g++
FLAGS := -std=c++11
BUILD_DIR := build
SRC_DIR := src
DATA_DIR := data
INC_DIR := include
BIN_DIR := bin
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/Agenda : $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/User.o $(BUILD_DIR)/main.o 
	@mkdir -p $(BIN_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) $^ -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp 
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)

run:
	@./$(BIN_DIR)/Agenda