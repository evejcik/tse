CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: test1 test2 test3 test4

hash.o: hash.c hash.h
	gcc $(CFLAGS) -c hash.c

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

test1.o: test1.c hash.h
	gcc $(CFLAGS) -c test1.c

test2.o: test2.c hash.h
	gcc $(CFLAGS) -c test2.c

test3.o: test3.c hash.h
	gcc $(CFLAGS) -c test3.c

test4.o: test4.c hash.h
	gcc $(CFLAGS) -c test4.c

test1: test1.o hash.o queue.o
	gcc $(CFLAGS) test1.o hash.o queue.o  -o test1

test2: test2.o hash.o queue.o
	gcc $(CFLAGS) test2.o hash.o queue.o -o test2

test3: test3.o hash.o queue.o
	gcc $(CFLAGS) test3.o hash.o queue.o -o test3

test4: test4.o hash.o queue.o
	gcc $(CFLAGS) test4.o hash.o queue.o -o test4

clean:
	rm -f *.o test1 test2 test3 test4
