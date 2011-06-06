//
//  GameManager.cpp
//  SimpleSample
//
//  Created by NoEvilPeople on 5/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GameManager.h"


#import <UIKit/UIKit.h>
#include "test_class.h"
#include "OpenGLCommon.h"
#include "ConstantsAndMacros.h"
#include "test_class.h"

GameManager::GameManager(void)
{
    //test change
}

/////////////////////////////////////
/////////////////////////////////////

void GameManager::Init(EAGLContext* pContext, GLuint renderBuffer, GLuint frameBuffer, GLuint depthBuffer, CGRect bounds)
{
    TestClass::Instance().Init(pContext, renderBuffer, frameBuffer, depthBuffer, bounds);
}

/////////////////////////////////////
/////////////////////////////////////

void GameManager::Destroy(void)
{
	///--- clean up something before exiting
    TestClass::Instance().Cleanup();
}

/////////////////////////////////////
/////////////////////////////////////

void GameManager::Update(void)
{
    TestClass::Instance().Update();
}