#include "common.h"
#include "map.h"
#include <vector>

Visualisation::Visualisation(std::string input_file) {
	std::ifstream fin(input_file);
	std::vector<std::vector<int>> map_data = read_map(fin);
	read_cars(fin);
	Drawing drawing_module(map_data, cars);
}



std::vector<std::vector<int>> Visualisation::read_map(std::ifstream & input) {
	int n, m, cell;
	input >> n >> m;
	std::vector<std::vector<int>> map_data;
	map_data.resize(n);
	for (int i = n - 1; i >= 0; i--) { 	
		map_data[i].resize(m);
		for (int j = 0; j < m; j++) {
			input >> cell;
			map_data[i][j] = cell;
		}
	}
	return map_data;
}

void Visualisation::read_cars(std::ifstream & input) {
	int n, numberOfSteps;
	input >> n;
	for (int i = 0; i < n; ++i) {
		input >> numberOfSteps;
		std::vector<Coord> coord;
		for (int j = 0; j < numberOfSteps; ++j) {
			Coord step;
			input >> step.x >> step.y;
			coord.push_back(step);
		}
		Car car(coord);
		cars.push_back(car);
	}
}