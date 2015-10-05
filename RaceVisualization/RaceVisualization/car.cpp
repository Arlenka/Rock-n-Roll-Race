#include <vector>
#include "car.h"


Car::Car(std::vector<Coord> coords_data, Parameters params)
	: coords(coords_data), parameters(params), current_step(0), step_iteration(0)
{
	
}


WCoord Car::move()
{
	int iterations_by_step = parameters.get_iterations_by_step();

	if (current_step + 1 < coords.size()) {
		if (step_iteration + 1 < iterations_by_step) {
			step_iteration++;
		} else {
			current_step++;
			step_iteration = 0;
		}
	}

	if (current_step + 1 < coords.size()) {
		float dx = (coords[current_step + 1].x - coords[current_step].x) / iterations_by_step;
		float dy = (coords[current_step + 1].y - coords[current_step].y) / iterations_by_step;
		float x = coords[current_step].x + step_iteration * dx;
		float y = coords[current_step].y + step_iteration * dy;
		return transate_to_wcoord(x, y);
	} else {
		Coord last = coords.back();
		return transate_to_wcoord(last.x, last.y);
	}
}


// TODO добавить умножение на коэфициент сжатия чтобы соответствовать 2.5D
WCoord Car::transate_to_wcoord(float x, float y)
{
	WCoord wcoord;
	int cell_size = parameters.get_cell_size();
	WCoord start_wcoord = parameters.get_start_wcoord();
	wcoord.x = round(x * cell_size + start_wcoord.x);
	wcoord.y = round(y * cell_size + start_wcoord.y);
	return wcoord;
}