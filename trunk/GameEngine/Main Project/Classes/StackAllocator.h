//
//  StackAllocator.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Types.h"

class StackAllocator
{
public:
	// Stack marker (current top of the stack)
	// NOTE: You can only roll back to a marker, not to arbitrary locations
	typedef u32 Marker;
    
    // New stack allocator with given size
	explicit StackAllocator(u32 stackSize_bytes);
	
	~StackAllocator();
	
	// New block of given size from top of stack
	void* alloc(u32 size_bytes);
	
	// Get the current top of the stack
	Marker getMarker() {return mCurrentTop;}
	
	// Roll stack back to a previous marker
	void freeToMarker(Marker marker);
	
	// Clears the entire stack
	void clear();
	
private:

	Marker mCurrentTop;	// Current top of the stack
	
	Marker mBase;	// Bottom of the stack
	
	Marker mMax;	// Bottom + stackSize_bytes
};