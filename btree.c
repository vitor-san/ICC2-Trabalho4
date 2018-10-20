#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

typedef union x {
	double nbr;
	char opr;
} Elem;

struct node {
	Elem info;
	int isLeaf;
	Node left;
	Node right;
};

Node newtNode () {
	Node new = malloc(sizeof(NODE));
	new->info.opr = ' ';
	new->left = NULL;
	new->right = NULL;
	new->isLeaf = 0;
	return new;
}

Tree newTree () {
	return newtNode();
}

void insertOper (Tree node, char c) {
	if (node == NULL) return;

	if (node->left == NULL && node->right == NULL) {
		
		node->info.opr = c;
		node->left = newtNode();
		node->right = newtNode();
		return;
	}

	else if (node->left == NULL) {
		node->info.opr = c;
		node->left = newtNode();
		return;
	}

	else if (node->right == NULL) {
		node->info.opr = c;
		node->right = newtNode();
		return;
	}
}

void insertNum (Tree node, double n) {
	if (node == NULL) return;

	if (node->left == NULL && node->right == NULL) {
		
		node->info.nbr = n;
		node->isLeaf = 1;
		return;
	}

	else if (node->left == NULL) {
		node->info.nbr = n;
		node->isLeaf = 1;
		return;
	}

	else if (node->right == NULL) {
		node->info.nbr = n;
		node->isLeaf = 1;
		return;
	}
}

char getOper (Node x) {
	return x->info.opr;
}

double getNum (Node x) {
	return x->info.nbr;
}

Node getLeft (Node x) {
	return x->left;
}

Node getRight (Node x) {
	return x->right;
}

int isLeaf (Node x) {
	return x->isLeaf;
}

void printTree (Tree n) {
	if (n == NULL) return;

	printTree(n->left);
	printTree(n->right);

	if (n->isLeaf) printf("O valor eh: %0.2lf\n", n->info.nbr);
	else printf("O valor eh: %c\n", n->info.opr);

	return;
}

void delTree (Tree t) {
	if (t == NULL) return;

	delTree(t->left);
	delTree(t->right);
	free(t);

	return;
}