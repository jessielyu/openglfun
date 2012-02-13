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
#include "SmartPointer.h"

template <class MemorySource>
class DefragmentableHeapAllocator
{
	// Can't use these type names directly, must define them like this
	typedef typename HeapAllocator<MemorySource>::UsedBlockInfo UsedBlockType;
	typedef typename HeapAllocator<MemorySource>::FreeBlockInfo FreeBlockType;
	
public:
	// Allocate a new defragmentable heap of size size_bytes
	// Just call our underlying heap constructor
	DefragmentableHeapAllocator(u32 size_bytes, u32 baseAlignment = 0)
	: heap(size_bytes, baseAlignment)
	{
		
	}
	
	~DefragmentableHeapAllocator()
	{
		
	}
	
	// Return a block from the free list for use
	SmartPointer<void>* useBlock(u32 requestedSize_bytes)
	{
		SmartPointer<void>* ptr = SmartPointerAllocator::Instance().allocateSmartPointer();
		ptr->reset(heap.useBlock(requestedSize_bytes));
		return ptr;
	}
	
//	// Put an unused block back on the free list
//	bool freeBlock(void* ptr);
	
	// Put an unused block back on the free list
	bool freeBlock(SmartPointer<void>* ptr) 
	{	
		bool success = heap.freeBlock(ptr->get());
		return SmartPointerAllocator::Instance().freeSmartPointer(ptr) && success;
	}
	
	// Print out contents of free list
	void printFreeList() const {heap.printFreeList();}
	
	// Move one block up
	// If possible, push one block of allocated memory down into previously freed space, eliminating a gap between allocated memory
	bool defragmentOneBlock()
	{
		if (!heap.mFreeListStart)
		{
			// No free memory, so no fragmentation
			LOG("All memory allocated, no free space to defragment.");
			return false;
		}
		
		// Find the lowest fragmented block
		SmartPointer<void>* lowestFragmentedBlock = SmartPointerAllocator::Instance().getLowestAddressPointerBetween((u32)heap.mFreeListStart, (u32)heap.mHeapStart + (u32)heap.mHeapSize);
		
		if (!lowestFragmentedBlock)
		{
			// Heap not fragmented
			LOG("Defragmentation complete.");
			return false;
		}
		
		// Push the ptr back by sizeof(UsedBlockInfo) to get the meta data
		UsedBlockType* real_ptr = (UsedBlockType*) ((u32)lowestFragmentedBlock->get() - sizeof(UsedBlockType)); 
		
		// New location
		UsedBlockType* newStart = (UsedBlockType*) heap.mFreeListStart;
		
		u32 usedBlockSize = real_ptr->size;
		u32 freeBlockSize = heap.mFreeListStart->size;
		
		ASSERT(freeBlockSize >= sizeof(FreeBlockType), "Size must be >= sizeof(FreeBlockInfo) (%d bytes)", sizeof(FreeBlockType));
		
		// Take this block off the free list
		heap.mFreeListStart = heap.mFreeListStart->next_ptr;
		
		// Actually move the memory
		memmove(newStart, real_ptr, usedBlockSize + sizeof(UsedBlockType));
		
		// Adjust SmartPointer
		void* newAddressToReturn = (void*) (((u32)newStart) + sizeof(UsedBlockType));
		lowestFragmentedBlock->reset(newAddressToReturn);
		
		// Create a new used block info to aid in freeing
		UsedBlockType* usedBlockToFree = (UsedBlockType*)(((u32)newAddressToReturn) + usedBlockSize);
		usedBlockToFree->size = freeBlockSize - sizeof(UsedBlockType);
		
		// Actually free the memory
		void* addressToFree = (void*) (((u32)usedBlockToFree) + sizeof(UsedBlockType));
		heap.freeBlock(addressToFree);
		
		return true;
	}
	
	
private:
	
	HeapAllocator<MemorySource> heap;		// Building on top of the basic functionality of a Heap Allocator
};

#endif
