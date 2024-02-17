LIB = lib
SRC = src
BLD = build

all: main.exe

# Executable target (build all objects and run)
main.exe: $(BLD)/main.o $(BLD)/util.o $(BLD)/phy.o $(BLD)/dll.o \
			$(BLD)/sim.o
	gcc $(BLD)/main.o $(BLD)/util.o $(BLD)/phy.o $(BLD)/dll.o \
		$(BLD)/sim.o -o main.exe
	@./main.exe

# main source file target
$(BLD)/main.o: $(SRC)/main.c $(SRC)/main.h $(LIB)/comms_config.h \
			   $(LIB)/util.c $(LIB)/util.h $(LIB)/phy.c $(LIB)/phy.h \
			   $(LIB)/dll.c $(LIB)/dll.h $(LIB)/net.h
	gcc -I $(LIB) -c $(SRC)/main.c -o $(BLD)/main.o 

# Utilities
$(BLD)/util.o: $(LIB)/util.c $(LIB)/util.h $(LIB)/comms_config.h
	gcc -c $(LIB)/util.c -o $(BLD)/util.o

# Physical (phy) layer object
$(BLD)/phy.o: $(LIB)/phy.c $(LIB)/phy.h $(LIB)/dll.c $(LIB)/dll.h \
		      $(LIB)/util.c $(LIB)/util.h $(LIB)/comms_config.h
	gcc -c $(LIB)/phy.c -o $(BLD)/phy.o

# Data Link Layer (dll) object
$(BLD)/dll.o: $(LIB)/dll.c $(LIB)/dll.h $(LIB)/net.h $(LIB)/comms_config.h
	gcc -c $(LIB)/dll.c -o $(BLD)/dll.o

# Simulation (sim) object
$(BLD)/sim.o: $(LIB)/sim.c $(LIB)/sim.h $(LIB)/phy.h $(LIB)/comms_config.h
	gcc -c $(LIB)/sim.c -o $(BLD)/sim.o

clean:
	rm $(wildcard $(BLD)/*.o)
	rm main.exe