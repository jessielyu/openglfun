//
//  PoolAllocator.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Types.h"

class PoolAllocator
{
public:
	
	// Allocate a new pool of total size poolSize in bytes, and of individual block size of blockSize, also in bytes
	PoolAllocator(u32 poolSize_bytes, u32 blockSize_bytes);
	
	// Deallocate 
	~PoolAllocator();
	
	// Return a block from the free list for use
	void* useBlock();
	
	// Put an unused block back on the free list
	bool freeBlock(void* ptr);
	
private:
	
	void* mPoolStart;		// Starting memory address of the pool
	
	u32 mPoolSize;			// Size of the pool (in total)
	u32 mBlockSize;			// Size of the individual blocks in the pool
	
	u32* mFreeListStart;	// Start of the free list
	//void* freeListEnd;		// End of the free list
};