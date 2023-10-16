CFLAGS=-Wall -pedantic -std=c11 -I. -g

OFILES=queue.o hash.o webpage.o

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

all: $(OFILES)
	ar cr ../lib/libutils.a $(OFILES)

webpage.o: webpage.h
	gcc $(CFLAGS) -c webpage.c

hash.o: hash/hash.h
	gcc $(CFLAGS) -c hash/hash.c

queue.o: queue/queue.h
	gcc $(DFLAGS) -c queue/queue.c

clean:
	rm -f *.o 
