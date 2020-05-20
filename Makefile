CFLAGS=-c -Wall
CC=gcc
CXX=g++

all: main.o assembler.o stack.o machine.o
	$(CC) -o pilemachine main.o machine.o stack.o
	$(CXX) -o assembler assembler.o


main.o: main.c machine.h stack.h
	$(CC) $(CFLAGS) main.c
	
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) stack.c
	
machine.o: machine.c machine.h stack.h
	$(CC) $(CFLAGS) machine.c

assembler.o: assembler.cpp
	$(CXX) $(CFLAGS) assembler.cpp
	
clean:
	rm -f main.o assembler.o stack.o machine.o pilemachine assembler
