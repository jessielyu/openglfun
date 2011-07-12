//
//  Assert.cpp
//  GameEngine
//
//  Created by NoEvilPeople on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Assert.h"
#include <stdarg.h>
#include <stdio.h>

void Assert(const char* file, const char* function, const int line, bool condition, const char* format, ...)
{
	if (!condition)
	{
		// Print out "meta" information
		printf("File: %s\n", file);
		printf("Function: %s() Line:%d\n", function, line);
		
		printf("Assert Text: ");
		// Pass format string and variable arguments to printf
		va_list argptr;
		va_start(argptr, format);
		vfprintf(stderr, format, argptr);
		va_end(argptr);
		
		printf("\n");
		
		// Halt execution
		asm("trap");
	}
}