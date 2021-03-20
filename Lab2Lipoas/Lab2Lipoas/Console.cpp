#include "Console.h"

void Console::Write(std::string str)
{
	std::cout << str << ' ';
}

void Console::WriteLine(std::string str="")
{
	std::cout << str << std::endl;
}

std::string Console::ReadLine()
{
	std::string str;
	std::getline(std::cin, str);
	return str;
}

char Console::GetChar()
{
	char ch;
	ch = _getche();
	std::cin.clear();
	return ch;
}

int Console::GetDigit()
{
	for (;;)
	{
		char ch;
		ch = _getche();
		WriteLine();
		std::cin.clear();
		if (std::isdigit(ch))
			return ch - '0';
		else
		{
			WriteLine("Неверный ввод, введите цифру.");
		}
	}
}

int Console::GetInt()
{
	std::string integerStr;
	std::getline(std::cin, integerStr);
	//std::cin >> integerStr;
	if (integerStr.size() == 0) {
		std::cin.clear();
		throw std::invalid_argument("Неверный ввод числа. Строка не может быть пустой.");
	}
	for (int i = 0; i < integerStr.size(); i++) {
		if (!std::isdigit(integerStr[i]))
		{
			std::cin.clear();
			throw std::invalid_argument("Неверный ввод числа.");
		}
	}
	int integer = std::stoi(integerStr);
	return integer;
}