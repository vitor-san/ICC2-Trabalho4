#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "stack.h"

#define DEBUG_MODE 1

char *getInput();
void simplifyPower(char *input);
char *getPrecende(char *input);
int countCommas(char *input);
char **getExpressions(char *input, int *number);
void convertRPN(char **expressions, int number; char *precedence);
void shuntingYard(char *expression, char* precedence);


int main () {
	int nbrExp = 0;
	char *input = getInput();
	simplifyPower(input);
	char *precedence = getPrecende(input);
	char **expression = getExpressions(input, &nbrExp);
	convertRPN(expression, nbrExp, precedence);

	free(input);
	free(precedence);
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

/*
	Change all "**" in input to "^ ".
	Parameter:
		char *input - string to be treated
*/
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

/*
	Returns a list of operators, with position 0 of the
	string being the most precedent operator and pos. 5
	the less precedent one.
	Parameter:
		char *input - string that will be examined
	Return:
		char * - string of operators in precedence order
*/
char *getPrecende (char *input) {
	char *precList = malloc(6*sizeof(char));
	char aux;
	int i = 0, j = 0;

	while (i < 5) {
		aux = input[j++];
		if (isspace(aux)) continue;
		precList[i++] = aux;
	}

	input[j] = '!';
	precList[5] = '\0';

	return precList;
}

/*
	Count the number of commas (',') in string passed as argument.
	Parameter:
		char *input - string to be analysed
	Return:
		int - number of commas in input string
*/
int countCommas(char *input) {
	int nCommas = 0, i = 0;
	char aux;

	do {		
		aux = input[i++];
		if (aux == ',') nCommas++;
	} while (aux != '\0');

	return nCommas;
}

/*
	Split input string into individual expressions.
	Parameters:
		char *input - string to be splitted
		int *number - variable in which the
		function will return the number of 
		expressions readed/splitted
	Return:
		char ** - an array of char *, each of them 
		an individual expression (i.e. a matrix)
*/
char **getExpressions (char *input, int *number) {
	int nbrExp = countCommas(input);
	char **allExp = malloc(nbrExp*sizeof(char *));

	strtok(input, "!"); // throws away the precedence list, already treated in the program

	for (int i = 0; i < nbrExp; i++) {
		allExp[i] = strtok(NULL, ",");
	}

	*number = nbrExp;

	return allExp;
}

/*
	Takes in a list of infix expressions and converts them
	into RPN (Reverse Polish notation) expressions
	Parameters:
		char **expressions - list of expressions to be converted
		int number - number of expressions
		char *precedence - a list that indicates the precedence
		of the operations contained in this expressions
*/
void convertRPN(char **expressions, int number; char *precedence) {

	for (int i = 0; i < number; i++) {
		shuntingYard(expressions[i], precedence);
	}

	return;
}

/*
	Parses a mathematical expression specified in infix notation,
	producing a postfix notation string.
	Parameters:
		char *expression - expression to be parsed
		char *precedence - list of precedence
*/
void shuntingYard(char *expression, char* precedence) {
	char temporary[strlen(expression)];
	Stack opStack = newStack();

	while () {
		if ()


	}

	return;
}