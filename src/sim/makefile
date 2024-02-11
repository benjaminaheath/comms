PHY_DIR = ../phy

CC = gcc
PHY_INCLUDE = -I $(PHY_DIR)
CFLAGS = -Wall 

SIM_OBJECTS = sim.o
PHY_OBJECTS = $(PHY_DIR)/phy.o

all: $(SIM_OBJECTS)

$(PHY_OBJECTS): $(PHY_DIR)/phy.c $(PHY_DIR)/phy.h
	$(CC) $(CFLAGS) -c $(PHY_DIR)/phy.c -o $(PHY_OBJECTS)

$(SIM_OBJECTS): sim.c sim.h $(PHY_OBJECTS)
	$(CC) $(CFLAGS) $(PHY_INCLUDE) -c sim.c -o sim.o

clean:
	rm -f sim.o