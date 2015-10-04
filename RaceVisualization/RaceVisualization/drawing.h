#pragma once
#include <vector>
#include "map.h"
#include "car.h"

class Drawing
{
	Drawing(std::vector<std::vector<int>> map_data);
	void draw(std::vector<Car> cars);
	
private:
	Map map;
};
