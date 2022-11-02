CC = g++
CFLAGS = -g -Wall

main.exe: main.o heap.o graph.o
	$(CC) $(CFLAGS) main.o heap.o graph.o -o main.exe

test_suite/test.exe: test_suite/test.o test_suite/test_functions.o heap.o graph.o
	$(CC) $(CFLAGS) test_suite/test.o test_suite/test_functions.o heap.o graph.o -o test_suite/test.exe

main.o: main.cpp heap.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

heap.o: heap.cpp heap.h
	$(CC) $(CFLAGS) -c heap.cpp -o heap.o

graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) -c graph.cpp -o graph.o

test_suite/test.o: test_suite/test.cpp test_suite/test_functions.h
	$(CC) $(CFLAGS) -c test_suite/test.cpp -o test_suite/test.o

test_suite/test_functions.o: test_suite/test_functions.cpp test_suite/test_functions.h heap.h graph.h
	$(CC) $(CFLAGS) -c test_suite/test_functions.cpp -o test_suite/test_functions.o

clean:
	rm -rf *.o main.exe

clean_test:
	rm -rf test_suite/*.o test_suite/test.exe