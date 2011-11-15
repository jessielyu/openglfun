//
//  DefragmentableHeapAllocator.h
//  GameEngine
//
//  Created by Joseph Conley on 7/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_DefragmentableHeapAllocator_h
#define GameEngine_DefragmentableHeapAllocator_h

#include "HeapAllocator.h"

template <class T>
class SmartPointer;

#include "RamMemorySource.h"

class DefragmentableHeapAllocator
{
public:
	// Allocate a new defragmentable heap of size size_bytes
	DefragmentableHeapAllocator(u32 size_bytes);
	
	// Deallocate 
	~DefragmentableHeapAllocator();
	
	// Return a block from the free list for use
	SmartPointer<void>* useBlock(u32 requested_size_bytes);
	
	// Put an unused block back on the free list
	bool freeBlock(void* ptr);
	
	// Put an unused block back on the free list
	bool freeBlock(SmartPointer<void>* ptr);
	
	// Print out contents of free list
	void printFreeList() const {heap.printFreeList();}
	
	// Move one block up
	bool defragmentOneBlock();
	
	
private:
	
	HeapAllocator<RamMemorySource> heap;		// Building on top of the basic functionality of a Heap Allocator
};

#endif
