#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct snode {
	char *str;
	int strlen;
	sNode next;
};

struct stack {
	sNode top;
};

sNode newNode() {
	sNode new = malloc(sizeof(SNODE));

	new->str = NULL;
	new->strlen = 0;
	new->next = NULL;

	return new;
}

void freeNode(sNode x) {
	free(x->str);
	free(x);

	return;
}

void printNode(sNode N) {
	puts(N->str);
	
	return;
}

Stack newStack() {
	Stack new = malloc(sizeof(STACK));
	
	new->top = NULL;

	return new;
}

int push(Stack S, char* str) {
	if (str == NULL) return 0;

	if (isEmpty(S)) {
		S->top = newNode();
		S->top->strlen = strlen(str);
		S->top->str = malloc((strlen(str)+1)*sizeof(char));
		strcpy(S->top->str, str);
	}

	else {
		sNode aux = newNode();
		aux->strlen = strlen(str);
		aux->str = malloc((strlen(str)+1)*sizeof(char));
		strcpy(aux->str, str);
		aux->next = S->top;
		S->top = aux;
	}

	return 1;
}

char *pop(Stack S) {
	if (isEmpty(S)) return NULL;

	char *info = S->top->str;
	sNode prev = S->top;
	S->top = S->top->next;
	freeNode(prev);

	return info;
}

char *top(Stack S) {
	if (isEmpty(S)) return NULL;

	return S->top->str;
}

int isEmpty(Stack x) {
	return (x->top == NULL);
}

void printStack(Stack S) {
	sNode aux = S->top;
	while (aux != NULL) {
		printNode(aux);
		aux = aux->next;
	}

	return;
}

void deleteStack(Stack x) {
	while (!isEmpty(x)) pop(x);
	free(x);

	return;
}