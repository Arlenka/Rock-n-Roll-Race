#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "drawing.h"
#include "car.h"
#include "coord.h"


const int DEFAULT_WINDOW_WIDTH = 500;
const int DEFAULT_WINDOW_HEIGHT = 500;
const int DEFAULT_STEPS_PER_CELL = 20;


class Visualization
{
public:
	// Visualization(); // конструктор с выбором входного файла через оконный интерфейс
	Visualization( std::string input_file ); // конструктор с указанным входным файлом
	// ~Visualization();

	void Run(); // запуск гонки
	// void Stop(); // преждевременная остановка

private:
	Drawing drawing_module;
	std::vector<Car> cars;
	int current_step;
	int step_number;

	void read_map( std::ifstream & input );
	void read_car( std::ifstream & input );

};