/*
 *  test_class.h
 *  SimpleSample
 *
 *  Created by nacho on 27/08/09.
 *  Copyright 2009 Ignacio Sanchez Gines. All rights reserved.
 *
 */

#ifndef _TESTCLASS_H
#define	_TESTCLASS_H

#import <QuartzCore/QuartzCore.h>

#include <OpenGLES/EAGL.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include "singleton.h"


class TestClass : public Singleton<TestClass>
{
	friend class Singleton<TestClass>;
	
private:
	
	EAGLContext* m_pContext;
    GLuint m_uiViewRenderbuffer;
    GLuint m_uiViewFramebuffer;
    GLuint m_uiDepthRenderbuffer;
	
public:
		
	TestClass(void);
		
	void Init(EAGLContext* pContext, GLuint renderBuffer, GLuint frameBuffer, GLuint depthBuffer, CGRect bounds);
    
	void Cleanup(void);
		
	void Update(void);		
    
     GLfloat accelX;
     GLfloat accelY;
     GLfloat accelZ;
    
    GLboolean doOrientation;
	
private:
    
    void setupTextures(void);
    void setupLights(void);
	
	void BeginRender(void);
	void EndRender(void);
	
	void DrawSomething(void);
    void drawTetra(void);
    
    void drawTexture(void);
    
    GLuint texture[1];
};

#endif	/* _TESTCLASS_H */