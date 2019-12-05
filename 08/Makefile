CC=g++
CFLAGS=-std=c++11

all: test_prog

test_prog: main.o
	$(CC) $(CFLAGS) -o test_prog main.o

main.o: main.cpp Vector.h
	$(CC) $(CFLAGS) -c main.cpp

test: test_prog
	./test_prog

clean:
	rm -rf *.o test_prog