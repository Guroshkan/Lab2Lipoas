#pragma once
#include<vector>
enum boardNeighbour{lowBoardNeighbour = 0,maxBoardNeighbour = 8};
class rule
{
public:
	std::vector<int> born;
	std::vector<int> survive;
	rule(std::vector<int> born, std::vector<int> survive) {
		this->born = born;
		this->survive = survive;
	}
	rule() {
		this->born = std::vector<int>{3};
		this->survive = std::vector<int>{2,3};
	}
};