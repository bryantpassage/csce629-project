CC = g++
CFLAGS = -g -Wall

all: main.o heap.o
	$(CC) $(CFLAGS) main.o heap.o -o main.exe

main.o: main.cpp heap.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

heap.o: heap.cpp heap.h
	$(CC) $(CFLAGS) -c heap.cpp -o heap.o

clean:
	rm -rf *.o main.exe