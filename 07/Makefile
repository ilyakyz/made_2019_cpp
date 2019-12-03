CC=g++
CFLAGS=-std=c++11

all: test_prog

test_prog: main.o format.o 
	$(CC) $(CFLAGS) -o test_prog main.o format.o

main.o: main.cpp format.hpp
	$(CC) $(CFLAGS) -c main.cpp

format.o: format.cpp format.hpp
	$(CC) $(CFLAGS) -c format.cpp

test: test_prog
	./test_prog

clean:
	rm -rf *.o test_prog