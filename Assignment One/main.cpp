#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <stdlib.h>
//#include <Carbon/Carbon.h>
//#include "MacApplication.h"
#include <QuickTime/QuickTime.h>	// For audio playback

#include "data.h"

const GLint MARIO_START_Y = 64;	// position where mario starts his jump
const GLint MARIO_STOP_Y = 146;	// position where mario ends his jump

extern GLint marioStandVertices[];	// vertices that make up mario standing
extern GLubyte marioStandIndices[];	// indices for polygons to make up mario standing
extern GLubyte pattern[];	// pattern for the polygon stipple in the pipe

GLuint frame = 0;	// Keep track of what frame we're on

GLfloat windowWidth = 640.0;	// window width
GLfloat windowHeight = 480.0;	// window height

GLuint timerDelay = 5;
GLuint jumpIncrement = 2;

// Texture handles
GLuint cloudTexture;
GLuint groundTexture;
GLuint brickTexture;
GLuint qblockTexture1;
GLuint qblockTexture2;
GLuint qblockTexture3;
GLuint bushTexture;
GLuint blockTexture;
GLuint jumpTexture;
GLuint coinTexture1;
GLuint coinTexture2;
GLuint coinTexture3;
GLuint coinTexture4;

GLuint marioY = 64;//MARIO_START_Y;	// Mario's current position
GLboolean jump = 0;	// Whether or not mario is jumping
GLboolean jumpMaxReached = 0;	// Whether or not the jump has peaked
GLboolean blockFadeIn = 0;	// Whether the block is fading in or out

GLuint currentQBlockTexture;	// Current texture to display for the question block

Movie jumpSound;  // jump sound
Movie coinSound; // coin sound

// Set clear color, matrix mode, orthogonal display
void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	//glClearColor(0.58,0.57,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,windowWidth,0.0,windowHeight);
}

void reset()
{
	// kind of a hack
	//glLoadIdentity();
	//gluOrtho2D(0.0,windowWidth,0.0,windowHeight);
	
	// better, still hacky?
	glPopMatrix();
	glPushMatrix();
	
	glColor4ub(255,255,255,255);
}

// Referenced texture tutorial from http://www.swiftless.com/tutorials/opengl/texture_under_windows.html
GLuint loadTexture( const char * filename, int width, int height )
{
	GLuint texture;	// Handle for the texture
	unsigned char * data;	// Data from the file
	FILE * file;	// The image file to read from

	// Open the file
	file = fopen( filename, "rb" );
	
	// Break out if file doesn't exist or whatnot
	if ( file == NULL ) 
	{
		return 0;
	}
	
	// Read in the data, close file
	data = (unsigned char *)malloc( width * height * 3 );
	fread( data, width * height * 3, 1, file );
	fclose( file );

	glGenTextures( 1, &texture ); // make the texture
	glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it's array
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture parameters

	// Mipmap settings
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Texture wrap settings
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	//Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free( data ); //free the memory
	return texture; //return texture handle
}

// Make our mario
void drawMario()
{
	reset();
	
	// Draw the jump texture if we're jumping
	if (jump)
	{
		// MarioY is the current jump height
		glTranslatef(240.0, marioY, 0);
		glScalef(4, 4, 4);
		glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, jumpTexture);
		
		// Using triangle strips
		glBegin (GL_TRIANGLE_STRIP);
		glTexCoord2d(0.0,0.0); glVertex2i(0,16);
		glTexCoord2d(0.0,1.0); glVertex2i(0,0);
		glTexCoord2d(1.0,0.0); glVertex2i(17,16);
		glTexCoord2d(1.0,1.0); glVertex2i(17,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	// Otherwise draw the standing mario indexed polygons
	else
	{
		// Enable vertex arrays and index arrays
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_INDEX_ARRAY );
		
		// Use our index and vertex arrays for mario standing
		glIndexPointer( GL_UNSIGNED_BYTE, 0, marioStandIndices );
		glVertexPointer( 2, GL_INT, 0, marioStandVertices );
		
		// Position and scale
		glTranslatef(250.0, MARIO_START_Y, 0);
		glScalef(4.0,4.0,4.0);
			
		// Draw red quads
		glColor3ub(248,56,0);
		glDrawElements( GL_QUADS, 56, GL_UNSIGNED_BYTE, marioStandIndices );
		
		// Draw brown quads
		glColor3ub(172, 124, 0);
		glDrawElements( GL_QUADS, 84, GL_UNSIGNED_BYTE, marioStandIndices+56 );
		
		// Draw tan quads
		glColor3ub(255, 164, 64);
		glDrawElements( GL_QUADS, 64, GL_UNSIGNED_BYTE, marioStandIndices+140 );
		
		// Turn off vertex and index array states
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_INDEX_ARRAY );
	}
}

// Draw our sky
void drawSky()
{
	reset();
	
	// Color of the sky
	glColor3f(0.58,0.57,1.0);
	
	// Triangle fan for sky color
	glBegin (GL_TRIANGLE_FAN);
	glVertex2i(320,240);
	glVertex2i(0,480);
	glVertex2i(640,480);
	glVertex2i(640,0);
	glVertex2i(0,0);
	glVertex2i(0,480);
	glEnd();
	
	reset();
	
	// Position and scale
	glTranslatef(90.0, 300.0, 0);
	glScalef(25.0,25.0,25.0);

	// Draw first cloud using quads
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, cloudTexture);
	glBegin (GL_QUADS);
	glTexCoord2d(0.0,1.0); glVertex2i(-2,-1); //with our vertices we have to assign a texcoord
	glTexCoord2d(1.0,1.0); glVertex2i(2,-1); //so that our texture has some points to draw to
	glTexCoord2d(1.0,0.0); glVertex2i(2,1);
	glTexCoord2d(0.0,0.0); glVertex2i(-2,1);
	glEnd();
	
	// Draw second cloud
	glTranslatef(22.0, 4.0, 0);
	glBegin (GL_QUADS);
	glTexCoord2d(0.0,1.0); glVertex2i(-2,-1); //with our vertices we have to assign a texcoord
	glTexCoord2d(1.0,1.0); glVertex2i(2,-1); //so that our texture has some points to draw to
	glTexCoord2d(1.0,0.0); glVertex2i(2,1);
	glTexCoord2d(0.0,0.0); glVertex2i(-2,1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// Draw our ground
void drawGround()
{
	reset();
	
	// Draw the ground using quad strips
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, groundTexture);
	glBegin (GL_QUAD_STRIP);
	glTexCoord2d(0.0,0.0); glVertex2i(0,64);
	glTexCoord2d(0.0,2.0); glVertex2i(0,0);
	glTexCoord2d(7.0,0.0); glVertex2i(320,64);
	glTexCoord2d(7.0,2.0); glVertex2i(320,0);
	
	glTexCoord2d(0.0,0.0); glVertex2i(320,64);
	glTexCoord2d(0.0,2.0); glVertex2i(320,0);
	glTexCoord2d(7.0,0.0); glVertex2i(640,64);
	glTexCoord2d(7.0,2.0); glVertex2i(640,0);
	glEnd();
	
	// Draw the bush texture in triangle strips
	glTranslatef(64.0,64.0, 0);
	glBindTexture (GL_TEXTURE_2D, bushTexture);
	glBegin (GL_TRIANGLE_STRIP);
	glTexCoord2d(0.0,0.0); glVertex2i(0,32); //with our vertices we have to assign a texcoord
	glTexCoord2d(0.0,1.0); glVertex2i(0,0);
	glTexCoord2d(1.0,0.0); glVertex2i(64,32); //so that our texture has some points to draw to
	glTexCoord2d(1.0,1.0); glVertex2i(64,0);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}

// Draw the pipe in lines and polys
void drawPipe()
{
	reset();
	
	// Scale and position
	glScalef(2.5,2.5,2.5);
	glTranslatef(200.0,25.75,0);
	
	// Background green top in quads
	glColor3ub(184,248,24);
	//glLineWidth(4);
	glBegin(GL_QUADS);
	glVertex2i(0,32);
	glVertex2i(32,32);
	glVertex2i(32,17);
	glVertex2i(0,17);
	glEnd();
	
	// background green bottom with a rectangle
	glRecti(2,0,30,16);
	
	// Use a thick line width
	glLineWidth(4);
	
	//dark green quads
	glColor3ub(0,171,0);
	glBegin(GL_QUADS);
	glVertex2i(15,30);
	glVertex2i(25,30);
	glVertex2i(25,17);
	glVertex2i(15,17);
	glEnd();
	
	glBegin(GL_QUADS);
	glVertex2i(16,16);
	glVertex2i(24,16);
	glVertex2i(24,0);
	glVertex2i(16,0);
	glEnd();
	
	
	// dark green lines
	glBegin(GL_LINES);
	glVertex2i(1,30);
	glVertex2i(6,30);
	glVertex2i(4,30);
	glVertex2i(4,17);
	glVertex2i(5,30);
	glVertex2i(5,17);
	glVertex2i(7,16);
	glVertex2i(7,0);
	glVertex2i(8,16);
	glVertex2i(8,0);
	glVertex2i(13,16);
	glVertex2i(13,0);
	glVertex2i(12,17);
	glVertex2i(12,30);
	glVertex2i(11,30);
	glVertex2i(31,30);
	glEnd();
	
	//dark green stipple lines, little thinner
	glLineWidth(2);
	glLineStipple(1, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2i(25,30);
	glVertex2i(25,17);
	glVertex2i(26,31);
	glVertex2i(26,17);
	glVertex2i(27,30);
	glVertex2i(27,17);
	glVertex2i(28,31);
	glVertex2i(28,17);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	
	// Back to thick lines
	glLineWidth(4);
	
	// Polygon stipple for the bottom checker pattern
	glEnable( GL_POLYGON_STIPPLE );
	glPolygonStipple( pattern ); 
	glBegin(GL_POLYGON);
	glVertex2i(24,17);
	glVertex2i(26,17);
	glVertex2i(26,0);
	glVertex2i(24,0);
	glEnd();
	glDisable( GL_POLYGON_STIPPLE );
	
	
	// top black outline, line loop
	glColor3ub(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(0,32);
	glVertex2i(32,32);
	glVertex2i(32,17);
	glVertex2i(0,17);
	glEnd();
	
	// bottom black outline, line strip
	glBegin(GL_LINE_STRIP);
	glVertex2i(2,0);
	glVertex2i(2,16);
	glVertex2i(30,16);
	glVertex2i(30,0);
	
	glEnd();
}

// Draw the bricks
void drawBricks()
{
	reset();
	
	// Scale and position
	glScalef(1.2,1.2,1.2);
	glTranslatef(150.0,175.0,0);

	// Draw the left two bricks using triangles
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, brickTexture);
	glBegin (GL_TRIANGLES);
	glTexCoord2d(0.0,0.0); glVertex2i(0,32);
	glTexCoord2d(0.0,1.0); glVertex2i(0,0);
	glTexCoord2d(2.0,0.0); glVertex2i(64,32);
	glTexCoord2d(0.0,1.0); glVertex2i(0,0);
	glTexCoord2d(2.0,0.0); glVertex2i(64,32);
	glTexCoord2d(2.0,1.0); glVertex2i(64,0);
	glEnd();
	
	// Draw the brick on the far right using polygons
	glTranslatef(96.0,0.0,0.0);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex2i(0,32);
	glTexCoord2d(1.0,0.0); glVertex2i(32,32);
	glTexCoord2d(1.0,1.0); glVertex2i(32,0);
	glTexCoord2d(0.0,1.0); glVertex2i(0,0);
	glEnd();
	
	// Move the question brick (and the coin) a bit if mario hit it
	if (jumpMaxReached && marioY > MARIO_START_Y + (3*(MARIO_STOP_Y - MARIO_START_Y)/4))
	{
		glTranslatef(0.0,4.0,0);
	}
	
	// Draw the question block
	glTranslatef(-32.0,0.0,0);
	glBindTexture (GL_TEXTURE_2D, currentQBlockTexture);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex2i(0,32);
	glTexCoord2d(1.0,0.0); glVertex2i(32,32);
	glTexCoord2d(1.0,1.0); glVertex2i(32,0);
	glTexCoord2d(0.0,1.0); glVertex2i(0,0);
	glEnd();
	
	// Draw the coin if mario just hit the block
	if (jumpMaxReached)
	{
		GLint coinHeight = MARIO_STOP_Y-marioY;
		
		if (coinHeight < (MARIO_STOP_Y - MARIO_START_Y) / 4)
		{
			glBindTexture (GL_TEXTURE_2D, coinTexture1);
		}
		else if (coinHeight < (MARIO_STOP_Y - MARIO_START_Y) / 2)
		{
			glBindTexture (GL_TEXTURE_2D, coinTexture2);
		}
		else if (coinHeight < 3*((MARIO_STOP_Y - MARIO_START_Y) / 4))
		{
			glBindTexture (GL_TEXTURE_2D, coinTexture3);
		}
		else
		{
			glBindTexture (GL_TEXTURE_2D, coinTexture4);
		}
	
		glTranslatef(0.0,32.0+coinHeight,0);
		glBegin (GL_POLYGON);
		glTexCoord2d(0.0,0.0); glVertex2i(0,32); 
		glTexCoord2d(1.0,0.0); glVertex2i(32,32); 
		glTexCoord2d(1.0,1.0); glVertex2i(32,0);
		glTexCoord2d(0.0,1.0); glVertex2i(0,0);
		glEnd();
	}
	
	glDisable(GL_TEXTURE_2D);
}

// Draw the blocks to the right of the pipe
void drawBlocks()
{
	reset();
	
	// Translate and scale
	glTranslatef(580.0,64.0,0);
	glScalef(1.2,1.2,1.2);

	// Draw one block a triangle strip
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, blockTexture);
	glBegin (GL_TRIANGLE_STRIP);
	glTexCoord2d(0.0,0.0); glVertex2i(0,32); //with our vertices we have to assign a texcoord
	glTexCoord2d(0.0,1.0); glVertex2i(0,0);
	glTexCoord2d(1.0,0.0); glVertex2i(32,32); //so that our texture has some points to draw to
	glTexCoord2d(1.0,1.0); glVertex2i(32,0);
	glEnd();
	
	// Draw the other two blocks with a polygon
	glTranslatef(32.0,0.0,0);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex2i(0,64); //with our vertices we have to assign a texcoord
	glTexCoord2d(1.0,0.0); glVertex2i(32,64); //so that our texture has some points to draw to
	glTexCoord2d(1.0,2.0); glVertex2i(32,0);
	glTexCoord2d(0.0,2.0); glVertex2i(0,0);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}


void display()
{
	// Clear the display
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw our scene
	drawSky();
	drawGround();
	drawBricks();
	drawBlocks();
	drawPipe();
	drawMario();
	
	// Swap the buffers (double buffered)
	glutSwapBuffers();
}

// This function does the animation for mario
void update(GLint timeElapsed)
{
	// Keep track of what frame we're on (not really using this anymore)
	frame++;
	
	if (frame >= 100)
	{
		frame = 0;
	}


	GLboolean refreshDisplay = 0;

	// If we're jumping
	if (jump)
	{
		// If we haven't reached the max height, keep going up
		if (!jumpMaxReached)
		{
			marioY += jumpIncrement;
			
			// if we just reached the max, turn around
			if (marioY > MARIO_STOP_Y)
			{
				jumpMaxReached = 1;
				
				StartMovie(coinSound);
			}
		}
		// If we have reached the max, go down
		else
		{
			marioY -= jumpIncrement;
			
			// If we're down, stop the jump
			if (marioY <= MARIO_START_Y)
			{
				marioY = MARIO_START_Y;
				jump = 0;
				jumpMaxReached = 0;
			}
		}
		
		refreshDisplay = 1;
	}
	
	// Make the block pulsate
	if (frame == 99)
	{
		if (blockFadeIn)
		{
			if (currentQBlockTexture == qblockTexture1)
			{
				currentQBlockTexture = qblockTexture2;
			}
			else if (currentQBlockTexture == qblockTexture2)
			{
				currentQBlockTexture = qblockTexture3;
				blockFadeIn = 0;
			}
		}
		else
		{
			if (currentQBlockTexture == qblockTexture1)
			{
				currentQBlockTexture = qblockTexture3;
			}
			else if (currentQBlockTexture == qblockTexture2)
			{
				currentQBlockTexture = qblockTexture1;
				blockFadeIn = 1;
			}
			else if (currentQBlockTexture == qblockTexture3)
			{
				currentQBlockTexture = qblockTexture2;
			}
		}
		
		
		refreshDisplay = 1;
	}
	
	if (refreshDisplay)
	{
		// Refresh our display
		glutPostRedisplay();
	}
	
	if (IsMovieDone(jumpSound)) { 
		GoToBeginningOfMovie(jumpSound); 
		//StartMovie(jumpSound);
		StopMovie(jumpSound);
	}
	
	if (IsMovieDone(coinSound)) { 
		GoToBeginningOfMovie(coinSound); 
		//StartMovie(coinSound);
		StopMovie(coinSound);
	}

	
	// Timer function so we can do the animation over time
	glutTimerFunc(timerDelay, update, 0);
}

// If the left mouse button is down, start a jump
void handleMouse(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		jump = 1;
		StartMovie(jumpSound);
		
	}
}

// Used reference about quicktime audio/video playback from http://www.meandmark.com/quicktimepart1.html
Movie setUpSound(const char *filenameCStr, const char *extension )
{
	// Treat the sound as a movie
	Movie soundToPlay;
	
	// Main application bundle?  idk what that means
	CFBundleRef gameBundle = CFBundleGetMainBundle();
	
	// Filename and extension in some fancy datatype
	CFStringRef filename = CFStringCreateWithCString(kCFAllocatorDefault, filenameCStr, GetApplicationTextEncoding());
	CFStringRef fileExtension = CFStringCreateWithCString(kCFAllocatorDefault, extension, GetApplicationTextEncoding());
	
	// not using this
	CFStringRef subdirectory; 
	
	OSErr error; // error status
	
    // Find the file in the application bundle.
    CFURLRef movieFileLocation;
    movieFileLocation = CFBundleCopyResourceURL(gameBundle, filename, fileExtension, subdirectory); 
    
	// Skip out if there's an error
    if (movieFileLocation == NULL)
	{
        return NULL;
	}
    
    Handle dataRef;	// The data
    OSType dataRefType;	// Not really sure?
    
	// memory allocation?
    dataRef = NewHandle(sizeof(AliasHandle));
    
    // Get the movie file set up so we can load it in memory.
    error = QTNewDataReferenceFromCFURL(movieFileLocation, 0, &dataRef, &dataRefType);
    if(error != noErr) {
        DisposeHandle(dataRef);
        CFRelease(movieFileLocation);
        return NULL;
    }
    
    // Get the movie into memory
    short fileID = movieInDataForkResID;
    short flags = 0;
    error = NewMovieFromDataRef(&soundToPlay, flags, &fileID, dataRef, dataRefType);
    
    // Dispose of the memory we allocated.
    DisposeHandle(dataRef);
    CFRelease(movieFileLocation);
	
	// Delay first time sound is played, get it out of the way now, but turn the volume off first, then back on
	short currentVolume = GetMovieVolume(soundToPlay);
	SetMovieVolume(soundToPlay, 0);
	StartMovie(soundToPlay);
	GoToBeginningOfMovie(soundToPlay); 
	StopMovie(soundToPlay);
	SetMovieVolume(soundToPlay, currentVolume);
	
	return soundToPlay;
}

int main(int argc, char**argv)
{
	// Set up glut and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Click for coins");

	// Load the textures
	cloudTexture = loadTexture("cloud.raw", 128, 64);
	groundTexture = loadTexture("ground.raw", 16, 16);
	brickTexture = loadTexture("bricks.raw", 32, 32);
	qblockTexture1 = loadTexture("qblock1.raw", 32, 32);
	qblockTexture2 = loadTexture("qblock2.raw", 32, 32);
	qblockTexture3 = loadTexture("qblock3.raw", 32, 32);
	bushTexture = loadTexture("bush.raw", 64, 32);
	blockTexture = loadTexture("block.raw", 32, 32);
	jumpTexture = loadTexture("jump.raw", 64, 64);
	coinTexture1 = loadTexture("coin1.raw", 32,32);
	coinTexture2 = loadTexture("coin2.raw", 32,32);
	coinTexture3 = loadTexture("coin3.raw", 32,32);
	coinTexture4 = loadTexture("coin4.raw", 32,32);
	
	currentQBlockTexture = qblockTexture1;
	
	// Set the graphics up
	init();
	
	// Call this to allow for audio playback
	EnterMovies();
	
	// Load the sounds
	jumpSound = setUpSound("jump","wav");
	coinSound = setUpSound("coin", "wav");
	
	// Set our display function
	glutDisplayFunc(display);
	
	// Timer function 
	glutTimerFunc(timerDelay, update, 0);
	
	// Handle mouse input with this function
	glutMouseFunc(handleMouse);
	
	// Start the main loop
	glutMainLoop();
	
	// Delete our textures when we're done
	// Is this really going to get executed?
	glDeleteTextures( 1, &cloudTexture );
	glDeleteTextures( 1, &groundTexture );
	glDeleteTextures( 1, &brickTexture );
	glDeleteTextures( 1, &qblockTexture1 );
	glDeleteTextures( 1, &qblockTexture2 );
	glDeleteTextures( 1, &qblockTexture3 );
	glDeleteTextures( 1, &bushTexture );
	glDeleteTextures( 1, &blockTexture );
	glDeleteTextures( 1, &jumpTexture );
	glDeleteTextures( 1, &coinTexture1);
	glDeleteTextures( 1, &coinTexture2);
	glDeleteTextures( 1, &coinTexture3);
	glDeleteTextures( 1, &coinTexture4);
}

