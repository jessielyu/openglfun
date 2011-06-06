/*
 *  test_class.cpp
 *  SimpleSample
 *
 *  Created by nacho on 27/08/09.
 *  Copyright 2009 Ignacio Sanchez Gines. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>
#include "test_class.h"
#include "OpenGLCommon.h"
#include "ConstantsAndMacros.h"

TestClass::TestClass(void)
{
}

/////////////////////////////////////
/////////////////////////////////////

void TestClass::Init(EAGLContext* pContext, GLuint renderBuffer, GLuint frameBuffer, GLuint depthBuffer, CGRect bounds)
{    
	m_pContext = pContext;
    m_uiViewRenderbuffer = renderBuffer;
    m_uiViewFramebuffer = frameBuffer;
    m_uiDepthRenderbuffer = depthBuffer;
    
    const GLfloat zNear = 0.01f, zFar = 1000.0f, fieldOfView = 45.0f;
    GLfloat size;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glDisable(GL_ALPHA);
    
    glMatrixMode(GL_PROJECTION);
    size = zNear * tanf(DEGREES_TO_RADIANS(fieldOfView) / 2.0f);
    
    GLfloat boundsWidthOverHeight = (bounds.size.width / bounds.size.height);
    
    glFrustumf(-size, size, -size / boundsWidthOverHeight, 
               size / boundsWidthOverHeight, zNear, zFar);
    
    doOrientation = false;
    

    // ORTHO projection
//    float aspect = (bounds.size.width / bounds.size.height);
//    
//    glOrthof(-1.0f, 1.0f, 
//             -1.0f / aspect, 
//             1.0f / aspect, 0.01, 10000.0f);

    glViewport(0, 0, bounds.size.width, bounds.size.height);
    
    glMatrixMode(GL_MODELVIEW);
    
    setupTextures();
    setupLights();
}

void TestClass::setupLights(void)
{
    glEnable(GL_LIGHTING);
    
    // Light 0
    glEnable(GL_LIGHT0);
    
    // Ambient
    const GLfloat light0Ambient[] = {0.1f,0.1f,0.1f,1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    
    // Diffuse
    const GLfloat light0Diffuse[] = {0.7f,0.7f,0.7f,1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    
    // Specular
    const GLfloat light0Specular[] = {0.7f,0.7f,0.7f,1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    
    // Shininess?
   // const GLfloat light0Shininess = 0.4f;
    
    // Position
    const Vertex3D light0Position[] = {0.0f,0.0f,-0.6f};
    glLightfv(GL_LIGHT0, GL_POSITION, (const GLfloat *)light0Position);
    
    // Calculate light vector so it points at the object
    const Vertex3D objectPoint[] = {{0.0, 0.0, 0.0}};
    const Vertex3D lightVector = Vector3DMakeWithStartAndEndPoints(light0Position[0], objectPoint[0]);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, (GLfloat *)&lightVector);
    
    // cutoff angle
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 1.0f);
}

void TestClass::setupTextures()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_SRC_COLOR);
    
    
    glGenTextures(1, texture);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"hw" ofType:@"png"];
    NSData *texData =[[NSData alloc] initWithContentsOfFile:path];
    UIImage *image = [[UIImage alloc] initWithData:texData];
    if (image == nil)
    {
        NSLog(@"OH NOES! NO IMAGE!");
    }
    
    GLuint width = CGImageGetWidth(image.CGImage);
    GLuint height = CGImageGetHeight(image.CGImage);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void* imageData = malloc(height * width * 4);
    CGContextRef context = CGBitmapContextCreate(imageData, width, height, 8, 4*width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    CGContextClearRect(context, CGRectMake(0, 0, width, height));
    
    //Flip y-axis
    //CGContextTranslateCTM(context, 0, height);
    //CGContextScaleCTM(context, 1.0, -1.0);
    
    CGColorSpaceRelease(colorSpace);
    CGContextClearRect(context, CGRectMake(0, 0, width, height));
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), image.CGImage);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    CGContextRelease(context);
    
    free(imageData);
    [image release];
    [texData release];
}

/////////////////////////////////////
/////////////////////////////////////

void TestClass::Cleanup(void)
{
	///--- clean up something before exiting
}

/////////////////////////////////////
/////////////////////////////////////

void TestClass::Update(void)
{
	BeginRender();
	
	DrawSomething();    
    //drawTetra();
    //drawTexture();
	
	EndRender();
}

/////////////////////////////////////
/////////////////////////////////////

void TestClass::BeginRender(void)
{
	[EAGLContext setCurrentContext:m_pContext];
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uiViewFramebuffer);
    glViewport(0, 0, 768, 1024);
}

/////////////////////////////////////
/////////////////////////////////////

void TestClass::EndRender(void)
{
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_uiViewRenderbuffer);
    [m_pContext presentRenderbuffer:GL_RENDERBUFFER_OES];
}

/////////////////////////////////////
/////////////////////////////////////

void TestClass::DrawSomething(void)
{
    

    //static GLfloat rot = 0.0;
    
    glClearColor(1.0f, 0.596f, 0.0f, 1.0f);
    //glColor4f(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    static const Vertex3D vertices[] = {
        {-1.5,  1.0, -0.0},
        { 1.5,  1.0, -0.0},
        {-1.5, -1.0, -0.0},
        { 1.5, -1.0, -0.0}
    };
    
    static const Vector3D normals[] = {
        {-1.5, 1.0, 1.0},
        {1.5, 1.0, 1.0},
        {-1.5, -1.0, 1.0},
        {1.5, -1.0, 1.0}
    };
    
    // Feel free to comment these texture coordinates out and use one
    // of the ones below instead, or play around with your own values.
    static const GLfloat texCoords[] = {
        0.0, 1.0,
        1.0, 1.0,
        0.0, 0.0,
        1.0, 0.0
    };
    
    //    static const GLfloat texCoords[] = {
    //        0.25, 0.75,
    //        0.75, 0.75,
    //        0.25, 0.25,
    //        0.75, 0.25
    //    };
    //    
    //    static const GLfloat texCoords[] = {
    //        0.0, 1.0,
    //        1.0, 1.0,
    //        0.0, 0.0,
    //        1.0, 0.0
    //    };
    
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
    
    static GLfloat rotation = 180.0f;
    static GLfloat yRot = 180.0f;
    static GLfloat zRot = 180.0f;
    static GLfloat wRot = 0.0f;
    
    if (doOrientation)
    {
        glRotatef((1+(0.5*accelY))*(rotation), 1, 0, 0);
        
        glRotatef(90, 0, 0, 1);
        
        glRotatef(rotation - ((1-(0.5*accelX))*(rotation)), 1, 0, 0);
    }
    else
    {
        glRotatef(rotation, 1, 0, 0);
        
        glRotatef(90, 0, 0, 1);
        
        //glRotatef(rotation, 1, 0, 0);

    }
    
    //glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
    
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);    
    static NSTimeInterval lastDrawTime = 0;
    if (lastDrawTime)
    {
        NSTimeInterval timeSinceLastDraw = [NSDate timeIntervalSinceReferenceDate] - lastDrawTime;
        //rotation += 50 * timeSinceLastDraw;
    }
    lastDrawTime = [ NSDate timeIntervalSinceReferenceDate];
    
    GLint rb_binding, rb_wide, rb_high, rb_format;
    glGetIntegerv(GL_RENDERBUFFER_BINDING_OES, &rb_binding);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &rb_wide);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &rb_high);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_INTERNAL_FORMAT_OES, &rb_format);
    //    printf("Current renderbuffer %d is %dx%d, format %04x\n", rb_binding, rb_wide, rb_high, rb_format);
    
//    // Position
//    static const Vertex3D light0Position[] = {0.0f,10.0f,10.0f,0.0f};
//    glLightfv(GL_LIGHT0, GL_POSITION, (const GLfloat *)light0Position);
//    
//    // Calculate light vector so it points at the object
//    static const Vertex3D objectPoint[] = {{0.0, 0.0, -3.0}};
//    const Vertex3D lightVector = Vector3DMakeWithStartAndEndPoints(light0Position[0], objectPoint[0]);
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, (GLfloat *)&lightVector);
}

void TestClass::drawTetra()
{
    static GLfloat rot = 0.0;
    
    // This is the same result as using Vertex3D, just faster to type and
    // can be made const this way
    static const Vertex3D vertices[]= {
        {0, -0.525731, 0.850651},             // vertices[0]
        {0.850651, 0, 0.525731},              // vertices[1]
        {0.850651, 0, -0.525731},             // vertices[2]
        {-0.850651, 0, -0.525731},            // vertices[3]
        {-0.850651, 0, 0.525731},             // vertices[4]
        {-0.525731, 0.850651, 0},             // vertices[5]
        {0.525731, 0.850651, 0},              // vertices[6]
        {0.525731, -0.850651, 0},             // vertices[7]
        {-0.525731, -0.850651, 0},            // vertices[8]
        {0, -0.525731, -0.850651},            // vertices[9]
        {0, 0.525731, -0.850651},             // vertices[10]
        {0, 0.525731, 0.850651}               // vertices[11]
    };
    
    static const Color3D colors[] = {
        {1.0, 0.0, 0.0, 1.0},
        {1.0, 0.5, 0.0, 1.0},
        {1.0, 1.0, 0.0, 1.0},
        {0.5, 1.0, 0.0, 1.0},
        {0.0, 1.0, 0.0, 1.0},
        {0.0, 1.0, 0.5, 1.0},
        {0.0, 1.0, 1.0, 1.0},
        {0.0, 0.5, 1.0, 1.0},
        {0.0, 0.0, 1.0, 1.0},
        {0.5, 0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0, 1.0},
        {1.0, 0.0, 0.5, 1.0}
    };
    
    static const GLubyte icosahedronFaces[] = {
        1, 2, 6,
        1, 7, 2,
        3, 4, 5,
        4, 3, 8,
        6, 5, 11,
        5, 6, 10,
        9, 10, 2,
        10, 9, 3,
        7, 8, 9,
        8, 7, 0,
        11, 0, 1,
        0, 11, 4,
        6, 2, 10,
        1, 6, 11,
        3, 5, 10,
        5, 4, 11,
        2, 7, 9,
        7, 1, 0,
        3, 9, 8,
        4, 8, 0,
    };
    
    static const Vector3D normals[] = {
        {0.000000, -0.417775, 0.675974},
        {0.675973, 0.000000, 0.417775},
        {0.675973, -0.000000, -0.417775},
        {-0.675973, 0.000000, -0.417775},
        {-0.675973, -0.000000, 0.417775},
        {-0.417775, 0.675974, 0.000000},
        {0.417775, 0.675973, -0.000000},
        {0.417775, -0.675974, 0.000000},
        {-0.417775, -0.675974, 0.000000},
        {0.000000, -0.417775, -0.675973},
        {0.000000, 0.417775, -0.675974},
        {0.000000, 0.417775, 0.675973},
    };
    
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-3.0f);  
    glRotatef(rot,1.0f,1.0f,1.0f);
    glClearColor(0.7, 0.7, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
        glEnable(GL_COLOR_MATERIAL);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_BYTE, icosahedronFaces);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    //glDisable(GL_COLOR_MATERIAL);
    static NSTimeInterval lastDrawTime;
    if (lastDrawTime)
    {
        NSTimeInterval timeSinceLastDraw = [NSDate timeIntervalSinceReferenceDate] - lastDrawTime;
        rot+=50 * timeSinceLastDraw;                
    }
    lastDrawTime = [NSDate timeIntervalSinceReferenceDate];
}

void TestClass::drawTexture()
{
    
    static GLfloat rot = 0.0;
    
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    //glColor4f(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    static const Vertex3D vertices[] = {
        {-1.0,  1.0, -0.0},
        { 1.0,  1.0, -0.0},
        {-1.0, -1.0, -0.0},
        { 1.0, -1.0, -0.0}
    };
    
    static const Vector3D normals[] = {
        {-1.0,  1.0,    1.0},
        {1.0,   1.0,    1.0},
        {-1.0,  -1.0,   1.0},
        {1.0,   1.0,    1.0}
    };
    
    // Feel free to comment these texture coordinates out and use one
    // of the ones below instead, or play around with your own values.
    static const GLfloat texCoords[] = {
        0.0, 0.5,
        0.5, 0.5,
        0.0, 0.0,
        0.5, 0.0
    };
    
    //    static const GLfloat texCoords[] = {
    //        0.25, 0.75,
    //        0.75, 0.75,
    //        0.25, 0.25,
    //        0.75, 0.25
    //    };
    //    
    //    static const GLfloat texCoords[] = {
    //        0.0, 1.0,
    //        1.0, 1.0,
    //        0.0, 0.0,
    //        1.0, 0.0
    //    };
    
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
    glRotatef(rot, 1.0, 1.0, 1.0);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    static NSTimeInterval lastDrawTime;
    if (lastDrawTime)
    {
        NSTimeInterval timeSinceLastDraw = [NSDate timeIntervalSinceReferenceDate] - lastDrawTime;
        rot+=  60 * timeSinceLastDraw;                
    }
    lastDrawTime = [NSDate timeIntervalSinceReferenceDate];
}