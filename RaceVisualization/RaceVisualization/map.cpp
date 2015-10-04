#include "map.h"

void Map::Draw()
{
	int n = map.size(), m = map[0].size();
	float height = glutGet( GLUT_WINDOW_HEIGHT ),
		width = glutGet( GLUT_WINDOW_WIDTH );
	float squareLength = fmin( height / n, width / m ); // the length of one little square - "cell"
	float xIndent = (width - squareLength * m) / 2, // indent from left and right window sides
		yIndent = (height - squareLength * n) / 2;  // indent from top and bottom window sides
	for( int i = 0; i < n; i++ ) {
		for( int j = 0; j < m; j++ ) {
			if( map[i][j] == 1 ) {
				glColor3f( 0.0, 0.0, 0.0 ); // choose color for black "board" squares
			} else {
				glColor3f( 0.7, 0.7, 0.7 ); // choose color for grey "road" squares
			}
			glRectf( (j + 1) * squareLength + xIndent, (i + 1) * squareLength + yIndent,
				j *squareLength + xIndent, i * squareLength + yIndent ); // draw square
		}
	}
}