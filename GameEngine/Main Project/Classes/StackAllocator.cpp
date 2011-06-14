//
//  StackAllocator.cpp
//  GameEngine
//
//  Created by NoEvilPeople on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <cstdlib>  // For malloc and free
#include <stdio.h>

#include "Assert.h"
#include "StackAllocator.h"

// New stack allocator with given size
StackAllocator::StackAllocator(u32 stackSize_bytes)
:	mBase(NULL),
	mCurrentTop(NULL),
	mMax(NULL)
{
	void* p = malloc(stackSize_bytes);
	
	// Did malloc fail?
    if (p==0)
    {
        // uh oh
		ASSERT(p, "StackAllocator: out of memory");
    }
    else
	{
		mBase = (Marker) p;
		mCurrentTop = mBase;
		mMax = mBase + stackSize_bytes;
	}
	
//	printf("stack base to begin %X\n", mBase);
//	printf("stack curtop to begin %X\n", mCurrentTop);
//	printf("stack max to begin %X\n", mMax);
}

StackAllocator::~StackAllocator()
{
	if (mCurrentTop != mBase)
	{
		ASSERT(false, "StackAllocator Class deleted before all memory freed!");
	}
	
	if (mBase)
	{
		free((void*)mBase);
	}
	else
	{
		ASSERT(mBase, "StackAllocator destructor: Memory could not be released!");
	}
}

// New block of given size from top of stack
void* StackAllocator::alloc(u32 size_bytes)
{
	if (!mBase || !mCurrentTop || !mMax)
	{
		ASSERT(false, "StackAllocator:: Pointer is NULL");
		return 0;
	}
	
	if (mMax < mCurrentTop + size_bytes)
	{
		ASSERT(false, "StackAllocator:: Out of memory");
		return 0;
	}
	
	Marker ret = mCurrentTop;
	
	mCurrentTop = mCurrentTop + size_bytes;
	
//	printf("stack base after %d byte alloc: %X\n", size_bytes, mBase);
//	printf("stack curtop after %d byte alloc: %X\n", size_bytes, mCurrentTop);
//	printf("stack max after %d byte alloc: %X\n", size_bytes, mMax);
	
	return (void*)ret;
}

// Roll stack back to a previous marker
void StackAllocator::freeToMarker(Marker marker)
{
	if (!mBase || !mCurrentTop || !mMax || !marker)
	{
		ASSERT(false, "StackAllocator:: Pointer is NULL");
		return;
	}
	
	if (marker < mBase || marker >= mMax)
	{
		ASSERT(false, "StackAllocator::freeToMarker:: marker is not in this stack");
		return;
	}
	
//	printf("stack base after freeToMarker %X\n", mBase);
//	printf("stack curtop after freeToMarker %X\n", mCurrentTop);
//	printf("stack max after freeToMarker %X\n", mMax);
		
	mCurrentTop = marker;
}

// Clears the entire stack
void StackAllocator::clear()
{
	mCurrentTop = mBase;
	
	ASSERT((void*)(mCurrentTop) != NULL, "StackAllocator::clear() mCurrentTop is NULL");
	
//	printf("stack base after clear %X\n", mBase);
//	printf("stack curtop after clear %X\n", mCurrentTop);
//	printf("stack max after clear %X\n", mMax);
}
	
