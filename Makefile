CC = gcc
CFLAGS = -g -O2 -Wall -Wundef
OBJECTS =

problem1:  Computational\ Mathematics\ Project/main.c
	$(CC) $(CFLAGS) -o problem1 Computational\ Mathematics\ Project/main.c include/pbPlots.c include/supportLib.c
run:
	./problem1

clean:
	rm -f problem1 *.png
	rm -rf problem1.dSYM