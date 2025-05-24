.PHONY: obj shared

PRJ_NAME := rectangle
SHARED_LIB_NAME := librectangle.so

CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin

LIB_DIR := $(CUR_DIR)/lib
LIB_SHARED_DIR := $(LIB_DIR)/shared

CC := gcc
C_FLAGS := -c -fPIC -o

# Create object files
create_obj:
	$(CC) $(C_FLAGS) $(OBJ_DIR)/main.o $(SRC_DIR)/main.c -I $(INC_DIR)
	$(CC) $(C_FLAGS) $(OBJ_DIR)/rectangle.o $(SRC_DIR)/rectangle.c -I $(INC_DIR)

# Create shared-lib
shared:
	$(CC) -shared $(OBJ_DIR)/* -o $(LIB_SHARED_DIR)/$(SHARED_LIB_NAME)

all: create_obj shared | $(BIN_DIR)
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -lrectangle -Wl,-rpath=$(LIB_SHARED_DIR) -o $(BIN_DIR)/$(PRJ_NAME)

clean: 
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED_DIR)/*
	rm -rf $(BIN_DIR)/*