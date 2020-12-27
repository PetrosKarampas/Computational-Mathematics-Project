CC = gcc
CFLAGS = -g -O2 -Wall -Wundef
OBJECTS =

all: problem1
problem1:  Computational\ Mathematics\ Project/problem1.c
	$(CC) $(CFLAGS) -o problem1 Computational\ Mathematics\ Project/problem1.c
run:
	./problem1

clean:
	rm -f problem1
	rm -rf problem1.dSYM
