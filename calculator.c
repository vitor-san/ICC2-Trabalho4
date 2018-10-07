#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

#define DEBUG_MODE 1

char *getInput();

int main () {
	char *input = getInput();
	puts(input);
	return 0;
}

char *getInput () {
	char c;
	char *input = malloc(1024*sizeof(char));
	int i = 0;

	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\t' || c == '\n') continue;
		input[i++] = c;
	}

	input[strlen(input)] = '\0';

	return input;
}