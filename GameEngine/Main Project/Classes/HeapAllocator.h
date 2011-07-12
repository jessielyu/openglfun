//
//  HeapAllocator.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Types.h"

class HeapAllocator
{
public:
	
	// Allocate a new heap of size size_bytes
	HeapAllocator(u32 size_bytes);
	
	// Deallocate 
	~HeapAllocator();
	
	// Return a block from the free list for use
	void* useBlock(u32 requested_size_bytes);
	
	// Put an unused block back on the free list
	bool freeBlock(void* ptr);
	
private:
	
	// Struct for tracking free blocks of memory
	struct FreeBlockInfo
	{
		FreeBlockInfo* next_ptr;
		u32 size;
	};
	
	// Struct for tracking used blocks of memory
	struct UsedBlockInfo
	{
		u32 size;
	};
	
	// Find next sufficiently large memory block
	FreeBlockInfo* findNextSufficientlyLargeBlock(FreeBlockInfo* startBlock, u32 necessarySize, FreeBlockInfo*& prev_ptr);
	
	void* mHeapStart;		// Starting memory address of the heap
	
	u32 mHeapSize;			// Size of the pool (in total)
	
	FreeBlockInfo* mFreeListStart;	// Start of the free list
};