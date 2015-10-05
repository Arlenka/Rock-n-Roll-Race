#include "map.h"

void Map::Calculate()
{
	int n = map.size(), m = map[0].size();
	float height = glutGet( GLUT_WINDOW_HEIGHT ),
		width = glutGet( GLUT_WINDOW_WIDTH );
	cell_size = fmin( height / n, width / m ); // the length of one little square - "cell"
	indent.x = (width - cell_size * m) / 2; // indent from left and right window sides
	indent.y = (height - cell_size * n) / 2;  // indent from top and bottom window sides
}

void Map::Draw()
{
	int n = map.size(), m = map[0].size();
	for( int i = 0; i < n; i++ ) {
		for( int j = 0; j < m; j++ ) {
			if( map[i][j] == 1 ) {
				glColor3f( 0.0, 0.0, 0.0 ); // choose color for black "board" squares
			} else {
				glColor3f( 0.7, 0.7, 0.7 ); // choose color for grey "road" squares
			}
			glRectf( (j + 1) * cell_size + indent.x, (i + 1) * cell_size + indent.y,
				j *cell_size + indent.x, i * cell_size + indent.y ); // draw square
		}
	}
}

float Map::Get_cell_size()
{
	return cell_size;
}

WCoord Map::Get_indent()
{
	return indent;
}
