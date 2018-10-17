#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

union x {
	double nbr;
	char opr;
};

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

void insertOper(Tree, char) {

	return;
}

void insertNumber(Tree, double) {


	return;
}

int isLeaf(Node) {




}


void delTree (Tree t) {
	if (t == NULL) return;

	delTree(t->left);
	delTree(t->right);
	delNode(t);

	return;
}