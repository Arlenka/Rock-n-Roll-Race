#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "drawing.h"
#include "car.h"
#include "coord.h"
#include "map.h"


const int DEFAULT_WINDOW_WIDTH = 500;
const int DEFAULT_WINDOW_HEIGHT = 500;
const int DEFAULT_STEPS_PER_CELL = 20;

// TODO: Всемогутер. Рефакторинг!
class Visualisation
{
public:
	Visualisation() {} // конструктор с выбором входного файла через оконный интерфейс
	Visualisation( std::string input_file ); // конструктор с указанным входным файлом
	// ~Visualization();

	void Run(); // запуск гонки
	// void Stop(); // преждевременная остановка

private:
	Drawing drawing_module;
	std::vector<Car> cars;
	int current_step;
	int step_number;

	int screen_width;
	int screen_height;
	int cell_size;
	int steps_number_per_cell;

	std::vector<std::vector<int>> read_map( std::ifstream & input );
	void read_cars( std::ifstream & input );

};