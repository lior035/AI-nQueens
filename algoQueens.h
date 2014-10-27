#ifndef ALGO
#define ALGO

#include "CheckBoard.h"
#include <iostream> 
using namespace std; 

class NqueensAlgo
{
private:
	bool runHelper(checkBoard * curr);
	checkBoard* recoverAdd;

public:
	void run();
};

#endif 