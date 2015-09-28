#include <glut.h>
#include <fstream>
#include <vector>

class Map
{
public:
	void ReadInput()
	{
		int n = 0, m = 0;
		std::ifstream fin( "input.txt" );
		fin >> n >> m;
		data.resize( n );
		for( int i = n - 1; i >= 0; i-- ) { 	// считывание такое, т.к. начало координат в openGL слева снизу, проще массив перевернуть
			data[i].resize( m );
			for( int j = 0; j < m; j++ ) {
				fin >> data[i][j];
			}
		}
	}
	void GetSize( int& n, int& m )
	{
		n = data.size();
		m = data[0].size();
	}
	bool isOne( int i, int j )
	{
		return data[i][j] == 1;
	}
private:
	std::vector< std::vector <int > > data;
};

static Map myMap; // быдлокод... в идеале, у Map надо создать функцию Draw,	
				  // но не понимаю, как ее передать в glutDisplayFunc, который требует строго void (*)()

void display()
{
	glClear( GL_COLOR_BUFFER_BIT );
	int n = 0, m = 0;
	myMap.GetSize( n, m );
	float height = glutGet( GLUT_WINDOW_HEIGHT ),
		  width = glutGet( GLUT_WINDOW_WIDTH );
	float squareLength = fmin( height, width );
	float x_num = squareLength / n,
		  y_num = squareLength / m;
	float x_start = (width - squareLength) / 2,
		  y_start = (height - squareLength) / 2;
	for( int i = 0; i < n; i++ ) {
		for( int j = 0; j < m; j++ ) {
			if( myMap.isOne( i, j ) ) {
				glBegin( GL_POLYGON );
				glColor3f( 1.0, 1.0, 1.0 );
				glVertex3f( j * x_num + x_start, i * y_num + y_start, 0 );
				glVertex3f( j * x_num + x_start, (i + 1) * y_num + y_start, 0 );
				glVertex3f( (j + 1) * x_num + x_start, (i + 1) * y_num + y_start, 0 );
				glVertex3f( (j + 1) * x_num + x_start, i * y_num + y_start, 0 );
				glEnd();
			}
		}
	}
	glutSwapBuffers();
}

void reshape( int w, int h )
{
	glViewport( 0, 0, w, h );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0, w, 0, h );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

int main( int argc, char * argv[] )
{
	myMap.ReadInput();
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );

	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "Rock'n'Roll Race" );

	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	glutMainLoop();

	return 0;
}