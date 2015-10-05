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
	map.Calculate();
}

void Drawing::Timer( int value )
{
	glutPostRedisplay();
	glutTimerFunc( 1, Timer, 0 );
}

void Drawing::display()
{
	glClearColor( 1.0, 1.0, 1.0, 0.0 ); // clear background to white
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	map.Draw(); // draw the map
	float cell_size = map.Get_cell_size();
	for( size_t i = 0; i < cars.size(); i++ ) {
		WCoord cord = cars[i].move( map.Get_cell_size(), map.Get_indent() );
		switch( cars[i].get_color() ) {
			case Red: 
				glColor3f( 1.0, 0.0, 0.0 );
				break;
			case Green:
				glColor3f( 0.0, 1.0, 0.0 );
				break;
			case Blue:
				glColor3f( 0.0, 0.0, 1.0 );
				break;
			default:
				break;
		} 
		glRectf( cord.x + cell_size / 4, cord.y + cell_size / 4, cord.x + cell_size * 3 / 4, cord.y + cell_size * 3 / 4 );
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

	glutTimerFunc( 1, Timer, 0 );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	glutMainLoop();
}