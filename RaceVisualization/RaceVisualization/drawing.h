#pragma once
#include <vector>
#include <glut.h>
#include "map.h"
#include "car.h"

class Drawing
{
public:
	Drawing( std::vector<std::vector<int>> map_data, std::vector<Car> _cars );
	Drawing() {};
	void draw( int argc, char * argv[] );

private:
	static void display();
	static void reshape( int width, int height );
	static Map map;
	static std::vector<Car> cars;
};
