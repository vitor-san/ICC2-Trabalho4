#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "stack.h"

#define DEBUG_MODE 1

char *getInput();

int main () {
	char *input = getInput();
	
	return 0;
}

/*
   Reads input from stdin, formatting it to contain no space 
   characters [' ' , '\n' , '\t'] and stores it in a string.
   Return:
      char * - string with input
*/
char *getInput () {
	char c;
	char *input = malloc(1024*sizeof(char));
	int i = 0;

	while ((c = fgetc(stdin)) != EOF) {
		if (isspace(c)) continue;
		input[i++] = c;
	}

	input[strlen(input)-1] = ',';
	input[strlen(input)] = '\0';

	return input;
}