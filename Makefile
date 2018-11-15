all:
	gcc -c main.c funcs.c
	gcc main.o funcs.o -o main

clean:
	rm *.o main