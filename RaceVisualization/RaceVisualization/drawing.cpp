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


void rotate(float &x, float &y, float angle)
{
	float tx = x,
		ty = y;
	x = tx * cos(angle) - ty * sin(angle);
	y = tx * sin(angle) + ty * cos(angle);
}
void rotateCar(float &Ax, float &Ay, float &Bx, float &By, float &Cx, float &Cy, float &Dx, float &Dy, float centerX, float centerY, float angle)
{
	Ax -= centerX;
	Bx -= centerX;
	Cx -= centerX;
	Dx -= centerX;

	Ay -= centerY;
	By -= centerY;
	Cy -= centerY;
	Dy -= centerY;

	rotate(Ax, Ay, angle);
	rotate(Bx, By, angle);
	rotate(Cx, Cy, angle);
	rotate(Dx, Dy, angle);

	Ax += centerX;
	Bx += centerX;
	Cx += centerX;
	Dx += centerX;

	Ay += centerY;
	By += centerY;
	Cy += centerY;
	Dy += centerY;
}
void Drawing::display()
{
	glClearColor( 1.0, 1.0, 1.0, 0.0 ); // clear background to white
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	map.Draw(); // draw the map
	float cell_size = map.Get_cell_size();
	for( size_t i = 0; i < cars.size(); i++ ) {
		//draw car
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, cars[i].texture );
		glTexEnvf( GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		float angle = 0.0;
		WCoord cord = cars[i].move( map.Get_cell_size(), map.Get_indent(), angle );
		float left = cord.x;
		float right = cord.x + cell_size;
		float bottom = cord.y + cell_size / 2;
		float top = cord.y;
		glDepthMask( GL_FALSE );
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glBegin( GL_POLYGON );
		float Ax = left,
			Ay = bottom,
			Bx = right,
			By = bottom,
			Cx = right,
			Cy = top,
			Dx = left,
			Dy = top;
	
		float centerX = Dx - (Dx - Bx) / 2,
			centerY = Dy - (Dy - By) / 2;
		rotateCar(Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, centerX, centerY, angle);
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( Ax, Ay, 0.0f );	
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( Bx, By, 0.0f );	
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( Cx, Cy, 0.0f );	
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( Dx, Dy, 0.0f );	
		//glTexCoord2f(0.0f, 0.0f); glVertex3f(left, bottom, 0.0f);
		//glTexCoord2f(1.0f, 0.0f); glVertex3f(right, bottom, 0.0f);
		//glTexCoord2f(1.0f, 1.0f); glVertex3f(right, top, 0.0f);
		//glTexCoord2f(0.0f, 1.0f); glVertex3f(left, top, 0.0f);

		glEnd();
		glDisable( GL_BLEND );
		glDepthMask( GL_TRUE );
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
	LoadTexture( "D:\\Rock-n-Roll-Race\\RaceVisualization\\images\\road.png", map.texture_road );
	LoadTexture( "D:\\Rock-n-Roll-Race\\RaceVisualization\\images\\forest.png", map.texture_board );
	for( size_t i = 0; i < cars.size(); i++ ) {
		LoadTexture( "D:\\Rock-n-Roll-Race\\RaceVisualization\\images\\car_1.png", cars[i].texture );
	}
	glutTimerFunc( 1, Timer, 0 );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	glutMainLoop();
}