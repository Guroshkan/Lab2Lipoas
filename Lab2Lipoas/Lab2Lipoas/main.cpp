#include <SFML/Graphics.hpp>
#include <random>
#include "monitor.h"
#include "Console.h"
using namespace sf;

int HEIGHT = 900;
int WIDTH = 900;
int sizeCellX = 40;
int sizeCellY = 40;
int heightPoint = 20;
const int BOTVALUE = 5;
const int TOPVALUE = 50;
const int StandartSpeed = 100;

rule tuneRules();
std::vector<int> fillRule(std::string);

int main()
{
	setlocale(LC_ALL, "Russian");
	Console::WriteLine("Программа представляет собой реализацию клеточного автомата Джона Конвея.");
	Console::WriteLine("Программу написал Гумеров Роман, студент группы 474 в рамках второй лабораторной работы по дисциплине ЛИПОАС.");

	for (;;) 
	{
		int countX;
		int countY;
		try 
		{
			Console::WriteLine("Введите количество клеток по горизонтали. От "
				+ std::to_string(BOTVALUE) + " до " 
				+ std::to_string(TOPVALUE) + ".");
			countX = Console::GetInt();
			if (!logic::checkBorder(countX, BOTVALUE, TOPVALUE))
			{
				Console::WriteLine("Число не соответствует границе. Повторите ввод.");
				continue;
			}
			Console::WriteLine("Введите количество клеток по вертикали. От "
				+ std::to_string(BOTVALUE) + " до "
				+ std::to_string(TOPVALUE) + ".");
			countY = Console::GetInt();
			if (!logic::checkBorder(countY, BOTVALUE, TOPVALUE))
			{
				Console::WriteLine("Число не соответствует границе. Повторите ввод.");
				continue;
			}
		}
		catch (std::invalid_argument ex)
		{
			Console::WriteLine(ex.what());
			Console::WriteLine("Повторите попытку.");
			continue;
		}
		int fillPart;
		for (;;) 
		{
			try 
			{
				Console::WriteLine("Выберите процент заполения матрицы.");
				fillPart = Console::GetInt();
				if (!logic::checkBorder(fillPart, 0, 100))
				{
					Console::WriteLine("Процент заполнения может принимать значения от 0 до 100. Повторите ввод.");
					continue;
				}
				break;
			}
			catch (std::invalid_argument ex)
			{
				Console::WriteLine(ex.what());
				Console::WriteLine("Повторите попытку.");
				continue;
			}
		}
		rule rules = tuneRules();
		monitor mon(HEIGHT, WIDTH, countX, countY, rules, StandartSpeed, fillPart);
		mon.show();

		for (;;)
		{
			Console::WriteLine("Вы хотите продолжить?");
			Console::WriteLine("1 - Да. 2 - Нет.");
			int userChoice = Console::GetDigit();
			switch (userChoice)
			{
			case Yes:
				break;
			case No:
				return 0;
			default:
				Console::WriteLine("Данного пункта меню не существует. Повторите ввод.");
				continue;
			}
			break;
		}
	}
	return 0;
}



rule tuneRules()
{
	for (;;)
	{
		Console::WriteLine("Вы хотите сыграть по стандартным правилам?");
		Console::WriteLine("3 соседа - клетка появляется.");
		Console::WriteLine("2,3 соседа - клетка выживает.");
		Console::WriteLine("0,1,4,5,6,7,8 соседей - клетка умирает.");
		Console::WriteLine("1 - Да. 2 - Нет.");
		int userChoice = Console::GetDigit();
		std::vector<int> ruleBorn;
		std::vector<int> ruleSurvive;
		std::vector<int> ruleDie;
		switch (userChoice)
		{
		case Yes:
			return rule();
		case No:
			ruleBorn = fillRule("рождения");
			ruleSurvive = fillRule("выживания");
			ruleDie = fillRule("смерти");
			return rule(ruleBorn, ruleSurvive, ruleDie);
		default:
			Console::WriteLine("Данного пункта меню не существует. Повторите ввод.");
			continue;
		}
		break;
	}
}

std::vector<int> fillRule(std::string mod)
{
	for(;;)
	{
		Console::WriteLine("Введите количество условий " + mod + ".0-9");
		int bornCountRules = Console::GetDigit();
		if (!logic::checkBorder(bornCountRules, 0, 9))
		{
			Console::WriteLine("Число не соответствует границе. Повторите ввод.");
			continue;
		}
		std::vector<int> ruleVec;
		for (int i = 0; i < bornCountRules; i++) 
		{
			Console::WriteLine("Введите количество соседей для " + to_string(i+1) + " условия " + mod + ".");
			int RuleValue = Console::GetDigit();
			if (!logic::checkBorder(RuleValue, 0, 8))
			{
				Console::WriteLine("Число не соответствует границе. Повторите ввод.");
				i--;
				continue;
			}
			bool ruleAlreadyExist = false;
			for (int j = 0; j < ruleVec.size(); j++)
			{
				if (ruleVec[j] == RuleValue)
				{
					Console::WriteLine("Данное правило " + mod + " уже присутствует под номером " + to_string(j+1) + "Повторите ввод.");
					ruleAlreadyExist = true;
					break;
				}
			}
			if (ruleAlreadyExist)
			{
				i--;
				continue;
			}
			else
			{
				ruleVec.push_back(RuleValue);
			}
		}
		if (ruleVec.size() > 0)
		{
			Console::Write("Конечное условие " + mod + " по количеству соседей выглядит так:");
			Console::Write(to_string(ruleVec[0]));
			for (int i = 1; i < ruleVec.size(); i++)
			{
				Console::Write(", " + to_string(ruleVec[i]));
			}
			Console::WriteLine("");
		}
		return ruleVec;
	}
}