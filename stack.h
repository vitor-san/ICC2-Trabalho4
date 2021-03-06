#ifndef STACK_H
	#define STACK_H
	
	typedef struct snode SNODE;
	typedef SNODE* sNode;
	typedef struct stack STACK;
	typedef STACK* Stack;

	Stack newStack();
	void push(Stack, char);
	char pop(Stack);	//returns '\n' when there is nothing left to pop
	char top(Stack);	//doesn't pop out the information; returns '\n' when there is nothing left to pop
	int isEmpty(Stack);
	void printStack(Stack);
	void delStack(Stack);

#endif