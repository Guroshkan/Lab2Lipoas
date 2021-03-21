#include <SFML/Graphics.hpp>
#include <random>
#include "monitor.h"
#include "Console.h"
using namespace sf;

int HEIGHT = 900;
int WIDTH = 900;
const int BOTVALUE = 5;
const int TOPVALUE = 50;
const int StandartSpeed = 100;

enum RuleInput { Conway = 1, KeyboardInput, FileInput };
rule showRules();
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
		rule rules = showRules();
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

rule showRules() 
{
	rule rules = tuneRules();
	if (rules.born.size() > 0&&rules.survive.size()>0)
	{
		Console::Write("Конечное условие рождения по количеству соседей выглядит так:");
		Console::Write(to_string(rules.born[0]));
		for (int i = 1; i < rules.born.size(); i++)
		{
			Console::Write(", " + to_string(rules.born[i]));
		}
		Console::WriteLine("");
		Console::Write("Конечное условие выживания по количеству соседей выглядит так:");
		Console::Write(to_string(rules.survive[0]));
		for (int i = 1; i < rules.survive.size(); i++)
		{
			Console::Write(", " + to_string(rules.survive[i]));
		}
		Console::WriteLine("");
	}
	return rules;
}

rule tuneRules()
{
	for (;;)
	{
		Console::WriteLine("По каким правилам вы хотите сыграть?");
		Console::WriteLine("1 - Стандартныее правила Conway Game. 2 - Ввести правила вручную с клавиатуры. 3 - Загрузить правила из файла.");
		int userChoice = Console::GetDigit();
		std::vector<int> ruleBorn;
		std::vector<int> ruleSurvive;
		std::vector<int> ruleDie;
		rule rules;
		switch (userChoice)
		{
		case Conway:
			return rule();
		case KeyboardInput:
			ruleBorn = fillRule("рождения");
			ruleSurvive = fillRule("выживания");
			rules = rule(ruleBorn, ruleSurvive);
			for (;;)
			{
				Console::WriteLine("Вы хотите сохранить свои правила?");
				Console::WriteLine("1 - Да. 2 - Нет.");
				int userChoiceSave = Console::GetDigit();
				switch (userChoiceSave)
				{
				case Yes:File::saveRules(rules); break;
				case No:
					break;
				default:
					Console::WriteLine("Данного пункта меню не существует. Повторите ввод.");
					continue;
				}
				break;
			}
			return rules;
		case FileInput:
			try
			{
				return File::loadRules();
			}
			catch (invalid_argument ex)
			{
				Console::WriteLine(ex.what());
				Console::WriteLine("Повторите ввод");
				continue;
			}
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
		if (!logic::checkBorder(bornCountRules, lowBoardNeighbour, maxBoardNeighbour+1))
		{
			Console::WriteLine("Число не соответствует границе. Повторите ввод.");
			continue;
		}
		std::vector<int> ruleVec;
		for (int i = 0; i < bornCountRules; i++) 
		{
			Console::WriteLine("Введите количество соседей для " + to_string(i+1) + " условия " + mod + ".");
			int RuleValue = Console::GetDigit();
			if (!logic::checkBorder(RuleValue, lowBoardNeighbour, maxBoardNeighbour))
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
		return ruleVec;
	}
}