#include <vector>
#include "car.h"

Car::Car( std::vector<Coord> &coords_data, int _frames_per_step, TColor _color )
	: coords( coords_data ), current_step( 0 ), step_iteration( 0 ),
	color( _color ), frames_per_step( _frames_per_step )
{

}


WCoord Car::move( float cell_size, WCoord indent )
{
	if( current_step + 1 < coords.size() ) {
		if( step_iteration + 1 < frames_per_step ) {
			step_iteration++;
		} else {
			current_step++;
			step_iteration = 0;
		}
	}

	if( current_step + 1 < coords.size() ) {
		float coord_x = coords[current_step + 1].x - coords[current_step].x;
		float coord_y = coords[current_step + 1].y - coords[current_step].y;
		float dx = (coord_x) / frames_per_step;
		float dy = (coord_y) / frames_per_step;
		float x = coords[current_step].x + step_iteration * dx;
		float y = coords[current_step].y + step_iteration * dy;
		return transate_to_wcoord( x, y, cell_size, indent );
	} else {
		Coord last = coords.back();
		return transate_to_wcoord( last.x, last.y, cell_size, indent );
	}
}


// TODO добавить умножение на коэфициент сжатия чтобы соответствовать 2.5D
WCoord Car::transate_to_wcoord( float x, float y, float cell_size, WCoord indent )
{
	WCoord wcoord( 0, 0 );
	wcoord.x = x * cell_size + indent.x;
	wcoord.y = y * cell_size + indent.y;
	return wcoord;
}