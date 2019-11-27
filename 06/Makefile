CC=g++
CFLAGS=-std=c++11 -DDIGIT_SIZE=100

all: test_prog

test_prog: main.o big_int.o 
	$(CC) $(CFLAGS) -o test_prog main.o big_int.o

main.o: main.cpp big_int.hpp
	$(CC) $(CFLAGS) -c main.cpp

big_int.o: big_int.cpp big_int.hpp
	$(CC) $(CFLAGS) -c big_int.cpp

test: test_prog
	./test_prog

clean:
	rm -rf *.o test_prog