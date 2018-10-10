#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack.h"
#include "btree.h"

#define DEBUG_MODE 1

char *getInput();
void simplify(char *input);
char *getPrecende(char *input);
int countCommas(char *input);
char **getExpressions(char *input, int *number);
void removeChar(char *string, char garbage);
void solve(char **exp, int nbrExp, char *precList);
bool checkExpression(char *exp);
bool isopndelim(char x);
bool isclsdelim(char x);
bool isdelim(char x);
bool isbinop(char x);
int precedence(char ope, char *precList);
void freeAll(char *input, char *precList, char **exp, int nbrExp);

int main () {
	int nbrExp = 0;
	char *input = getInput();
	simplify(input);
	char *precedence = getPrecende(input);
	char **expressions = getExpressions(input, &nbrExp);
	solve(expressions, nbrExp, precedence);

	freeAll(input, precedence, expressions, nbrExp);
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
	Changes all "**" in input to "^ ", all 
	"log" to "l", "exp" to "e" and "sqrt" to "s".
	Parameter:
		char *input - string to be treated
*/
void simplify (char *input) {
	int prevPos = -2;

	for (int i = 0; i < strlen(input); i++) {
		
		if (input[i] == 's') {
			input[i+1] = ' ';
			input[i+2] = ' ';
			input[i+3] = ' ';
		}

		else if (input[i] == 'l' || input[i] == 'e') {
			input[i+1] = ' ';
			input[i+2] = ' ';
		}

		else if (input[i] == '*' && (prevPos+1 == i)) {
			input[i-1] = '^';
			input[i] = ' ';
		}

		else if (input[i] == '*') {
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
int countCommas (char *input) {
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
		removeChar(allExp[i], ' ');
		removeChar(allExp[i], '\n');
	}

	*number = nbrExp;

	return allExp;
}

/*
	Removes a determinated character from a string.
	Parameters:
		char *string - string to be modified
		char garbage - char to be deleted from string
*/
void removeChar (char *string, char garbage) {
	char *source, *destination;

	for (source = destination = string; *source != '\0'; source++) {
		*destination = *source;
		if (*destination != garbage) destination++;
	}
	*destination = '\0';

	return;
}

/*
	Takes in a list of infix notation expressions and calculates
	them using binary trees and stacks.
	Parameters:
		char **exp - list of expressions to be calculated
		int nbrExp - number of expressions
		char *precList - a list that indicates the precedence
		of the operations contained in these expressions
*/
void solve (char **exp, int nbrExp, char *precList) {
	bool isWrong = false;

	for (int i = 0; i < nbrExp; i++) {
		isWrong = checkExpression(exp[i]);

		if (isWrong) {
			printf("Expressao incorreta.\n");
			continue;
		}

		else if (DEBUG_MODE) printf("A expressao e semi-valida.\n"); 

		//colocar na arvore
		//calcular
		//se o resultado for calculavel, printar o resultado. Caso contrario, printar (Expressao invalida.\n)
	}

	return;
}

/*
	Search for errors in expression passed as
	argument. 
	(The question is: have you found any errors?)
	Parameter:
		char *exp - expression to be checked
	Return:
		bool - true if the expression is wrong,
		false if it's correct
*/
bool checkExpression (char *exp) {
	char *cur = exp;
	Stack delimStk = newStack();	//antes de retornar, eu SEMPRE preciso deletar a pilha primeiro;

	while (*cur != '\0') {
		
		if (isopndelim(*cur)) {
			push(delimStk, *cur);
		}

		else if (isclsdelim(*cur)) {
			if ( *cur == ')' && top(delimStk) == '(' ) pop(delimStk);
			else if ( *cur == ']' && top(delimStk) == '[' ) pop(delimStk);
			else if ( *cur == '}' && top(delimStk) == '{' ) pop(delimStk);
			else {
				delStack(delimStk);
				return true;
			}
		}

		else if (isbinop(*cur)) {
			if (isbinop(*(cur+1))) {
				delStack(delimStk);
				return true;
			}
		}

		cur++;
	}

	if (!isEmpty(delimStk)) {
		delStack(delimStk);
		return true;
	}

	delStack(delimStk);
	return false;
}

/*
	Checks if a char is a open delimiter or not.
	Parameter:
		char x - char to be analysed
	Return:
		bool - true if is, false if isn't
*/
bool isopndelim (char x) {
	if (x == '(' || x == '[' || x == '{') return true;
	else return false;
}

/*
	Checks if a char is a close delimiter or not.
	Parameter:
		char x - char to be analysed
	Return:
		bool - true if is, false if isn't
*/
bool isclsdelim (char x) {
	if (x == ')' || x == ']' || x == '}') return true;
	else return false;
}

/*
	Checks if a char is a delimiter or not.
	Parameter:
		char x - char to be analysed
	Return:
		bool - true if is, false if isn't
*/
bool isdelim (char x) {
	if (x == '(' || x == ')' || x == '[' || x == ']' || x == '{' || x == '}') return true;
	else return false;
}

/*
	Checks if a char is a binary operation or not.
	Parameter:
		char x - char to be analysed
	Return:
		bool - true if is, false if isn't
*/
bool isbinop (char x) {
	if (x == '^' || x == '*' || x == '/' || x == '+' || x == '-') return true;
	else return false;
}

/*
	Calculates the precedence of operator "op".
	Parameters:
		char ope - operator to be checked
		char *precList - string containing the 
		order of precedence
	Return:
		int - a number indicating it's precedence
		(1 - lowest, 5 - highest)
*/
int precedence (char ope, char *precList) {
	int p = 5, i = 0;
	
	while (precList[i] != ope && p > 0) {
		p--;
		i++;
	}

	return p;
}

/*
	Deallocates all the strings mallocated through the program.
	Parameters:
		char *input - input string
		char *precList - precedence list
		char **exp - matrix of expressions
		int nbrExp - number of expressions
*/
void freeAll (char *input, char *precList, char **exp, int nbrExp) {
	for (int i = 0; i < nbrExp; i++) {
		free(exp[i]);
	}
	free(exp);

	free(precList);
	free(input);

	return;
}