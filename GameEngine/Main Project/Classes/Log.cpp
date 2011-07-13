//
//  Log.cpp
//  GameEngine
//
//  Created by NoEvilPeople on 7/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Log.h"
#include <stdarg.h>
#include <stdio.h>

void Log(const char* file, const char* function, const int line, bool printMetaInfo, const char* format, ...)
{
	if (printMetaInfo)
	{
		// Print out "meta" information
		printf("File: %s\n", file);
		printf("Function: %s() Line:%d\n", function, line);
		
		printf("Log Text: ");
		
	}
	
	// Pass format string and variable arguments to printf
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	
	printf("\n");
}