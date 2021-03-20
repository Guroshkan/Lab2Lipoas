#include "monitor.h"
#include <iostream>
monitor::monitor(int h, int w,int countX,int countY,rule rules,int delay,int fill)
{
	this->HEIGHT = h;
	this->WIDTH = w;
	this->rules = rules;
	this->delay = delay;
	int sizePixelX = h / countX;
	int sizePixelY = w / countY;
	int sizeCell = sizePixelX < sizePixelY ? sizePixelX : sizePixelY;
	grid gr(countX, countY, sizePixelX, sizePixelY);
	matrix = gr;
	this->countX = countX;
	this->countY = countY;
	this->fill = fill;
	pause = true;
}

void monitor::show()
{
	logic log(rules);
	if (fill != 0)
	{
		for (int i = 0; i < countX; i++)
		{
			for (int j = 0; j < countY; j++)
			{
				if (rand()%100 < fill)
				{
					matrix.field[i][j].alive = true;
				}
			}
		}
	}
	RenderWindow window(VideoMode(HEIGHT, WIDTH), "Conway Game.");
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))//кнопка нажата
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case  sf::Keyboard::Enter: pause = false; break;
				case sf::Keyboard::S:
					if (pause)
					{
						for (;;)
						{
							try
							{
								File::saveMatrix(HEIGHT, WIDTH, countX, countY, matrix);
								Console::WriteLine("Матрица уcпешно сохранена.");
								break;
							}
							catch (invalid_argument ex)
							{
								Console::WriteLine(ex.what());
								Console::WriteLine("Повторите попытку.");
							}
						}
					}
					break;
				case sf::Keyboard::L:
					if (pause)
					{
						for (;;)
						{
							try
							{
								this->matrix = File::loadMatrix();
								this->countX = matrix.countX;
								this->countY = matrix.countY;
								Console::WriteLine("Матрица успешно загружена.");
								break;
							}
							catch (invalid_argument ex)
							{
								Console::WriteLine(ex.what());
								Console::WriteLine("Повторите попытку.");
							}
						}
					}
					break;
				case sf::Keyboard::Space:pause = !pause; break;
				case sf::Keyboard::Add:
					delay /= 2;
					if (delay == 0)
						delay = 1;
					break;
				case sf::Keyboard::Subtract:
					delay *= 2;
					if (delay > 10000)
						delay = 10000;
					break;
				case sf::Keyboard::Escape:
					window.close();
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)//изменить значение клетки при нажатии
			{
				Vector2i windowPos = window.getPosition();
				windowPos.x += 8;//смещение координат окна из-за шапки
				windowPos.y += 40;
				Vector2i pos = Mouse::getPosition();
				int coordX = (pos.x - windowPos.x) / matrix.sizeCellX;
				int coordY = (pos.y - windowPos.y) / matrix.sizeCellY;
				if (!(coordX < 0 || coordX >= matrix.countX || coordY < 0 || coordY >= matrix.countY))
				{
					matrix.field[coordX][coordY].alive = !matrix.field[coordX][coordY].alive;

					sf::RectangleShape rec = RectangleShape(sf::Vector2f(matrix.sizeCellX - 1, matrix.sizeCellY - 1));
					rec.setPosition(coordX * matrix.sizeCellX, coordY * matrix.sizeCellY);
					window.draw(rec);
					window.display();
				}
			}	
			if (event.type == sf::Event::Resized)
			{
				Vector2u size(HEIGHT, WIDTH);
				window.setSize(size);
				/*Vector2u windowSize = window.getSize();
				HEIGHT = windowSize.x;
				WIDTH = windowSize.y;
				int sizeTmpX = HEIGHT / matrix.field[0][0].sizeX;
				int sizeTmpY = WIDTH / matrix.field[0][0].sizeY;

				for (int i = 0; i < matrix.field.size(); i++) 
				{
					for (int j = 0; j < matrix.field.size(); j++)
					{
						matrix.field[i][j].sizeX = sizeTmpX;
						matrix.field[i][j].sizeY = sizeTmpY;
					}
				}*/
			}
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		// Отрисовка окна	
		for (int i = 0; i < countX; i++)
		{
			for (int j = 0; j < countY; j++)
			{
				int sizeX = matrix.field[i][j].sizeX;
				int sizeY = matrix.field[i][j].sizeY;
				if (matrix.field[i][j].alive)
				{
					sf::RectangleShape rec = RectangleShape(sf::Vector2f(sizeX - 1, sizeY - 1));
					rec.setFillColor(sf::Color::White);
					if (pause)
						rec.setFillColor(sf::Color::Red);
					rec.setPosition(i * sizeX , j * sizeY );
					window.draw(rec);
				}
			}
		}
		if (!pause)
		{
			matrix = log.nextGen(matrix);
			sleep(sf::milliseconds(delay));
		}
		window.display();
		
	}
}
