#include "matCellInfo.h"

matCellInfo::matCellInfo()
{
	this->row = -1;
	this->col = -1;
}

void matCellInfo::updateRow (int r)
{
	this->row = r;
}

void matCellInfo::updateCol (int c)
{
	this->col = c;
}

void matCellInfo::updateCellCords (int c, int r)
{
	this->updateCol(c);
	this->updateRow(r);
}

int matCellInfo::getCol()
{
	return this->col;
}

int matCellInfo::getRow()
{
	return this->row;
}