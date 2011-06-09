//
//  Assert.cpp
//  GameEngine
//
//  Created by NoEvilPeople on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Assert.h"
#include <stdio.h>

void ASSERT(bool condition, char* text)
{
	// TODO: Add filename and line number
	printf("%s\n", text);
	asm("trap");
}