#include <vector>
#include "map.h"

class Drawing
{
	Drawing(std::vector<std::vector<int>> map_data);
	void draw(std::vector<Car> cars);
	
private:
	Map map;
};
