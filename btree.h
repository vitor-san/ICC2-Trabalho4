#ifndef BTREE_H
	#define BTREE_H
	
	typedef union x Elem;
	typedef struct node NODE;
	typedef NODE* Node;
	typedef Node Tree;

	Tree newTree();
	void insertOper(Tree, char);
	void insertNumber(Tree, double);
	int isLeaf(Node);
	void delTree(Tree);

#endif