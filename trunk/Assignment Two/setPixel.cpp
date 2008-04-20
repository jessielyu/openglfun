/**
 * setPixel -- openGL routine for setting a pixel
 *
 */
 #include "SetPixel.h"

#include <OpenGL/gl.h>

void SetPixel::setPixel (int x, int y)
{
  glRecti( x, y, x+1, y+1 );
}
