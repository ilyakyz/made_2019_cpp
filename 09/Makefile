CC=g++
CFLAGS=-std=c++14

all: test_prog

test_prog: main.o ThreadPool.o 
	$(CC) $(CFLAGS) -o test_prog main.o ThreadPool.o

main.o: main.cpp ThreadPool.hpp
	$(CC) $(CFLAGS) -c main.cpp

ThreadPool.o: ThreadPool.cpp ThreadPool.hpp
	$(CC) $(CFLAGS) -c ThreadPool.cpp

test: test_prog
	./test_prog

clean:
	rm -rf *.o test_prog