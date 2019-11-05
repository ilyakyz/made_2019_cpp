CC=g++
CFLAGS=-std=c++11

all: test_prog

test_prog: main.o parser.o 
	$(CC) $(CFLAGS) -o test_prog main.o parser.o

main.o: main.cpp parser.hpp
	$(CC) $(CFLAGS) -c main.cpp

parser.o: parser.cpp parser.hpp
	$(CC) $(CFLAGS) -c parser.cpp

test: test_prog
	./test_prog

clean:
	rm -rf *.o test_prog