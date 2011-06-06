//
//  GameManager.h
//  SimpleSample
//
//  Created by NoEvilPeople on 5/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _GAME_MANAGER_H
#define	_GAME_MANAGER_H

#import <QuartzCore/QuartzCore.h>

#include <OpenGLES/EAGL.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include "singleton.h"



class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

public:
    
	GameManager(void);
    
	void Init(EAGLContext* pContext, GLuint renderBuffer, GLuint frameBuffer, GLuint depthBuffer, CGRect bounds);
    
	void Destroy(void);
    
	void Update(void);		
    	
};

#endif	/* _TESTCLASS_H */