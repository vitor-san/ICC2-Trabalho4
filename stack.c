#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct snode {
	int n;
	sNode next;
};

struct stack {
	sNode top;
};

sNode newNode() {
	sNode new = malloc(sizeof(SNODE));

	new->n = 0;
	new->next = NULL;

	return new;
}

void freeNode(sNode x) {
	free(x);

	return;
}

void printNode(sNode x) {
	printf("%d\n", x->n);

	return;
}

Stack newStack() {
	Stack new = malloc(sizeof(STACK));
	
	new->top = NULL;

	return new;
}

void push(Stack S, int num) {

	if (isEmpty(S)) {
		S->top = newNode();
		S->top->n = num;
	}

	else {
		sNode aux = newNode();
		aux->n = num;
		aux->next = S->top;
		S->top = aux;
	}

	return;
}

int pop(Stack S) {
	if (isEmpty(S)) return -1;

	int info = S->top->n;
	sNode prev = S->top;
	S->top = S->top->next;
	freeNode(prev);

	return info;
}

int top(Stack S) {
	if (isEmpty(S)) return -1;

	return S->top->n;
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