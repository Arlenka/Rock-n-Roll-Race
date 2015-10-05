#pragma once
class Parameters
{
public:
	Parameters();

	int get_screen_width();
	int get_screen_height();
	int get_cell_size();
	int get_iterations_by_step();
	WCoord get_start_wcoord();

private:
	int screen_width;
	int screen_height;
	int cell_size;
	int iterations_by_step;
	WCoord start_wcoord;
};