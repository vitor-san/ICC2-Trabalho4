#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"



int precedence (char ope, char *precList) {
	int p = 5, i = 0;
	
	while (precList[i] != ope && p > 0) {
		p--;
		i++;
	}

	return p;
}

bool isdelim (char x) {
	if (x == '(' || x == ')' || x == '[' || x == ']' || x == '{' || x == '}') return true;
	else return false;
}

bool isbinop (char x) {
	if (x == '^' || x == '*' || x == '/' || x == '+' || x == '-') return true;
	else return false;
}

void recursiveBuild (char* exp, int beg, int end, Tree curNode, char *precList) {
	if (curNode == NULL) return;

	char op;
	int opPos;
	bool hasFoundOp = false;
	bool isOnParentheses = false;
	bool isOnBrackets = false;
	bool isOnBraces = false;

	for (int i = beg; i <= end; i++) {
		
		if (exp[i] == '\0') break;

		if (exp[i] == '(') {
			isOnParentheses = true;
		}

		else if (exp[i] == '[') {
			isOnBrackets = true;
		}

		else if (exp[i] == '{') {
			isOnBraces = true;
		}

		else if (exp[i] == ')') {
			isOnParentheses = false;
		}

		else if (exp[i] == ']') {
			isOnBrackets = false;
		}

		else if (exp[i] == '}') {
			isOnBraces = false;
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
			for (int i = beg, j = 0; i < end-beg+1; i++, j++) temp[j] = exp[i];
			temp[j] = '\0';

			insertNum(curNode, atof(temp));
			free(temp);
		}

	}

	return;
}







int main () {

	Tree expTree = newTree();
	char exp[] = "2.4/5.2";
	char precList[] = "^/*-+";

	recursiveBuild(exp, 0, strlen(exp)+1, expTree, precList);
	printTree(expTree);
	
	delTree(expTree);
	return 0;
}