CC = gcc
CFLAGS = -g -O2 -Wall -Wundef
OBJECTS =

all: problem1b	problem1d problem2d

problem1b:  Problem-1b/problem1b.c
	$(CC) $(CFLAGS) -o bin/problem1b Problem-1b/problem1b.c

problem1d:  Problem-1d/problem1d.c
	$(CC) $(CFLAGS) -o bin/problem1d Problem-1d/problem1d.c
	
problem2d:  Problem-2d/problem2d.c
	$(CC) $(CFLAGS) -o bin/problem2d Problem-2d/problem2d.c -lm

clean:
	rm -f bin/problem1b bin/problem1d bin/problem2d
	rm -rf bin/*.dSYM
