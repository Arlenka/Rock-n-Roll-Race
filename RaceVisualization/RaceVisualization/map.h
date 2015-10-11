#pragma once
#include <vector>
#include <glut.h>
#include "coord.h"
#include "SOIL.h"

class Map
{
public:
	Map() {}
	Map( std::vector<std::vector<int>> &map_data )
	{
		map = map_data;
		cell_size = 0;
		indent = WCoord( 0, 0 );
	}
	void Calculate();
	void Draw();
	float Get_cell_size();
	WCoord Get_indent();
	//	OpenGLObject get_map();

	GLuint texture_board;
	GLuint texture_road;

private:
	std::vector<std::vector<int>> map; // TODO может тут хранить не в виде 2мерного массива?
	float cell_size;
	WCoord indent;
};