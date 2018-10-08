#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct snode {
	char c;
	sNode next;
};

struct stack {
	sNode top;
};

sNode newNode() {
	sNode new = malloc(sizeof(SNODE));

	new->c = 0;
	new->next = NULL;

	return new;
}

void freeNode(sNode x) {
	free(x);

	return;
}

void printNode(sNode N) {
	printf("%c\n", N->c);
	
	return;
}

Stack newStack() {
	Stack new = malloc(sizeof(STACK));
	
	new->top = NULL;

	return new;
}

void push(Stack S, char ch) {

	if (isEmpty(S)) {
		S->top = newNode();
		S->top->c = ch;
	}

	else {
		sNode aux = newNode();
		aux->c = ch;
		aux->next = S->top;
		S->top = aux;
	}

	return;
}

char pop(Stack S) {
	if (isEmpty(S)) return '\n';

	char info = S->top->c;
	sNode prev = S->top;
	S->top = S->top->next;
	freeNode(prev);

	return info;
}

char top(Stack S) {
	if (isEmpty(S)) return '\n';

	return S->top->c;
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