CC = gcc
CFLAGS = -Wall -g -pthread

all: prog

clean:
	rm -f prog *.o

linkedList.o: linkedList.c linkedList.h
	$(CC) $(CFLAGS) -c linkedList.c

prog.o: prog.c linkedList.h
	$(CC) $(CFLAGS) -c prog.c

prog: linkedList.o prog.o
	$(CC) $(CFLAGS) -o prog prog.o linkedList.o