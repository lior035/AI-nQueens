#ifndef CHECK_BOARD
#define CHECK_BOARD

#include "matCellInfo.h"
#include <iostream> 
using namespace std;

class checkBoard
{
private:

	int ** board; //in each cell: 0 = false; 1= true; 2 = queen is assign
	int sizeBoard;
	int leftMostEmptyCol;

	void initializeToTrue();// will make all the array true
	void updateLegalPlacesAtBoard (int col, int row); // will update the bool array  according to the last queen assigned

public:

	checkBoard (); // constructor
	checkBoard (checkBoard * copyFrom); // copy constructor

	bool enterQueenToColumn(int col, int row); // if legal, will assgind the queen to this cordinates, and update the legal place of the board now, return true if the queen was assgined to this cordinate 
	
	matCellInfo* giveFreePlaceAtColumn (int col, int * numOfFree); // return array that indicate address of the legal places at the column, also return the number of legal places

	int giveLeftMostEmptyCol (); 
	bool updateLeftMostEmptyCol(); // true - there is more free colmun false otherwise

	int getSizeOfBoard ();
	int getValInBoardAt (int col, int row);

	int numOfLegalAccordingToAssgiment (int row, int col);


	void printBoard ();

	~checkBoard (); //destructor
};

#endif 
