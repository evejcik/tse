CFLAGS=-Wall -pedantic -std=c11 -I../utils -L../lib -g
LIBS=-lutils -lcurl

all: test

test: 
	gcc $(CFLAGS) indexIoTest.c $(LIBS) -o $@

clean:
	rm -f test

