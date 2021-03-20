#pragma once
#include <string>
#include <iostream>
#include <conio.h>

class Console
{
public:
	static void Write(std::string);
	static void WriteLine(std::string);
	static std::string ReadLine();
	static char GetChar();
	static int GetDigit();
	static int GetInt();

};