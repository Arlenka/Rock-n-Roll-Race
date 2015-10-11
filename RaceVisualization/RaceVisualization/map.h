#pragma once
#include <vector>
#include <glut.h>
#include "coord.h"
#include "SOIL.h"
#include <memory>

class Map
{
public:
	Map() {}
	Map( std::vector<std::vector<int>> &map_data )
	{
		map = map_data;
		cell_size = 0;
		indent = WCoord( 0, 0 );
		texture_board = 0;
		texture_map = 0;
		texture_road = 0;
		glGenTextures( 1, &texture_map );
		need_reload = true;
	}
	void Calculate();
	void Draw();
	float Get_cell_size();
	WCoord Get_indent();
	//	OpenGLObject get_map();

	void SaveTexture();
	void ReloadTexture();

	bool Need_to_reload()
	{
		return need_reload;
	}
	GLuint texture_board;
	GLuint texture_road;
	GLuint texture_map;
private:
	std::vector<std::vector<int>> map; // TODO может тут хранить не в виде 2мерного массива?
	float cell_size;
	WCoord indent;
	bool need_reload;
};