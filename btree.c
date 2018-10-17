#include <stdlib.h>
#include <stdio.h>
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

Node newNode () {
	Node new = malloc(sizeof(NODE));
	new->info.nbr = 0;
	new->left = NULL;
	new->right = NULL;
	new->isLeaf = 0;
	return new;
}

void delNode (Node x) {
	if (x == NULL) return;
	
	if (x->left == NULL && x->right == NULL) {
		free(x);
		return;
	}
	
	delNode(x->left);
	delNode(x->right);
	free(x);

	return;
}

Tree newTree () {
	return newNode();
}

void insertOper (Tree node, char c) {
	if (node == NULL) return;

	if (node->left == NULL && node->right == NULL) {
		
		node->info.opr = c;
		node->left = newNode();
		node->right = newNode();
		return;
	}

	else {
		node->info.opr = c;
		return;
	}
}

void insertNum (Tree node, double n) {
	if (node == NULL) return;

	if (node->left == NULL && node->right == NULL) {
		
		node->info.nbr = n;
		node->isLeaf = 1;
		node->left = newNode();
		node->right = newNode();
		return;
	}

	else {
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

	if (n->isLeaf) printf("%0.2lf\n", n->info.nbr);
	else printf("%c\n", n->info.opr);

	return;
}

void delTree (Tree t) {
	if (t == NULL) return;

	delTree(t->left);
	delTree(t->right);
	delNode(t);

	return;
}