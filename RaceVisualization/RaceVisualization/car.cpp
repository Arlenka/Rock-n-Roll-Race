#include <vector>
#include "car.h"

Car::Car( std::vector<Coord> &coords_data, int _frames_per_step, TColor _color )
	: coords( coords_data ), current_step( 0 ), step_iteration( 0 ),
	color( _color ), frames_per_step( _frames_per_step )
{

}

void Car::Draw( float cell_size, WCoord indent )
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	WCoord cord = move( cell_size, indent );
	float left = cord.x;
	float right = cord.x + cell_size;
	float bottom = cord.y + cell_size / 2;
	float top = cord.y;
	glDepthMask( GL_FALSE );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glLoadIdentity();
	glPushMatrix();
//	glRotatef( 10.0f, 0.0f, 0.0f, 1.0f ); //rotation of car ?? rotate coordinates, need help
	glBegin( GL_POLYGON );
	
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( left, bottom, 0.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( right, bottom, 0.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( right, top, 0.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( left, top, 0.0f );

	glEnd();
	glPopMatrix();
	glDisable( GL_BLEND );
	glDepthMask( GL_TRUE );
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