#include "drawing.h"

Map Drawing::map; // static data members must be explicitly defined in exactly one compilation unit
std::vector<Car> Drawing::cars;
GLuint texture;

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

	//glColor3f( 1.0, 0.0, 0.0 );
	//glTranslatef( -150, -150, 0 );
	//glRotatef( 1.0, 0, 0, 1.0 );
	//glTranslatef( 150, 150, 0 );
	//glBegin( GL_POLYGON );

	//glVertex3f( 100, 100, 0.0f );
	//glVertex3f( 200, 100, 0.0f );
	//glVertex3f( 200, 200, 0.0f );
	//glVertex3f( 100, 200, 0.0f );

	//glEnd();


	map.Draw(); // draw the map
	float cell_size = map.Get_cell_size();
	for( size_t i = 0; i < cars.size(); i++ ) {
		cars[i].Draw( map.Get_cell_size(), map.Get_indent() );
	}
	glFlush();
	
	glutSwapBuffers();
}

void Drawing::LoadTexture( const char* filename, GLuint& texture )
{
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	int width, height;
	int channels;
	unsigned char* image = SOIL_load_image( filename, &width, &height, &channels, SOIL_LOAD_RGBA );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
		( float )GL_MODULATE);
	SOIL_free_image_data( image );
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void Drawing::draw( int argc, char * argv[] )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "Rock'n'Roll Race" );
	//load textures for cars and map
	LoadTexture( "C:\\Study\\PromProg\\Rock-n-Roll-Race\\RaceVisualization\\images\\road.png", map.texture_road );
	LoadTexture( "C:\\Study\\PromProg\\Rock-n-Roll-Race\\RaceVisualization\\images\\forest.png", map.texture_board );
	for( size_t i = 0; i < cars.size(); i++ ) {
		LoadTexture( "C:\\Study\\PromProg\\Rock-n-Roll-Race\\RaceVisualization\\images\\car_1.png", cars[i].texture );
	}
	glutTimerFunc( 1, Timer, 0 );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	glutMainLoop();
}