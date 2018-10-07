CC = gcc
DEPS = stack.h
OBJ = stack.c calculator.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

calculator: $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm *.o