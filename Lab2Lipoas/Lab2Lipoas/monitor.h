#pragma once
#include <SFML/Graphics.hpp>
#include "cell.h"
#include "grid.h"
#include "Logic.h"
#include "File.h"
#include <random>
using namespace sf;

class monitor
{
	int HEIGHT;
	int WIDTH;
	int countX;
	int countY;
	grid matrix;
	rule rules;
	bool pause;
	int delay;
	int fill;
public:
	monitor(int, int,int,int,rule,int,int);
	void show();
};