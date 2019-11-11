CC=g++
CFLAGS=-std=c++11

all: test_prog

test_prog: main.o matrix.o 
	$(CC) $(CFLAGS) -o test_prog main.o matrix.o

main.o: main.cpp matrix.hpp
	$(CC) $(CFLAGS) -c main.cpp

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(CFLAGS) -c matrix.cpp

test: test_prog
	./test_prog

clean:
	rm -rf *.o test_prog