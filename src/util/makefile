# util makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c17

HEADERS = ../include
CONFIG = ../config

SRCS = util.c
OBJS = $(SRCS:.c=.o)

all: util.o

util.o: util.c $(HEADERS)/util.h $(CONFIG)/comms_config.h
	$(CC) $(CFLAGS) -I $(HEADERS) -I $(CONFIG) -c util.c -o util.o

clean:
	rm -f util.o