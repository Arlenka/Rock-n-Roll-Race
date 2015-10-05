#pragma once 
#include "coord.h"
#include "parameters.h"

class Car
{
public:
	Car( std::vector<Coord> &coords_data, Parameters &param );
	Car( std::vector<Coord> &coords_data )
	{
		coords = coords_data;
	}

	WCoord move();

private:
	std::vector<Coord> coords;
	int current_step;
	int step_iteration;
	Parameters parameters;

	WCoord transate_to_wcoord( float x, float y );
};