//
//  RamMemorySource.h
//  GameEngine
//
//  Created by Joseph Conley on 11/3/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_RamMemorySource_h
#define GameEngine_RamMemorySource_h

#include "Types.h"
#include "Assert.h"

#include <cstdlib>  // For malloc and free

// Just a simple malloc/free wrapper
class RamMemorySource
{
public:	
	void* malloc(u32 size_bytes)
	{
		void* pointerToMemory = std::malloc(size_bytes);
		
		ASSERT(pointerToMemory, "Unable to allocate %d bytes: out of memory", size_bytes);
		
		return pointerToMemory;
	}
	
	void free(void* pointerToFree)
	{
		ASSERT(pointerToFree, "Passed NULL pointer to free!");
		
		std::free(pointerToFree);
	}
};

#endif
