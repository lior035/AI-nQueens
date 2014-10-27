#include "checkBoard.h" 

checkBoard::checkBoard()
{
	int i;

	//initializing objects member

	cout<<"Enter size of the check board please"<<endl; 
	cin>>this->sizeBoard;

	int bSize = this->sizeBoard;

	this->board = new int * [bSize];
		
	for(i=0;i<bSize;i++)
	{
		this->board[i] = new int [bSize];
	}

	this->leftMostEmptyCol = 0;

	//make the bool array true
	this->initializeToTrue();
}

//-----------------------------------------------------------------

void checkBoard::initializeToTrue()
{
	int i, j;

	for ( i = 0; i<this->sizeBoard; i++)
	{
		for (j= 0; j<this->sizeBoard; j++)
			this->board[i][j] = 1;
	}
}

//-----------------------------------------------------------------

void checkBoard::updateLegalPlacesAtBoard(int col, int row)
{
	//this function get the place in which the queen was assigned to and according to it update the bool array of the board
	int i, j;

	this->board[row][col] = 2; //this cell is assaignd with a queen

	//updating same col of the queen as false
	for (i=0; i<this->sizeBoard; i++)
	{
		if (this->board[i][col] != 2) // the place in which the current queen is assgined
			this->board[i][col] = 0; // place mark as false
	}

	//updating same row of the queen as false
	for (j = 0; j<this->sizeBoard; j++)
	{
		if (this->board[row][j] != 2)
			this->board[row][j] = 0;
	}

	//updating both hypotenuses of this queen to be false

	i = row;
	j = col;

	while ((i>=0)&&(j>=0))
	{
		if (this->board[i][j] != 2)
			this->board[i][j] = 0;
			
		i--;
		j--;	
	}

	i = row;
	j = col;

	while ((i<this->sizeBoard)&&(j<this->sizeBoard))
	{
		if (this->board[i][j] != 2)
			this->board[i][j] = 0;
			
		i++;
		j++;
		
	}

	i = row;
	j = col;

	while ((i>=0)&&(j<this->sizeBoard))
	{
		if (this->board[i][j] != 2)
			this->board[i][j] = 0;
			
		i--;
		j++;
		
	}

	i = row;
	j = col;

	while ((i<this->sizeBoard)&&(j>=0))
	{
		if (this->board[i][j] != 2)
			this->board[i][j] = 0;
			
		i++;
		j--;
		
	}
}

//-------------------------------------------------------------------------------

checkBoard::checkBoard(checkBoard* source)
{
	this->sizeBoard = source->getSizeOfBoard();
	int ** b = new int * [this->sizeBoard];

	int i;
	for (i=0; i<this->sizeBoard; i++)
		b[i] = new int [this->sizeBoard];

	int k = 0;
	for (i =0; i<this->sizeBoard; i++)
	{
		for(k=0;k<this->sizeBoard; k++)
		{
			int number = source->getValInBoardAt(i,k);
			if (number != -1)
				b[i][k] = number ;
			else
				exit(1);
		}
	}
	this->board = b;
	this->leftMostEmptyCol = source->giveLeftMostEmptyCol();
}

//================================================================================

bool checkBoard::enterQueenToColumn(int col, int row)
{
	if (this->board[row][col] == 1)
	{
		this->board[row][col] = 2;
		this->updateLegalPlacesAtBoard(col, row);

		return true;
	}

	return false;
}

//================================================================================

matCellInfo * checkBoard::giveFreePlaceAtColumn (int col, int * numOfFree)
{
	* numOfFree = 0;
	matCellInfo * legalPlaceAtCol;
	int i,j;

	if ((col<0)||(col>=this->getSizeOfBoard()))
	{
		legalPlaceAtCol = NULL;
		return legalPlaceAtCol;
	}

	for (i = 0; i<this->sizeBoard;i++)
	{
		if (this->board[i][col] == 1) // legal place
		{
			int num = *numOfFree;
			num++;
			*numOfFree = num;
		}
	}

	if (*numOfFree ==0)
	{
		legalPlaceAtCol = NULL;
		return legalPlaceAtCol;
	}

	else
	{
		legalPlaceAtCol = new matCellInfo[*numOfFree];
		int k = 0;

		int * priority = new int [*numOfFree];

		for (i = 0; i<this->sizeBoard;i++)
		{
			if (this->board[i][col] == 1) // legal place
			{
				legalPlaceAtCol[k].updateCellCords(col,i);
				priority[k] = this->numOfLegalAccordingToAssgiment( i,  col);
				k++;
			}
		}

		for(i = 0; i<*numOfFree;i++)
		{
			for (j = i+1; j<*numOfFree; j++)
			{
				if (priority[i]>priority[j])
				{
					int save;
					save = priority[j];
					priority[j] = priority[i];
					priority[i] = save;

					int saveR, saveC;

					saveR = legalPlaceAtCol[i].getRow();
					saveC = legalPlaceAtCol[i].getCol();

					legalPlaceAtCol[i].updateCellCords(legalPlaceAtCol[j].getCol(),legalPlaceAtCol[j].getRow());
					legalPlaceAtCol[j].updateCellCords(saveC,saveR);
				}
			}
		}

		delete priority;
		return legalPlaceAtCol;
	}
}

//==============================================================================

int checkBoard::numOfLegalAccordingToAssgiment(int row, int col)
{
	int counter = 0;
	int k,r;

	for (r= col++; r<this->getSizeOfBoard();r++)
	{
		if (this->getValInBoardAt(row,r) == 1)
			counter++;
	}

	for (k = row++; k<this->getSizeOfBoard();k++)
	{
		if (this->getValInBoardAt(k,col) == 1)
			counter++;
	}

	r = row++;
	k = col++;

	while((r<this->getSizeOfBoard())&&(k<this->getSizeOfBoard()))
	{
		if (this->getValInBoardAt(r,k)==1)
			counter++;
		r++;
		k++;
	}

	r = row--;
	k = col++;

	while ((r>=0)&&(k<this->getSizeOfBoard()))
	{
		if (this->getValInBoardAt(r,k) == 1)
			counter++;
		r--;
		k++;
	}

	return counter;
}
//==============================================================================

bool checkBoard::updateLeftMostEmptyCol()
{
	this->leftMostEmptyCol +=1;
	if (this->leftMostEmptyCol < this->sizeBoard)
		return true;
	else 
		return false; //no more free col
}

//==============================================================================

int checkBoard::giveLeftMostEmptyCol()
{
	return this->leftMostEmptyCol;
}

//==============================================================================

int checkBoard::getSizeOfBoard()
{
	return this->sizeBoard;
}

//=============================================================================

int checkBoard::getValInBoardAt(int row, int col)
{
	if ((row>=0)&&(row<this->getSizeOfBoard())&&(col>=0)&&(col<this->getSizeOfBoard()))
		return this->board[row][col];
	return -1;
}

//==============================================================================

void checkBoard::printBoard ()
{
	int i, j;
	int k = 0;

	matCellInfo* mc = new matCellInfo [this->getSizeOfBoard()];

	cout<<"Here is the assigment : "<<endl;

	for (i=0;i<this->sizeBoard;i++)
	{
		for (j=0; j<this->sizeBoard;j++)
		{
			if (this->board[i][j] == 2)
			{
				cout<<"Q  ";//cout<<"("<<i<<","<<j<<")  ";
				mc[k++].updateCellCords(j,i);
			}

			else
				cout<<"E  ";
		}
		cout<<endl;
	}
	
	cout<<endl;
	cout<<"Shell you prefer the assgiment as a list: "<<endl;
	for (k = 0; k<this->getSizeOfBoard(); k++)
		cout<<"Queen "<<k+1<<" : ("<<mc[k].getRow()<<","<<mc[k].getCol()<<")."<<endl;

	delete mc;
}

//=============================================================================

checkBoard::~checkBoard()
{
	int i;

	for(i=0;i<this->sizeBoard;i++)
		delete this->board[i];
	
	delete this->board;
}