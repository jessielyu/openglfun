//
//  PoolAllocator.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_PoolAllocator_h
#define GameEngine_PoolAllocator_h

#include "Types.h"

#include <stdio.h>

#include "Assert.h"
#include "MemoryAlignment.h"

template <class MemorySource>
class PoolAllocator
{
private:
	
	void* mPoolStart;		// Starting memory address of the pool
	
	u32 mPoolSize;				// Size of the pool (in total)
	u32 mBlockSize;				// Size of the individual blocks in the pool
	u32 mBaseAlignmentOffset;	// How many bytes we moved up the base address to achieve the requested alignment (necessary for freeing)
	
	u32* mFreeListStart;		// Start of the free list
	
public:
	
	// Allocate a new pool of total size poolSize in bytes, and of individual block size of blockSize, also in bytes, with the base of the pool aligned to baseAlignment bytes
	PoolAllocator(u32 poolSize_bytes, u32 blockSize_bytes, u32 baseAlignment = 0)
	:	mPoolStart(NULL),
	mPoolSize(poolSize_bytes),
	mBlockSize(blockSize_bytes),
	mFreeListStart(NULL)
	{
		if (poolSize_bytes < blockSize_bytes)
		{
			ASSERT(false, "PoolAllocator: Specified pool size can not be less than block size");
			return;
		}
		
		if (poolSize_bytes % blockSize_bytes != 0)
		{
			ASSERT(false, "PoolAllocator: Specified pool size can not be evenly split up into the specified number of block bytes");
			return;
		}
		
		if (blockSize_bytes < sizeof(void*))
		{
			ASSERT(false, "PoolAllocator only supports block sizes >= sizeof(void*)");
			return;
		}
		
		void* ptr;
		
		// If there is a an alignment requirement
		if (baseAlignment != 0)
		{
			// Allocate for the worst case, extra size equal to the alignment
			void* rawPtr = MemorySource::malloc(poolSize_bytes + baseAlignment);
			
			// Call a helper function to find the first aligned address in the range we allocated
			ptr = (void*) Helper::MemoryAlignment::alignAddress((u32)rawPtr, baseAlignment);
			
			// Store the offset so we know how much to free
			mBaseAlignmentOffset = ((u32)ptr) - ((u32)rawPtr);
		}
		else
		{
			// Allocate total bytes
			ptr = MemorySource::malloc(poolSize_bytes);
			
			// No alignment
			mBaseAlignmentOffset = 0;
		}
		
		// Did malloc fail?
		if (ptr == 0)
		{
			// uh oh
			ASSERT(ptr, "out of memory");
		}
		
		// Keep track of the start address to free later
		mPoolStart = ptr;
		
		// For now, the start of the free list is the start of the pool
		mFreeListStart = (u32*) ptr;
		
		// Number of items in the pool is the pool size / item size
		u32 numPoolItems = poolSize_bytes / blockSize_bytes;
		
		// Memory address right after the pool
		void* endMemoryAddress = (void*)((u32)mPoolStart + (numPoolItems * blockSize_bytes));
		
		// if debug, 0 out all the memory
		// Maybe we don't want to bother to 0 out ALL the memory
		// But we need the last item in the free list to contain a pointer to NULL, so it at least has to be 0
		u32* temp_ptr = (u32*)ptr;
		while (temp_ptr != endMemoryAddress)
		{
			*temp_ptr = 0;
			
			++temp_ptr;
		}
		
		// Use the memory of each free block to store the address of the next free block
		while (ptr != (void*)((u32)endMemoryAddress - mBlockSize))	// Make sure to leave the last block NULL!
		{
			// Get a u32 reference to the start of the block
			u32& nextStorage = *(u32*) ptr;
			
			// Store the address of the next free block
			nextStorage = (u32)ptr + blockSize_bytes;
			
			// Now use this "pointer" we just saved to do the same thing with the next block
			ptr = (void*) nextStorage;
		}
	}

	
	// Deallocate 
	~PoolAllocator()
	{
		// If debug, verify all memory has been properly freed
		u32 count = 0;
		
		// Traverse the list, counting how many elements there are
		// Note: remember to set item's next pointers to NULL when returning them to the list
		while (mFreeListStart != NULL)
		{
			// Go to next item in the list
			mFreeListStart = (u32*)*mFreeListStart;
			
			++count;
		}
		
		// If count != total size / block size, some blocks were not returned to the free list
		if (count != mPoolSize / mBlockSize)
		{
			ASSERT(false, "PoolAllocator::~PoolAllocator: Not all memory has been freed!");
		}
		
		void* ptrToFree = NULL;
		
		// If we had an alignment, push the address to free back to the start of the allocated memory
		ptrToFree = (void*)( ((u32)mPoolStart) - mBaseAlignmentOffset );
		
		ASSERT(ptrToFree, "PoolAllocator destructor: Can't release memory!");
		
		// Free the pool memory
		if (ptrToFree)
		{
			MemorySource::free(ptrToFree);
		}
	}
	
	// Return a block from the free list for use
	void* useBlock()
	{
		if (mFreeListStart != NULL)
		{
			void* ptrToUse = (void*)mFreeListStart;
			
			// Equivalent to mFreeListStart = mFreeListStart->next;
			mFreeListStart = (u32*)*mFreeListStart;
			
			// Return previous start of list
			return ptrToUse;
		}
		
		ASSERT(mFreeListStart, "PoolAllocator: mFreeListStart is NULL. Out of memory.");
		return NULL;
	}
	
	// Put an unused block back on the free list
	bool freeBlock(void* ptr)
	{
		if (!ptr)
		{
			ASSERT(false, "StackAllocator:: Pointer is NULL");
			return false;
		}
		
		if (ptr < mPoolStart || ptr >= (void*)((u32)(mPoolStart) + mPoolSize))
		{
			ASSERT(false, "PoolAllocator::freeBlock: Block is not in this pool.");
			return false;
		}
		
		// Store mFreeListStart->next
		u32 newNext = (u32)mFreeListStart; // This should even work if mFreeListStart is NULL (the list is empty)
		
		// For development debug
		//	if (newNext < (u32)mPoolStart || newNext >= ((u32)(mPoolStart) + mPoolSize))
		//	{
		//		ASSERT(false, "PoolAllocator::freeBlock: Block is not in this pool.");
		//		return false;
		//	}
		
		// Append to the front of the list
		mFreeListStart = (u32*)ptr;
		
		// For development debug
		//	if (mFreeListStart < mPoolStart || mFreeListStart >= (void*)((u32)(mPoolStart) + mPoolSize))
		//	{
		//		ASSERT(false, "PoolAllocator::freeBlock: Block is not in this pool.");
		//		return false;
		//	}
		
		// This is where we store the next pointer
		u32& locationToWriteNextTo = *(u32*)ptr;
		
		// For development debug
		//	if ((u32)&locationToWriteNextTo < (u32)mPoolStart || (u32)&locationToWriteNextTo >= ((u32)(mPoolStart) + mPoolSize))
		//	{
		//		ASSERT(false, "PoolAllocator::freeBlock: Block is not in this pool.");
		//		return false;
		//	}
		
		// This is actually storing the next pointer
		locationToWriteNextTo = newNext;
		
		return false;
	}
	

};

#endif