//
//  Memory.cpp
//  GameEngine
//
//  Created by NoEvilPeople on 6/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Memory.h"
#include "Assert.h"

void* operator new (size_t size) throw(std::bad_alloc)
{
    void* p = malloc(size);
	    
    // Did malloc fail?
    if (p==0)
    {
        // uh oh
		ASSERT(p, "out of memory");
    }
    
    return p;
}

void* operator new[](size_t size) throw(std::bad_alloc)
{
	void* p = malloc(size); // correct?
	
	// Did malloc fail?
    if (p==0)
    {
        // uh oh
		ASSERT(p, "out of memory");
    }
    
    return p;
}

void operator delete (void* p) throw()
{
    free(p);
}

void operator delete[] (void* p) throw()
{
	free(p);
}