#include "coord.h"

class Car
{
	Car(std::vector<Coord> coords_data);
	WCoord move();

private:
	std::vector<Coord> coords;

	WCoord transate_to_wcoord(Coord coord);
};