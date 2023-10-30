CFLAGS= -Wall -pedantic -std=c11 -I../utils -L../lib -g
LIBS=-lutils -lcurl

all: indexer

indexer:
	gcc $(CFLAGS) indexerStep4b.c $(LIBS) -o $@

clean:
	rm -f indexer
