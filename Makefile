all:
	gcc -o calculator btree.c stack.c calculator.c -lm

run:
	./calculator