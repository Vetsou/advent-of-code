# ====================================================================================================
# Usage:
# make DAY=XX		# Build selected aoc day (Ex. make DAY=01)
# make dayX			# Build and run selected aoc day (Ex. make day1, make day10)
# make setup		# Setup project structure
# make clean		# Clean build files
# ====================================================================================================

# CONFIG =============================================================================================

SRC_PATH ?= src
BIN_PATH ?= bin

LIB_PATH := $(SRC_PATH)/lib
INC_PATH := $(SRC_PATH)/include

# SYS CONFIG =========================================================================================

MDIR := mkdir
RM := del /Q

# FILES ==============================================================================================

DAY ?= 01
DAY_SRC := $(SRC_PATH)/day-$(DAY).c
DAY_OBJ := $(BIN_PATH)/day-$(DAY).o
DAY_DEP := $(BIN_PATH)/day-$(DAY).d
TARGET := $(BIN_PATH)/day-$(DAY).exe

LIB_SRC := $(wildcard $(LIB_PATH)/*.c)
LIB_OBJ := $(LIB_SRC:$(LIB_PATH)/%.c=$(BIN_PATH)/%.o)

# COMPILER ===========================================================================================

DEBUG_FLAGS =
WARN_FLAGS = -Wall -Wextra -Wno-format

CC := gcc
LIB_FLAGS := -lmingw32
CFLAGS := -std=c99 $(WARN_FLAGS) -I$(INC_PATH) -MMD -MP

# TARGETS ============================================================================================

$(TARGET): $(DAY_OBJ) $(LIB_OBJ)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $^

$(DAY_OBJ): $(DAY_SRC) $(INC_PATH)/aoc.h
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@ -MF $(DAY_DEP)

$(BIN_PATH)/%.o: $(LIB_PATH)/%.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

all: setup $(TARGET)

clean:
	$(RM) $(BIN_PATH)

setup:
	if not exist "$(BIN_PATH)" $(MDIR) $(BIN_PATH)

run: all
	$(TARGET)

# DAYS ===============================================================================================

day1:
	@$(MAKE) DAY=01 run

day2:
	@$(MAKE) DAY=02 run

day3:
	@$(MAKE) DAY=03 run

day4:
	@$(MAKE) DAY=04 run

day7:
	@$(MAKE) DAY=07 run

day8:
	@$(MAKE) DAY=08 run

# ====================================================================================================

.PHONY: all clean setup run