#include <string>
#include <vector>
#include <fstream>
#include "drawing.h"
#include "car.h"
#include "coord.h"


class Visualization
{
	// Visualization(); // конструктор с выбором входного файла через оконный интерфейс
	Visualization(std::string input_file); // конструктор с указанным входным файлом
	// ~Visualization();

	void Run(); // запуск гонки
	// void Stop(); // преждевременная остановка

	int get_screen_width();
	int get_screen_height();
	int get_cell_size();
	int get_steps_number_per_cell();

private:
	std::vector<std::vector<int>> map;
	Drawing drawing_module;
	std::vector<Car> cars;
	int current_step;
	int step_number;

	int screen_width;
	int screen_height;
	int cell_size;
	int steps_number_per_cell;

	void read_map(std::ifstream & input);
	void read_car(std::ifstream & input);

};