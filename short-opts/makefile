CC     = gcc
CFLAGS = -O2

short-opts: main.o opts.o
	$(CC) $(CFLAGS) -o short-opts main.o opts.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

opts.o: opts.c opts.h
	$(CC) $(CFLAGS) -c -o opts.o opts.c

clean:
	rm -f short-opts
	rm -f *.o
