CC = gcc
CFLAGS = -g -O2 -Wall -Wundef
OBJECTS =

all: problem1b	problem1d

problem1b:  Problem-1b/problem1b.c
	$(CC) $(CFLAGS) -o problem1b Problem-1b/problem1b.c

problem1d:  Problem-1d/problem1d.c
	$(CC) $(CFLAGS) -o problem1d Problem-1d/problem1d.c


clean:
	rm -f problem1b problem1d
	rm -rf *.dSYM
