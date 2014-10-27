#ifndef MATINFO
#define MATINFO

#include <iostream> 
using namespace std;

class matCellInfo
{
private:
	int row, col;

public:
	matCellInfo();
	void updateRow (int r);
	void updateCol (int c);
	void updateCellCords (int c, int r);

	int getRow();
	int getCol();
};

#endif 
