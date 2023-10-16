CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: test1 test2 test3 test4 test6 test7 test8 test9 test10

list.o: list.c list.h
	gcc $(CFLAGS) -c list.c

test1.o: test1.c list.h
	gcc $(CFLAGS) -c test1.c

test2.o: test2.c list.h
	gcc $(CFLAGS) -c test2.c

test3.o: test3.c list.h
	gcc $(CFLAGS) -c test3.c

test4.o: test4.c list.h
	gcc $(CLFAGS) -c test4.c

test6.o: test6.c list.h
	gcc $(CFLAGS) -c test6.c

test7.o: test7.c list.h
	gcc $(CFLAGS) -c test7.c

test8.o: test8.c list.h
	gcc $(CFLAGS) -c test8.c

test9.o: test9.c list.h
	gcc $(CFLAGS) -c test9.c

test10.o: test10.c list.h
	gcc $(CFLAGS) -c test10.c

test1: test1.o list.o
	gcc $(CFLAGS) test1.o list.o -o test1

test2: test2.o list.o
	gcc $(CFLAGS) test2.o list.o -o test2

test3: test3.o list.o
	gcc $(CFLAGS) test3.o list.o -o test3

test4: test4.o list.o
	gcc $(CFLAGS) test4.o list.o -o test4

test6: test6.o list.o
	gcc $(CFLAGS) test6.o list.o -o test6

test7: test7.o list.o
	gcc $(CFLAGS) test7.o list.o -o test7

test8: test8.o list.o
	gcc $(CFLAGS) test8.o list.o -o test8

test9: test9.o list.o
	gcc $(CFLAGS) test9.o list.o -o test9

test10: test10.o list.o
	gcc $(CFLAGS) test10.o list.o -o test10

clean:
	rm -f *.o test1 test2 test3 test4 test6 test7 test8 test9 test10
