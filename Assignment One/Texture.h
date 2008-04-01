#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

class Texture
{
public:
		static GLuint loadTexture(const char* filename, GLuint width, GLuint height);
};