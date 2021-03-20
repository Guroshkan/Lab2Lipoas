#include "Logic.h"
#include <iostream>
logic::logic(rule r)
{
	this->rules = r;
}

grid logic::nextGen(grid matrix)
{
	grid newMatrix(matrix.countX,matrix.countY,matrix.sizeCellX,matrix.sizeCellY);
	for (int i = 0; i < newMatrix.field.size(); i++)
	{
		for (int j = 0; j < newMatrix.field[i].size(); j++)
		{
			newMatrix.field[i][j].alive = false;
		}
	}
	for (int i = 0; i < matrix.field.size(); i++)
	{
		for (int j = 0; j < matrix.field[i].size(); j++) 
		{
			int countOfNeighbour = this->countNeighbour(matrix, i, j);
			if (!matrix.field[i][j].alive)//если клетка мертва - смотрим модет ли она появиться
			{
				for (int r = 0; r < rules.born.size(); r++)
				{
					if (countOfNeighbour == rules.born[r])
					{
						newMatrix.field[i][j].alive = true;
						break;
					}
				}
					continue;
			}
			else //иначе если она жива
			{
				for (int r = 0; r < rules.survive.size(); r++)
				{
					if (countOfNeighbour == rules.survive[r])//она выживает. проверка на смерть не требуется(вроде как)так как она мертва внутри
					{
						newMatrix.field[i][j].alive = true;
						break;
					}
				}
				continue;
			}
		}
	}
	return newMatrix;
}

bool logic::checkBorder(int a, int b, int c)
{
	return a>=b&&a<=c;
}

int logic::countNeighbour(grid matrix, int x, int y)
{
	int result = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (j == y && i == x) { continue; }
			int curri = i;
			int currj = j;
			if (i < 0)
				curri = matrix.field.size() - 1;
			if (i == matrix.field.size())
				curri = 0;
			if (j < 0)
				currj = matrix.field[0].size() - 1;
			if (j == matrix.field[0].size())
				currj = 0;
			if (matrix.field[curri][currj].alive)//IndexOutOfRangeException
			{
				result++;
			}
		}
	}
	return result;
}
