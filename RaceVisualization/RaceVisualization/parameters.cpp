#include "parameters.h"

int Parameters::get_screen_width() { return 0; }
int  Parameters::get_screen_height() { return 0; }
int  Parameters::get_cell_size() { return 0; }
int  Parameters::get_iterations_by_step() { return 0; }
WCoord Parameters::get_start_wcoord() { 
	WCoord a;
	a.x = 0;
	a.y = 0;
	return a;
}