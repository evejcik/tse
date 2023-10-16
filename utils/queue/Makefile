CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: queue_test1 queue_test2 queue_test3 queue_test4 queue_test5 queue_test6

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

queue_test1.o: queue_test1.c queue.h
	gcc $(CFLAGS) -c queue_test1.c

queue_test2.o: queue_test2.c queue.h
	gcc $(CFLAGS) -c queue_test2.c

queue_test3.o: queue_test3.c queue.h
	gcc $(CFLAGS) -c queue_test3.c

queue_test4.o: queue_test4.c queue.h
	gcc $(CFLAGS) -c queue_test4.c

queue_test5.o: queue_test5.c queue.h
	gcc $(CFLAGS) -c queue_test5.c

queue_test6.o: queue_test6.c queue.h
	gcc $(CFLAGS) -c queue_test6.c

queue_test1: queue_test1.o queue.o
	gcc $(CFLAGS) queue_test1.o queue.o -o queue_test1

queue_test2: queue_test2.o queue.o
	gcc $(CFLAGS) queue_test2.o queue.o -o queue_test2

queue_test3: queue_test3.o queue.o
	gcc $(CFLAGS) queue_test3.o queue.o -o queue_test3

queue_test4: queue_test4.o queue.o
	gcc $(CFLAGS) queue_test4.o queue.o -o queue_test4

queue_test5: queue_test5.o queue.o
	gcc $(CFLAGS) queue_test5.o queue.o -o queue_test5

queue_test6: queue_test6.o queue.o
	gcc $(CFLAGS) queue_test6.o queue.o -o queue_test6	

clean:
	rm -f *.o queue_test1 queue_test2 queue_test3 queue_test4 queue_test5 queue_test6
