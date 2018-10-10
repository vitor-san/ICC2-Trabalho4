#ifndef BTREE_H
	#define BTREE_H
	
	typedef struct tnode TNODE;
	typedef TNODE* tNode;
	typedef struct btree TREE;
	typedef TREE* Tree;

	Tree newTree();
	void delTree(Tree);

#endif