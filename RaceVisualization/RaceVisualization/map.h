#pragma once
#include <vector>
#include <glut.h>

class Map
{
public:
	Map() {}
	Map( std::vector<std::vector<int>> map_data )
	{
		map = map_data;
	}
	void Draw();
	//	OpenGLObject get_map();

private:
	std::vector<std::vector<int>> map; // TODO может тут хранить не в виде 2мерного массива?
};