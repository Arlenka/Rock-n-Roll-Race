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
	void Resize(int n, int m)
	{
		map.resize(n);
		for (int i = 0; i < n; ++i) {
			map[i].resize(m);
		}
	}
	void InitialCell(int i, int j, int cell)
	{
		map[i][j] = cell;
	}
	
	void Draw();
	//	OpenGLObject get_map();

private:
	std::vector<std::vector<int>> map; // TODO может тут хранить не в виде 2мерного массива?
};