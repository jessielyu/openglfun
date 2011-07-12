//
//  Assert.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

// Assert functionality only in debug
#ifdef DEBUG
#define ASSERT(x,y,...)	Assert(__FILE__,__FUNCTION__,__LINE__,x,y,##__VA_ARGS__)
#else
#define ASSERT(x,y,...)
#endif

void Assert(const char* file, const char* function, const int line, bool condition, const char* format, ...);