CFLAGS=-Wall -pedantic -std=c11 -I. -g

OFILES=queue.o hash.o webpage.o pageio.o index.o indexio.o

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

all: 			$(OFILES)
	ar cr ../lib/libutils.a $(OFILES)

clean:
				rm -f webpage.o pageio.o index.o indexio.o ../lib/libutils.a
