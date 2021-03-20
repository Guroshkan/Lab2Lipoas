#include "grid.h"

grid::grid(int countX, int countY, int sizeCellX,int sizeCellY)
{
	/*int maxGridSize = sizeX > sizeY ? sizeX : sizeY;
	int minMonitorSize = sizeMonitorX < sizeMonitorY ? sizeMonitorX : sizeMonitorY;
	int sizeSell = minMonitorSize / maxGridSize;*/
	this->sizeCellX = sizeCellX;
	this->sizeCellY = sizeCellY;
	this->countX = countX;
	this->countY = countY;
	for (int i = 0; i < countX; i++)
	{
		std::vector<cell>row;
		for (int j = 0; j < countY; j++)
		{
			cell c = cell(sizeCellX,sizeCellY);
			row.push_back(c);
		}
		field.push_back(row);
	}
}

grid::grid()
{
	for (int i = 0; i < 10; i++)
	{
		std::vector<cell>row;
		for (int j = 0; j < 10; j++)
		{
			cell c = cell(10,10);
			row.push_back(c);
		}
		field.push_back(row);
	}
}
