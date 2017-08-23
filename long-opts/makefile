CC     = gcc
CFLAGS = -O2

long-opts: main.o options.o
	$(CC) $(CFLAGS) -o long-opts main.o options.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

options.o: options.c options.h
	$(CC) $(CFLAGS) -c -o options.o options.c

clean:
	rm -f long-opts
	rm -f *.o
