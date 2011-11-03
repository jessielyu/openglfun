//
//  Assert.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_Assert_h
#define GameEngine_Assert_h

// Assert functionality only in debug
#ifdef DEBUG
#define ASSERT(x,y,...)	internal_Assert(__FILE__,__FUNCTION__,__LINE__,x,y,##__VA_ARGS__)
#else
#define ASSERT(x,y,...)
#endif

// Don't use me directly! Use the macro above
void internal_Assert(const char* file, const char* function, const int line, bool condition, const char* format, ...);

#endif