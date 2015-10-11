#pragma once
#include <Windows.h>
#include <vector>
#include <glut.h>
#include "map.h"
#include "car.h"
/* OpenGL needs static functions and command line arguments for drawing*/

class Drawing
{
public:
	Drawing( Map &map_data, std::vector<Car> &_cars );
	Drawing() {};
	void draw( int argc, char * argv[] );
	void LoadTexture( const char*, GLuint& texture );

private:
	static void display();
	static void reshape( int width, int height );
	static Map map;
	static std::vector<Car> cars;
	static void Timer( int value );
};
