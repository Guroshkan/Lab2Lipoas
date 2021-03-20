#include "cell.h"

cell::cell(int sizeX = 10, int sizeY = 10)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->alive = false;
}
