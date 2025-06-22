.PHONY: obj static

PRJ_NAME := rectangle
STATIC_LIB_NAME := librectangle.a

CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin

LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static

CC := gcc
C_FLAGS := -c -o

# Create object files
create_obj:
	$(CC) $(C_FLAGS) $(OBJ_DIR)/main.o $(SRC_DIR)/main.c -I $(INC_DIR)
	$(CC) $(C_FLAGS) $(OBJ_DIR)/rectangle.o $(SRC_DIR)/rectangle.c -I $(INC_DIR)

# Create static-lib
static:
	ar rcs $(LIB_STATIC_DIR)/$(STATIC_LIB_NAME) $(OBJ_DIR)/rectangle.o

all: create_obj static
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -lrectangle -o $(BIN_DIR)/$(PRJ_NAME)

clean: 
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_STATIC_DIR)/*
	rm -rf $(BIN_DIR)/*