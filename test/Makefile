CFLAGS=-Wall -pedantic -std=c11 -I../utils -L../lib -g
LIBS=-lutils -lcurl

all: test1
test1: test1.o
	gcc $(CFLAGS) test1.c $(LIBS) -o $@

clean:
	rm -f test1

