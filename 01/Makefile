CC=g++
CFLAGS=-std=c++11

all: calc

calc: main.o calc.o 
	$(CC) $(CFLAGS) -o calc main.o calc.o

main.o: main.cpp calc.h
	$(CC) $(CFLAGS) -c main.cpp

calc.o: calc.cpp calc.h
	$(CC) $(CFLAGS) -c calc.cpp

test: calc
	sh test.sh

run: calc
	./calc $(ARGS)

clean:
	rm -rf *.o calc