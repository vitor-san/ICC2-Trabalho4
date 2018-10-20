/* Program that calculates mathematical expressions
   with an specific operation precedence order, given
   by the user.
   Author: Vitor Santana Cordeiro
   Year: 2018
   ICMC, USP, Sao Carlos, Sao Paulo, Brazil.
   Introduction to Computer Science II Assignment
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack.h"
#include "btree.h"

#define EMPTY 9876.5432
#define ERROR -12345.6789

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
Tree buildTree(char *exp, char *precList);
void recursiveBuild(char* exp, int beg, int end, Tree curNode, char *precList);
double calculate(Tree curNode);
int precedence(char ope, char *precList);
void freeAll(char *input, char *precList, char **exp);

int main () {
	int nbrExp = 0;

	char *input = getInput();
	simplify(input);

	char *precedence = getPrecende(input);
	char **expressions = getExpressions(input, &nbrExp);

	solve(expressions, nbrExp, precedence);

	freeAll(input, precedence, expressions);

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
	Tree expTree;
	double result;

	for (int i = 0; i < nbrExp; i++) {
		isWrong = checkExpression(exp[i]);

		if (isWrong) {
			printf("Expressao incorreta.\n");
			continue;
		}

		expTree = buildTree(exp[i], precList);
		result = calculate(expTree);
		
		if (result == ERROR) {
			printf("Expressao incorreta.\n");
			delTree(expTree);
			continue;
		}

		printf("%.2f\n", result);
		delTree(expTree);
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
	Builds up a tree of operators and numbers,
	which will be used later to solve de expression.
	Parameters:
		char *exp - expression used to build the tree
		char *precList - list containing precedence order
	Return:
		Tree - root of the expression tree
*/
Tree buildTree (char *exp, char *precList) {
	Tree expTree = newTree();
	recursiveBuild(exp, 0, strlen(exp)-1, expTree, precList);
	return expTree;
}


/*
	Helps 'buildTree' to reach it's goal by 
	doing assignments at each node, recursively.
	Parameters:
		char *exp - expression used to build the tree
		int beg - beggining of the expression
		int end - end of the expression
		Tree curNode - current node of recursion
		char *precList - list containing precedence order
*/
void recursiveBuild (char* exp, int beg, int end, Tree curNode, char *precList) {
	if (curNode == NULL) return;

	char op;
	int opPos;
	bool hasFoundOp = false;
	bool isOnParentheses = false;
	int nbrParentheses = 0;
	bool isOnBrackets = false;
	int nbrBrackets = 0;
	bool isOnBraces = false;
	int nbrBraces = 0;

	for (int i = beg; i <= end; i++) {
		
		if (exp[i] == '\0') break;

		if (exp[i] == '(') {
			if (nbrParentheses++ == 0) isOnParentheses = true;
		}

		else if (exp[i] == '[') {
			if (nbrBrackets++ == 0) isOnBrackets = true;
		}

		else if (exp[i] == '{') {
			if (nbrBraces++ == 0) isOnBraces = true;
		}

		else if (exp[i] == ')') {
			if (nbrParentheses-- == 1) isOnParentheses = false;
		}

		else if (exp[i] == ']') {
			if (nbrBrackets-- == 1) isOnBrackets = false;
		}

		else if (exp[i] == '}') {
			if (nbrBraces-- == 1) isOnBraces = false;
		}

		else if (!isOnParentheses && !isOnBrackets && !isOnBraces && isbinop(exp[i]) ) {
			
			if (!hasFoundOp) {
				hasFoundOp = true;
				op = exp[i];
				opPos = i;
			}

			else if (precedence(exp[i], precList) < precedence(op, precList)) {
				op = exp[i];
				opPos = i;
			}

		}

	}

	if (hasFoundOp) {
		insertOper(curNode, op);
		recursiveBuild(exp, beg, opPos-1, getLeft(curNode), precList);
		recursiveBuild(exp, opPos+1, end, getRight(curNode), precList);
	}

	else {
		
		if (isdelim(exp[beg])) recursiveBuild(exp, beg+1, end-1, curNode, precList);
		
		else if (!(beg == end) && isdelim(exp[beg+1])) {
			insertOper(curNode, exp[beg]);
			recursiveBuild(exp, beg+2, end-1, getLeft(curNode), precList);
		}

		else {
			char *temp = calloc(end-beg+2, sizeof(char));
			int j;
			for (int i = beg, j = 0; i <= end; i++, j++) temp[j] = exp[i];

			insertNum(curNode, atof(temp));
			free(temp);
		}

	}

	return;
}


/*
	Evaluates the expression represented by the tree,
	going from it's leaves to it's root.
	Parameter:
		Tree expTree - binary tree containing the
		expression to be calculated
	Return:
		double - final result of the calculations
*/
double calculate (Tree curNode) {
	if (curNode == NULL) return EMPTY;

	double oper1 = calculate(getLeft(curNode));
	double oper2 = EMPTY;
	if (getOper(curNode) != 'l' && getOper(curNode) != 'e' && getOper(curNode) != 's') oper2 = calculate(getRight(curNode));

	if (oper1 == ERROR || oper2 == ERROR) return ERROR;

	if (oper1 == EMPTY) {		//this means that the current node is a leaf 
		return getNum(curNode);
	}

	if (oper2 == EMPTY) {
		
		switch (getOper(curNode)) {
			case 'l':
				if (oper1 <= 0) return ERROR;
				else return log2(oper1);
			break;

			case 'e':
				return exp(oper1);
			break;

			case 's':
				if (oper1 < 0) return ERROR;
				else return sqrt(oper1);
			break;
		}

	}

	switch (getOper(curNode)) {
		case '+': 
			return oper1 + oper2;
		break;

		case '-': 
			return oper1 - oper2;
		break;

		case '*': 
			return oper1 * oper2;
		break;

		case '/':
			if (oper2 == 0) return ERROR; 
			else return oper1 / oper2;
		break;

		case '^':
			return pow(oper1, oper2);
		break;
	}
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
void freeAll (char *input, char *precList, char **exp) {

	free(input);
	free(precList);
	free(exp);

	return;
}