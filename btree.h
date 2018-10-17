#ifndef BTREE_H
	#define BTREE_H
	
	typedef struct node NODE;
	typedef NODE* Node;
	typedef Node Tree;

	Tree newTree();
	void insertOper(Tree, char);
	void insertNum(Tree, double);
	char getOper(Node);
	double getNum(Node);
	Node getLeft(Node);
	Node getRight(Node);
	int isLeaf(Node);
	void printTree(Tree);
	void delTree(Tree);

#endif