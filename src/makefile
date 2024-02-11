# src root makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c17

PHY_DIR = phy
SIM_DIR = sim
UTIL_DIR = util
HEADERS = include
CONFIG = config

SRCS = main.c
OBJS = $(SRCS:.c=.o)

BIN_DIR = ../bin
TARGET = $(BIN_DIR)/comms.exe

all: $(TARGET)

$(TARGET): main.o util.o 
	$(CC) $(CFLAGS) -o main.o $(UTIL_DIR)/util.o

main.o:	$(HEADERS)/main.h $(CONFIG)/comms_config.h
	$(CC) $(CFLAGS) -c main.c

util.o:
	@make -C util

clean:
	rm -f $(OBJS) $(TARGET)