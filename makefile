CC     = gcc
CFLAGS = -O2

short-opts-example-1: short-opts-example-1.o
	$(CC) $(CFLAGS) -o short-opts-example-1 short-opts-example-1.o

short-opts-example-1.o: short-opts-example-1.c
	$(CC) $(CFLAGS) -c -o short-opts-example-1.o short-opts-example-1.c


short-opts-example-2: short-opts-example-2.o
	$(CC) $(CFLAGS) -o short-opts-example-2 short-opts-example-2.o

short-opts-example-2.o: short-opts-example-2.c
	$(CC) $(CFLAGS) -c -o short-opts-example-2.o short-opts-example-2.c


long-opts-example-1: long-opts-example-1.o
	$(CC) $(CFLAGS) -o long-opts-example-1 long-opts-example-1.o

long-opts-example-1.o: long-opts-example-1.c
	$(CC) $(CFLAGS) -c -o long-opts-example-1.o long-opts-example-1.c


long-opts-example-2: long-opts-example-2.o
	$(CC) $(CFLAGS) -o long-opts-example-2 long-opts-example-2.o

long-opts-example-2.o: long-opts-example-2.c
	$(CC) $(CFLAGS) -c -o long-opts-example-2.o long-opts-example-2.c


clean:
	rm -f opts-example-1 opts-example-2 long-opts-example-1 long-opts-example-2
	rm -f *.o
