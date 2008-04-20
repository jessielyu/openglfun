#include <GLUT/glut.h>

#include "FillTest.h"

#include "clipTest.h"
#include "Paint.h"
#include "LineTest.h"


void display()
{
	//LineTest::displayLines();
	glColor3ub(255,255,255);
	FillTest::displayPolygons();
	//ClipTest::displayClip();
	//Paint::displayPaint();
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
   glutCreateWindow( "Doin' Thangs" );

   /* 
    * Callback function; causes "display()" to be called each time there
    * is a display callback. 
    */
   glutDisplayFunc( display );

   /* 
    * Causes program to enter an event-processing loop; should be last
    * statement in main() 
    */
   glutMainLoop( );

   return 0;

}