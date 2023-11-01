CFLAGS= -Wall -pedantic -std=c11 -I../utils -L../lib -g
LIBS=-lutils -lcurl

all: indexer indexerE

indexer:
	gcc $(CFLAGS) indexerStep5.c $(LIBS) -o $@

indexerE:
	gcc $(CFLAGS) indexerStep7.c $(LIBS) -o $@

clean:
	rm -f indexer indexerE
