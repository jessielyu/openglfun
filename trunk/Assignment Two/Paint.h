#ifndef INCLUDED_Paint
#define INCLUDED_Paint

#include <GLUT/glut.h>

class Paint
{
public:

	static void mouse( int, int, int, int );
	static void displayPaint( void );
	static void myReshape( GLsizei, GLsizei );

	static void myinit( void );

	static void drawLineLoop( int, int [], int [] );

	static void screen_box( int, int, int );
	static void right_menu( int );
	static void middle_menu( int );
	static void color_menu( int );
	static void fill_menu( int );

	static int pick( int, int );
	//static void setPixel (int x, int y);

};

#endif