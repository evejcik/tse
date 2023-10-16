CFLAGS=-Wall -pedantic -std=c11 -I. -g

OFILES=queue.o hash.o #webpage.o

all: $(OFILES)
	ar cr ../lib/libutils.a $(OFILES)

#webpage.o: webpage.h
#	gcc $(CFLAGS) -c webpage.c

hash.o:  hash/hash.h
#	gcc $(CFLAGS) -c hash/hash.c

queue.o: queue/queue.h
#	gcc $(CFLAGS) -c queue/queue.c

clean:
	rm -f *.o 
