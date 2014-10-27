#ifndef stck
#define stck
#include "matCellInfo.h"

class Stack 
{
   int MaxStack;
   int EmptyStack;
   int top;
   matCellInfo* items;

public:
   Stack(int);
   ~Stack();
   void push(int col, int row);
   void pop(int* col, int* row);
   int empty();
   int full();
};
#endif