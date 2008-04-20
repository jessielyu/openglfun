#include <GLUT/glut.h>

#include "FillTest.h"

#include "clipTest.h"
#include "Paint.h"
#include "LineTest.h"

int maxScreen = 2;
int whichScreen = 0;

void display()
{

	switch(whichScreen)
	{
		case 0:
			LineTest::displayLines();
			break;
		case 1:
			FillTest::displayPolygons();
			break;
		case 2:
			ClipTest::displayClip();
			break;
	}
	
	// Not using
	//Paint::displayPaint();
}

// If the left mouse button is down, start a jump
void handleMouse(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		whichScreen++;
		if (whichScreen > maxScreen)
		{
			whichScreen = 0;
		}
		glutPostRedisplay();
	}
}

/* 
 * Main routine - GLUT setup and initialization 
 */
int main( int argc, char** argv ) {

   /* 
    * Initializes GLUT and should be used before any OpenGL functions 
    */
   glutInit( &argc, argv );

   /* 
    * Creates window on screen with title in argument 
    */
   glutCreateWindow( "Scan Conversion" );

   /* 
    * Callback function; causes "display()" to be called each time there
    * is a display callback. 
    */
   glutDisplayFunc( display );
   
   // Handle mouse input with this function
	glutMouseFunc(handleMouse);
	
	// Draw on black
	glClearColor(1.0,1.0,1.0,0.0);
	
	// Draw white
	glColor3ub(0,0,0);
	
   /* 
    * Causes program to enter an event-processing loop; should be last
    * statement in main() 
    */
   glutMainLoop( );

   return 0;

}