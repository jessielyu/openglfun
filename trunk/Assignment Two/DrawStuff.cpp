/**
 * Routines that you'll need to write
 *
 */
#include <GLUT/glut.h>         /* glut.h includes gl.h and glu.h*/

void setPixel (int x, int y);



/* 
 * Draw line from x1, y1 to x2, y2 
 */
void drawLine( int x1, int y1, int x2, int y2) {

  /* Your task is to rewrite this using only calls to setPixel() */

  glBegin( GL_LINES ); 
    glVertex2i( x1, y1 );
    glVertex2i( x2, y2 );
  glEnd( );

}


/* 
 * Draw filled polygon 
 */

void drawPolygon( int n, int x[], int y[] ) {

  /* Your task is to rewrite this using only calls to setPixel() */
  
int i;

 glBegin( GL_POLYGON ); 
    for (i = 0; i < n; i++ ) {
      glVertex2i( x[i], y[i] );
    }
 glEnd( );

}


/**
 * Clip the polygon with vertex count in and verticies inx and iny against
 * the rectangular clipping region specified by lower left corner (x0, y0) 
 * and upper right corner (x1, y1).  The resulting vertices are places in
 * outx, and outy with the vertex count places in out.
 */
void clipPolygon (int in, int inx[], int iny[], int *out, int outx[],
                  int outy[], int x0, int y0, int xq, int y1)
{
  /* provide your implementation here */
}
