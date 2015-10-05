#include "drawing.h"

Map Drawing::map; // static data members must be explicitly defined in exactly one compilation unit
std::vector<Car> Drawing::cars;

Drawing::Drawing( std::vector<std::vector<int>> &map_data, std::vector<Car> &_cars )
{
	map = Map( map_data );
	cars = _cars;
}

void Drawing::reshape( int width, int height )
{
	glViewport( 0, 0, width, height );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0, width, 0, height );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void Drawing::display()
{
	glClearColor( 1.0, 1.0, 1.0, 0.0 ); // clear background to white
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	map.Draw(); // draw the map
	for( size_t i = 0; i < cars.size(); i++ ) {
		// draw cars: TODO
	}
	glutSwapBuffers();
}


void Drawing::draw( int argc, char * argv[] )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );

	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "Rock'n'Roll Race" );

	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	glutMainLoop();
}