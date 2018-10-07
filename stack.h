#ifndef STACK_H
	#define STACK_H
	
	typedef struct snode SNODE;
	typedef SNODE* sNode;
	typedef struct stack STACK;
	typedef STACK* Stack;

	Stack newStack();
	int push(Stack, char*);		//returns 0 in case of error
	char *pop(Stack);	//returns NULL when there is nothing left to pop
	char *top(Stack);	//doesn't pop out the information; returns NULL when there is nothing left to pop
	int isEmpty(Stack);
	void printStack(Stack);
	void deleteStack(Stack);

#endif