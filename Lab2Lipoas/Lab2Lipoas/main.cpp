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
	Console::WriteLine("��������� ������������ ����� ���������� ���������� �������� ����� ������.");
	Console::WriteLine("��������� ������� ������� �����, ������� ������ 474 � ������ ������ ������������ ������ �� ���������� ������.");

	for (;;) 
	{
		int countX;
		int countY;
		try 
		{
			Console::WriteLine("������� ���������� ������ �� �����������. �� "
				+ std::to_string(BOTVALUE) + " �� " 
				+ std::to_string(TOPVALUE) + ".");
			countX = Console::GetInt();
			if (!logic::checkBorder(countX, BOTVALUE, TOPVALUE))
			{
				Console::WriteLine("����� �� ������������� �������. ��������� ����.");
				continue;
			}
			Console::WriteLine("������� ���������� ������ �� ���������. �� "
				+ std::to_string(BOTVALUE) + " �� "
				+ std::to_string(TOPVALUE) + ".");
			countY = Console::GetInt();
			if (!logic::checkBorder(countY, BOTVALUE, TOPVALUE))
			{
				Console::WriteLine("����� �� ������������� �������. ��������� ����.");
				continue;
			}
		}
		catch (std::invalid_argument ex)
		{
			Console::WriteLine(ex.what());
			Console::WriteLine("��������� �������.");
			continue;
		}
		int fillPart;
		for (;;) 
		{
			try 
			{
				Console::WriteLine("�������� ������� ��������� �������.");
				fillPart = Console::GetInt();
				if (!logic::checkBorder(fillPart, 0, 100))
				{
					Console::WriteLine("������� ���������� ����� ��������� �������� �� 0 �� 100. ��������� ����.");
					continue;
				}
				break;
			}
			catch (std::invalid_argument ex)
			{
				Console::WriteLine(ex.what());
				Console::WriteLine("��������� �������.");
				continue;
			}
		}
		rule rules = tuneRules();
		monitor mon(HEIGHT, WIDTH, countX, countY, rules, StandartSpeed, fillPart);
		mon.show();

		for (;;)
		{
			Console::WriteLine("�� ������ ����������?");
			Console::WriteLine("1 - ��. 2 - ���.");
			int userChoice = Console::GetDigit();
			switch (userChoice)
			{
			case Yes:
				break;
			case No:
				return 0;
			default:
				Console::WriteLine("������� ������ ���� �� ����������. ��������� ����.");
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
		Console::WriteLine("�� ������ ������� �� ����������� ��������?");
		Console::WriteLine("3 ������ - ������ ����������.");
		Console::WriteLine("2,3 ������ - ������ ��������.");
		Console::WriteLine("0,1,4,5,6,7,8 ������� - ������ �������.");
		Console::WriteLine("1 - ��. 2 - ���.");
		int userChoice = Console::GetDigit();
		std::vector<int> ruleBorn;
		std::vector<int> ruleSurvive;
		std::vector<int> ruleDie;
		switch (userChoice)
		{
		case Yes:
			return rule();
		case No:
			ruleBorn = fillRule("��������");
			ruleSurvive = fillRule("���������");
			ruleDie = fillRule("������");
			return rule(ruleBorn, ruleSurvive, ruleDie);
		default:
			Console::WriteLine("������� ������ ���� �� ����������. ��������� ����.");
			continue;
		}
		break;
	}
}

std::vector<int> fillRule(std::string mod)
{
	for(;;)
	{
		Console::WriteLine("������� ���������� ������� " + mod + ".0-9");
		int bornCountRules = Console::GetDigit();
		if (!logic::checkBorder(bornCountRules, 0, 9))
		{
			Console::WriteLine("����� �� ������������� �������. ��������� ����.");
			continue;
		}
		std::vector<int> ruleVec;
		for (int i = 0; i < bornCountRules; i++) 
		{
			Console::WriteLine("������� ���������� ������� ��� " + to_string(i+1) + " ������� " + mod + ".");
			int RuleValue = Console::GetDigit();
			if (!logic::checkBorder(RuleValue, 0, 8))
			{
				Console::WriteLine("����� �� ������������� �������. ��������� ����.");
				i--;
				continue;
			}
			bool ruleAlreadyExist = false;
			for (int j = 0; j < ruleVec.size(); j++)
			{
				if (ruleVec[j] == RuleValue)
				{
					Console::WriteLine("������ ������� " + mod + " ��� ������������ ��� ������� " + to_string(j+1) + "��������� ����.");
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
			Console::Write("�������� ������� " + mod + " �� ���������� ������� �������� ���:");
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