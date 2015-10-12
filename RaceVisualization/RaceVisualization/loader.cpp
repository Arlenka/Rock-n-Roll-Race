#include "loader.h"
#include "map.h"
#include <vector>

Loader::Loader(std::string map_file, std::string cars_file, int argc, char* argv[])
{
	colorMap["Red"] = Red;
	colorMap["Green"] = Green;
	colorMap["Blue"] = Blue;
	
	std::ifstream map_in( map_file );
	Map map = read_map( map_in );
	std::ifstream cars_in(cars_file);
	std::vector<Car> cars = read_cars( cars_in );
	Drawing drawing_module( map, cars );
	drawing_module.draw(argc, argv);
}

Map Loader::read_map( std::ifstream & input )
{
	int n = 0,
		m = 0,
		cell = 0;
	input >> n >> m;
	std::vector<std::vector<int>> map_data;
	map_data.resize( n );
	for( int i = n - 1; i >= 0; i-- ) {
		map_data[i].resize( m );
		for( int j = 0; j < m; j++ ) {
			input >> cell;
			map_data[i][j] = cell;
		}
	}
	Map map(map_data);
	return map;
}
std::vector<Car> Loader::read_cars( std::ifstream & input )
{
	int n = 0,
		numberOfSteps = 0;
	std::string color = "";
	input >> n;
	std::vector<Car> cars;
	for( int i = 0; i < n; ++i ) {
		input >> color;
		input >> numberOfSteps;
		Car car(colorMap[color]);
		for( int j = 0; j < numberOfSteps; ++j ) {
			Coord step;
			input >> step.x >> step.y;
			car.push( step );
		}
		car.getAngles();
		cars.push_back( car );
	}
	
	return cars;
}