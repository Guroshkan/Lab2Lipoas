#pragma once
#include"rule.h"
#include"grid.h"

class logic
{
	rule rules;
	int countNeighbour(grid, int, int);
public:
	logic(rule);
	grid nextGen(grid);
	static bool checkBorder(int, int, int);
};