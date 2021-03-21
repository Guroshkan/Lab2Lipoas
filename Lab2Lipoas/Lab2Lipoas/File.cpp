#include "File.h"

void File::saveMatrix(int h,int w,int countX,int countY,grid matrix)
{
	Console::WriteLine("Вы хотите сохранить матрицу в файл.");
	std::string filePath = getCorrectPath(Write);
	std::ofstream f;
	f.open(filePath);
	f << h << ' ' << w << ' ' << countX << ' ' << countY << '\n';
	for (int i = 0; i < countY; i++)
	{
		for (int j = 0; j < countX; j++)
		{
			if (matrix.field[j][i].alive)
				f << "1 ";
			else
				f << "0 ";
		}
		f << '\n';
	}
	f << '\0';
	f.close();
}

grid File::loadMatrix()
{
	Console::WriteLine("Вы хотите загрузить матрицу их файла.");
	std::string filePath = getCorrectPath(Read);
	std::string line1 = getMessage(filePath);
	std::vector<std::string> lineVec = split(line1, '\n');
	std::vector<std::string> valueStrVec = split(lineVec[0],' ');
	std::vector<int> valueVec;
	for (int i = 0; i < valueStrVec.size(); i++)//проверяем параметры
	{
		if (valueStrVec[i].size() == 0) {
			std::cin.clear();
			throw std::invalid_argument("Неверное содержание файла. Несоответсвие количества аргументов.");
		}
		for (int j = 0; j < valueStrVec[i].size(); j++) {
			if (!std::isdigit(valueStrVec[i][j]))
			{
				throw std::invalid_argument("Неверное содержание файла. Несоответсвие типов аргументов.");
			}
		}
		try
		{
			valueVec.push_back(std::stoi(valueStrVec[i]));
		}
		catch (std::invalid_argument)
		{
			throw std::invalid_argument("Неверное содержание файла. Значение параметра должно быть представлено цифрами 0 или 1.");
		}
	}
	int h, w, countX, countY;
	h = valueVec[0];
	w = valueVec[1];
	countX = valueVec[2];
	countY = valueVec[3];
	std::vector<std::vector<int>> matrixInt;
	for (int i = 1; i < lineVec.size()-1; i++)
	{
		std::vector<std::string> lineMatrixStrVec = split(lineVec[i], ' ');
		std::vector<int> lineMatrixVec;
		if(lineMatrixStrVec.size()-1!=countX)
			throw std::invalid_argument("Неверное содержание файла. Несоответствие размера матрицы.");
		for (int j = 0; j < lineMatrixStrVec.size()-1; j++) 
		{
			if(lineMatrixStrVec[j].size()!=1)
				throw std::invalid_argument("Неверное содержание файла. Пропущены значения.");
			if (!std::isdigit(lineMatrixStrVec[j][0]))
			{
				throw std::invalid_argument("Неверное содержание файла.Значение кетки должно быть представлено цифрами 0 или 1.");
			}
			try
			{
				lineMatrixVec.push_back(std::stoi(lineMatrixStrVec[j]));
			}
			catch (std::invalid_argument)
			{
				throw std::invalid_argument("Неверное содержание файла. Значение кетки должно быть представлено цифрами 0 или 1.");
			}
		}
		matrixInt.push_back(lineMatrixVec);
	}
	int sizePixelX = h / countX;
	int sizePixelY = w / countY;
	grid loadedMatrix(countX,countY, sizePixelX, sizePixelY);

	for (int i = 0; i < countY; i++)
	{
		for (int j = 0; j < countX; j++)
		{
			if(matrixInt[i][j]==1)
				loadedMatrix.field[j][i].alive = true;
			else if (matrixInt[i][j] == 0)
				loadedMatrix.field[j][i].alive = false;
			else
				throw std::invalid_argument("Неверное содержание файла. Представление клектки должно содержать значения 0 или 1.");
		}
	}
	return loadedMatrix;
}

void File::saveRules(rule rules)
{
	Console::WriteLine("Вы хотите сохранить правила в файл.");
	std::string filePath = getCorrectPath(Write);
	std::ofstream f;
	f.open(filePath);
	for (int i = 0; i < rules.born.size();i++)
	{
		f << to_string(rules.born[i]) + ' ';
	}
	f << '\n';
	for (int i = 0; i < rules.survive.size(); i++)
	{
		f << to_string(rules.survive[i]) + ' ';
	}
	f << '\0';
	f.close();
}

rule File::loadRules()
{
	Console::WriteLine("Вы хотите загрузить правила из файла.");
	std::string filePath = getCorrectPath(Read);
	std::string line = getMessage(filePath);
	std::vector<std::string> lineVec = split(line, '\n');
	if(lineVec.size()!=2)
		throw invalid_argument("Неверное содержание файла. Ожидается 2 строки.");
	std::vector<int> valueVecBorn;
	std::vector<std::string>lineVecBornStr = split(lineVec[0], ' ');
	if (lineVecBornStr.size() > 10)
		throw invalid_argument("Неверное содержание файла. Ожидается не больше 9 значений.");
	for (int i = 0; i < lineVecBornStr.size()-1; i++)
	{
		try
		{
			for (int j = 0; j < valueVecBorn.size(); j++)
			{
				if(to_string(valueVecBorn[j])== lineVecBornStr[i])
					throw invalid_argument("Неверное содержание файла. Значение параметра повторяется.");
				if (logic::checkBorder(valueVecBorn[j], lowBoardNeighbour, maxBoardNeighbour))
					throw invalid_argument("Неверное содержание файла. Значение параметра повторяется.");
			}
			valueVecBorn.push_back(std::stoi(lineVecBornStr[i]));
		}
		catch (std::invalid_argument ex)
		{
			ex.what();
			throw invalid_argument("Неверное содержание файла. Значение параметра должно быть представлено уникальным числом от 0 до 8.");
		}
	}
	std::vector<int> valueVecSurvive;
	std::vector<std::string>lineVecSurviveStr = split(lineVec[1], ' ');
	if (lineVecSurviveStr.size() > 10)
		throw invalid_argument("Неверное содержание файла. Ожидается не больше 9 значений.");
	for (int i = 0; i < lineVecSurviveStr.size()-1; i++)
	{
		try
		{
			for (int j = 0; j < valueVecSurvive.size(); j++)
			{
				if (to_string(valueVecSurvive[j]) == lineVecSurviveStr[i])
					throw invalid_argument("Неверное содержание файла. Значение параметра повторяется.");
				if (logic::checkBorder(valueVecSurvive[j], lowBoardNeighbour, maxBoardNeighbour))
					throw invalid_argument("Неверное содержание файла. Значение параметра повторяется.");
			}
			valueVecSurvive.push_back(std::stoi(lineVecSurviveStr[i]));
		}
		catch (std::invalid_argument ex)
		{
			throw invalid_argument("Неверное содержание файла. Значение параметра должно быть представлено уникальным числом от 0 до 8.");
		}
	}
	return rule(valueVecBorn,valueVecSurvive);
}

std::vector<std::string> File::split(std::string s, char symb)
{
	size_t pos_start = 0, pos_end;
	std::string tmp;
	std::vector<std::string> res;
	while ((pos_end = s.find(symb, pos_start)) != std::string::npos) {
		res.push_back(s.substr(pos_start, pos_end - pos_start));
		pos_start = pos_end + 1;
	}
	res.push_back(s.substr(pos_start));
	return res;
}

std::string File::getMessage(std::string path)
{
	std::string message;
	std::vector<char> vec;
	char sim;
	std::ifstream fs(path);
	while (fs.get(sim) && sim != '\0')
	{
		vec.push_back(sim);
	}
	char* arr = new char[vec.size()];
	int i = vec.size();
	for (int i = 0; i < vec.size(); i++) {
		arr[i] = vec[i];
	}
	arr[vec.size()] = '\0';
	message = std::string(arr);
	fs.close();
	return message;
}

std::string File::getCorrectPath(bool write)
{
	for (;;)
	{
		Console::WriteLine("Введите путь к файлу.");
		std::string filePath = Console::ReadLine();
		if (!write)//только на чтение
		{
			if (!File::isFileExist(filePath))
			{
				Console::WriteLine("Файл с таким именем не существует. Повторите ввод.");
				continue;
			}
			return filePath;
		}
		else//на запись
		{
			if (File::isFileExist(filePath))
			{
				for (;;)
				{
					Console::WriteLine("Файл с таким именем уже существует. Хотите ли вы его перезаписать?");
					Console::WriteLine("1 - Да. 2 - Нет.");
					int saveResultChoice;
					saveResultChoice = Console::GetDigit();
					switch (saveResultChoice)
					{
					case Yes:
						if (!File::isFileReadOnly(filePath))
						{
							return filePath;
						}
						else
						{
							Console::WriteLine("Файл с таким именем закрыт на запись. Повторите ввод.");
							break;
						}
					case No:
						Console::WriteLine("Файл не будет перезаписан.");
						break;
					default:
						Console::WriteLine("Неверный символ, повторите ввод.");
						continue;
					}
					break;
				}
			}
			else if (File::canBeCreate(filePath))
			{
				return filePath;
			}
			else
			{
				Console::WriteLine("Файл с таким именем не может быть создан.");
			}
		}

	}
	
}

bool File::isFileExist(std::string filePath)
{
	try
	{
		return std::filesystem::exists(filePath);
	}
	catch (std::exception ex) 
	{
		return false;
	}
}

bool File::isFileReadOnly(std::string filePath)
{
	if (!isFileExist(filePath))
	{
		return false;
	}
	std::ofstream file;
	file.open(filePath);
	bool isFileReadonly = !file.is_open();
	if (!isFileReadonly)
	{
		file.close();
	}
	return isFileReadonly;
}

bool File::canBeCreate(std::string filePath)
{
	if (isFileExist(filePath))
	{
		return true;
	}
	std::ofstream file;
	file.open(filePath);
	file.close();
	bool canBeCreate = isFileExist(filePath);
	try
	{
		std::filesystem::remove(filePath);
	}
	catch (std::exception ex) {}

	return canBeCreate;
}