#include "drawing.h"

Map Drawing::map; // static data members must be explicitly defined in exactly one compilation unit
std::vector<Car> Drawing::cars;
GLuint texture;

Drawing::Drawing( Map &map_data, std::vector<Car> &_cars )
{
	map = map_data;
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

	bool flag = !map.Need_to_reload();
	map.Draw(); // draw the map
	float cell_size = map.Get_cell_size(); // calculate the size of cell
	for( size_t i = 0; i < cars.size(); i++ ) {
		cars[i].Draw( map.Get_cell_size(), map.Get_indent() ); // draw car
	}
	glFlush(); // flush changes
	if( flag ) {
		glutSwapBuffers(); // if map wasn't reloaded (and buffers weren't swapped), swap buffers
	}
}

// load image from filen to texture
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
	LoadTexture( "..\\images\\road.png", map.texture_road );
	LoadTexture( "..\\images\\forest.png", map.texture_board );
	std::string car_filename;
	for( size_t i = 0; i < cars.size(); i++ ) {
		switch( cars[i].get_color() ) {
			case Red: 
				car_filename = "..\\images\\car_red.png";
				break;
			case Blue:
				car_filename = "..\\images\\car_blue.png";
				break;
			case Green:
				car_filename = "..\\images\\car_green.png";
				break;
			default:
				car_filename = "..\\images\\car_red.png";
		}
		LoadTexture( car_filename.c_str(), cars[i].texture );
	}
	glutTimerFunc( 1, Timer, 0 );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	glutMainLoop();
}