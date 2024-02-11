CC = gcc
CFLAGS = -Wall

OBJECTS = phy.o

all: $(OBJECTS)

phy.o: phy.c
	$(CC) $(CFLAGS) -c phy.c -o phy.o

clean:
	rm -f phy.o
