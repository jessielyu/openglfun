//
//  StackAllocator.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_StackAllocator_h
#define GameEngine_StackAllocator_h

#include "Types.h"

#include <stdio.h>
#include "Assert.h"

template <class MemorySource>
class StackAllocator
{
public:
	// Stack marker (current top of the stack)
	// NOTE: You can only roll back to a marker, not to arbitrary locations
	typedef u32 Marker;
	
private:
	Marker	mCurrentTop;		// Current top of the stack
	Marker	mBase;				// Bottom of the stack
	Marker	mMax;				// Bottom + stackSize_bytes
	u32		mBaseAlignmentOffset;		// Base alignment of the stack
	
public:
	
	// Get the current top of the stack
	Marker getMarker() {return mCurrentTop;}
	
	StackAllocator(u32 stackSize_bytes, u32 baseAlignment = 0)
	:	mBase(NULL),
	mCurrentTop(NULL),
	mMax(NULL)
	{
		void* ptr;
		
		// If there is a an alignment requirement
		if (baseAlignment != 0)
		{
			// Allocate for the worst case, extra size equal to the alignment
			void* rawPtr = MemorySource::malloc(stackSize_bytes + baseAlignment);
			
			// Call a helper function to find the first aligned address in the range we allocated
			ptr = (void*) Helper::MemoryAlignment::alignAddress((u32)rawPtr, baseAlignment);
			
			// Store the offset so we know how much to free
			mBaseAlignmentOffset = ((u32)ptr) - ((u32)rawPtr);
		}
		else
		{
			// Allocate total bytes
			ptr = MemorySource::malloc(stackSize_bytes);
			
			// No alignment
			mBaseAlignmentOffset = 0;
		}
		
		// Did malloc fail?
		if (ptr==0)
		{
			// uh oh
			ASSERT(ptr, "Couldn't create StackAllocator: out of memory");
		}
		else
		{
			mBase = (Marker) ptr;
			mCurrentTop = mBase;
			mMax = mBase + stackSize_bytes;
		}
		
		//	printf("stack base to begin %X\n", mBase);
		//	printf("stack curtop to begin %X\n", mCurrentTop);
		//	printf("stack max to begin %X\n", mMax);
	}
	
	~StackAllocator()
	{
		if (mCurrentTop != mBase)
		{
			ASSERT(false, "StackAllocator Class deleted before all memory freed!");
		}
		
		void* ptrToFree = NULL;
		
		// If we had an alignment, push the address to free back to the start of the allocated memory
		ptrToFree = (void*)( ((u32)mBase) - mBaseAlignmentOffset );
		
		ASSERT(ptrToFree, "Can't release memory!");
		
		if (ptrToFree)
		{
			MemorySource::free((void*)ptrToFree);
		}
	}
	
	// New block of given size from top of stack
	void* alloc(u32 size_bytes)
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
	void freeToMarker(Marker marker)
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
	void clear()
	{
		mCurrentTop = mBase;
		
		ASSERT((void*)(mCurrentTop) != NULL, "StackAllocator::clear() mCurrentTop is NULL");
		
		//	printf("stack base after clear %X\n", mBase);
		//	printf("stack curtop after clear %X\n", mCurrentTop);
		//	printf("stack max after clear %X\n", mMax);
	}
};



#endif