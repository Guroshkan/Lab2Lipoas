#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include"grid.h"
#include <fstream>
#include <filesystem>
#include "Console.h"
enum userYoN { Yes = 1, No };
enum ModOpenFile { Write = true, Read = false };
namespace fs = std::filesystem;
class File
{
public:
	static void saveMatrix(int, int, int, int, grid);
	static grid loadMatrix();
	static std::vector<std::string> split(std::string,char);
	static std::string getMessage(std::string);
	static std::string getCorrectPath(bool);
	static bool isFileExist(std::string);
	static bool isFileReadOnly(std::string);
	static bool canBeCreate(std::string);
};