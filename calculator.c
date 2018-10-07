#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "stack.h"

#define DEBUG_MODE 1

char *getInput();
void simplifyPower(char *input);

int main () {
	char *input = getInput();
	simplifyPower(input);
	puts(input);	//don't fuck with that!!

	return 0;
}

/*
   Reads input from stdin, formatting it to contain no space 
   or tab characters and stores it in a string.
   Return:
      char * - string with input
*/
char *getInput () {
	char c;
	char *input = malloc(1024*sizeof(char));
	int i = 0;

	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\t' || c == ' ') continue;
		input[i++] = c;
	}

	input[strlen(input)-1] = ',';
	input[strlen(input)] = '\0';

	return input;
}

void simplifyPower (char *input) {
	int prevPos = -2;

	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == '*' && (prevPos+1 == i)) {
			input[i-1] = '^';
			input[i] = ' ';
			continue;
		}

		if (input[i] == '*') {
			prevPos = i;
		}
	}

	return;
}