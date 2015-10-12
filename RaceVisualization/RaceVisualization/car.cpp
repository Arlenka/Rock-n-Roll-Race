#include <vector>
#include "car.h"

Car::Car( std::vector<Coord> &coords_data, int _frames_per_step, TColor _color = Red)
	: coords( coords_data ), current_step( 0 ), step_iteration( 0 ),
	color( _color ), frames_per_step( _frames_per_step )
{

}


WCoord Car::move( float cell_size, WCoord indent, float &angle )
{
	if( current_step + 1 < coords.size() ) {
		if( step_iteration  < frames_per_step ) {
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
		
		angle = abs(2.0*coords[current_step].helpAngle - coords[current_step].angle);
		return transate_to_wcoord( x, y, cell_size, indent );
	} else {
		Coord last = coords.back();
		return transate_to_wcoord( last.x, last.y, cell_size, indent );
	}
}

float findAngle(int x, int y)
{
	float angle = 0.0;
	angle = (float)x / sqrt(x * x + y * y);
	return acos(angle);
}

void Car::getAngles() {
	for (int i = 1; i < coords.size(); ++i) {
		coords[i - 1].angle = findAngle(coords[i].x - coords[i - 1].x, coords[i].y - coords[i - 1].y);
		if (coords[i].y - coords[i - 1].y < 0) {
			coords[i - 1].helpAngle = PI;
		}
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