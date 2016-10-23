CC     = gcc
CFLAGS = -O2

short-opts: main.o options.o
	$(CC) $(CFLAGS) -o short-opts main.o options.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

options.o: options.c options.h
	$(CC) $(CFLAGS) -c -o options.o options.c

clean:
	rm -f short-opts
	rm -f *.o
