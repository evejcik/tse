CFLAGS=-Wall -pedantic -std=c11 -I. -g

OFILES=queue.o hash.o webpage.o pageio.o indexio.o

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

all: $(OFILES)
	ar cr ../lib/libutils.a $(OFILES)

clean:
	rm -f webpage.o ../lib/libutils.a     
