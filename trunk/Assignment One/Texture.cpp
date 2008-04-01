#include "Texture.h"

#include <stdlib.h>
#include <stdio.h>


GLuint Texture::loadTexture(const char* filename, GLuint width, GLuint height)
{
	GLuint texture;
	unsigned char *data;
	FILE* file;
	
	file = fopen(filename, "rb");
	
	if (!file)
	{
		return 0;
	}
	
	fread(data, width*height*3, 1, file);
	data = (unsigned char *)malloc( width * height * 3 );
	
	fclose(file);
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Maybe change GL_MODULATE TO GL_DECAL?
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	//mipmaps
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Repeat the texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
	return texture;
	
}