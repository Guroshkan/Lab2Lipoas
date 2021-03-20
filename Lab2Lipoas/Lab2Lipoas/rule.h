#pragma once
#include<vector>

class rule
{
public:
	std::vector<int> born;
	std::vector<int> survive;
	std::vector<int> die;
	rule(std::vector<int> born, std::vector<int> survive, std::vector<int> die) {
		this->born = born;
		this->survive = survive;
		this->die = die;
	}
	rule() {
		this->born = std::vector<int>{3};
		this->survive = std::vector<int>{2,3};
		this->die = std::vector<int>{0,1,4,5,6,7,8};
	}
};