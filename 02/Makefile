CC=g++
CFLAGS=-std=c++11

all: test_prog

test_prog: main.o allocator.o 
	$(CC) $(CFLAGS) -o test_prog main.o allocator.o

main.o: main.cpp allocator.hpp
	$(CC) $(CFLAGS) -c main.cpp

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(CFLAGS) -c allocator.cpp

test: test_prog
	./test_prog

clean:
	rm -rf *.o test_prog