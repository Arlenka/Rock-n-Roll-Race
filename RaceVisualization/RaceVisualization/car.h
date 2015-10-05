#pragma once 
#include "coord.h"

enum TColor { Red, Blue, Green };

class Car
{
public:
	Car( std::vector<Coord> &coords_data, int _frames_per_step, TColor _color );
	Car( std::vector<Coord> &coords_data )
	{
		coords = coords_data;
		color = Red;
	}

	WCoord move( float cell_size, WCoord indent );
	TColor get_color()
	{
		return color;
	}

private:
	std::vector<Coord> coords;
	int current_step;
	int step_iteration;
	int frames_per_step;
	TColor color;
	WCoord transate_to_wcoord( float x, float y, float cell_size, WCoord indent );
};