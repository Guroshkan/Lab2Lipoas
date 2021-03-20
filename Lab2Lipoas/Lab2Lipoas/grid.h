#pragma once
#include <vector>
#include "cell.h"

class grid
{
public:
	int countX;
	int countY;
	int sizeCellX;
	int sizeCellY;
	std::vector<std::vector<cell>> field;
	grid(int, int,int,int);
	grid();
};