#include "stack.h"


Stack::Stack(int size) 
{
   MaxStack = size;
   EmptyStack = -1;
   top = EmptyStack;
   items = new matCellInfo[MaxStack];
}

Stack::~Stack() 
{
	delete items;
}

void Stack::push(int col, int row)
{
	items[++top].updateCellCords(col,row);
}

void Stack::pop(int * col, int* row)
{
	*col = items[top].getCol();
	*row = items[top].getRow();
    items[top--];
}

int Stack::full()
{
   return top + 1 == MaxStack;
}

int Stack::empty() 
{
   return top == EmptyStack;
}