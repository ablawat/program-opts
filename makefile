CC     = gcc
CFLAGS = -O2

opts-example-1: opts-example-1.o
	$(CC) $(CFLAGS) -o opts-example-1 opts-example-1.o

opts-example-1.o: opts-example-1.c
	$(CC) $(CFLAGS) -c -o opts-example-1.o opts-example-1.c

opts-example-2: opts-example-2.o
	$(CC) $(CFLAGS) -o opts-example-2 opts-example-2.o

opts-example-2.o: opts-example-2.c
	$(CC) $(CFLAGS) -c -o opts-example-2.o opts-example-2.c

clean:
	rm -f *.o
	rm -f test
