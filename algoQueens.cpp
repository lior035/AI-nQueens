#include "algoQueens.h"

void NqueensAlgo::run()
{
	checkBoard * cb = new checkBoard();// buling up the check board
	int * num = new int;

	this->recoverAdd = cb;


	bool recv;

	recv = runHelper(cb);

	if (recv == true)
	{
		cout<<"board final:"<<endl;
		recoverAdd->printBoard();
		delete cb;
	}

	else
	{
		cout<<"error"<<endl;
		delete cb;
	}

}

//==========================================================================================================

bool NqueensAlgo::runHelper(checkBoard * curr)
{
	bool recvVal;
	matCellInfo* currMat;
	checkBoard * copyCheck;
	
	int* numFreeAtCol = new int;
	* numFreeAtCol = 0;

	currMat = curr->giveFreePlaceAtColumn(curr->giveLeftMostEmptyCol(),numFreeAtCol);

	if (currMat == NULL)
	{
		if (curr->giveLeftMostEmptyCol()>=curr->getSizeOfBoard()) // in this case the assignment has completed
			return true; 
		else if (*numFreeAtCol == 0)//numFreeAtCol == 0
			return false;
	}

	else
	{
		int i = 0;
		copyCheck = new checkBoard (curr);

		while (i<*numFreeAtCol)
		{
			curr->enterQueenToColumn(currMat[i].getCol(),currMat[i].getRow());
			curr->updateLeftMostEmptyCol();

			recvVal = this->runHelper(curr);

			if (recvVal == true)
			{
				delete copyCheck;
				return true;
			}

			else
			{
				//delete curr;
				checkBoard* container = new checkBoard (copyCheck);
				curr = container; //will initialize curr to the point before changing according to copyCheck
				this->recoverAdd = curr;
			}

			i++;
		}
		
		delete copyCheck;
		delete currMat;
		return false;
	}
}