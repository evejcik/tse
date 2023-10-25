CFLAGS= -Wall -pedantic -std=c11 -I../utils -L../lib -g
LIBS=-lutils -lcurl

all: pagesaveTest

pagesaveTest:
	gcc $(CFLAGS) pagesaveTest.c $(LIBS) -o $@

clean:
	rm -f pagesaveTest
