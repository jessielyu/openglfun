//
//  DefragmentableHeapAllocator.cpp
//  GameEngine
//
//  Created by Joseph Conley on 7/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DefragmentableHeapAllocator.h"

#include "RamMemorySource.h"
#include "SmartPointer.h"

// Just call our underlying heap constructor
DefragmentableHeapAllocator::DefragmentableHeapAllocator(u32 size_bytes)
: heap(size_bytes)
{
	
}

DefragmentableHeapAllocator::~DefragmentableHeapAllocator()
{
	// Nothing to do here
}

// Put an unused block back on the free list
bool DefragmentableHeapAllocator::freeBlock(SmartPointer<void>* ptr) 
{	
	bool success = heap.freeBlock(ptr->get());
	return SmartPointerAllocator::Instance().freeSmartPointer(ptr) & success;
}

SmartPointer<void>* DefragmentableHeapAllocator::useBlock(u32 requestedSize_bytes)
{
	SmartPointer<void>* ptr = SmartPointerAllocator::Instance().allocateSmartPointer();
	ptr->reset(heap.useBlock(requestedSize_bytes));
	return ptr;
}

// If possible, push one block of allocated memory down into previously freed space, eliminating a gap between allocated memory
bool DefragmentableHeapAllocator::defragmentOneBlock()
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
	HeapAllocator<RamMemorySource>::UsedBlockInfo* real_ptr = (HeapAllocator<RamMemorySource>::UsedBlockInfo*) ((u32)lowestFragmentedBlock->get() - sizeof(HeapAllocator<RamMemorySource>::UsedBlockInfo)); 
	
	// New location
	HeapAllocator<RamMemorySource>::UsedBlockInfo* newStart = (HeapAllocator<RamMemorySource>::UsedBlockInfo*) heap.mFreeListStart;
	
	u32 usedBlockSize = real_ptr->size;
	u32 freeBlockSize = heap.mFreeListStart->size;
	
	ASSERT(freeBlockSize >= sizeof(HeapAllocator<RamMemorySource>::FreeBlockInfo), "Size must be >= sizeof(FreeBlockInfo) (%d bytes)", sizeof(HeapAllocator<RamMemorySource>::FreeBlockInfo));
		
	// Take this block off the free list
	heap.mFreeListStart = heap.mFreeListStart->next_ptr;
	
	// Actually move the memory
	memmove(newStart, real_ptr, usedBlockSize + sizeof(HeapAllocator<RamMemorySource>::UsedBlockInfo));
	
	// Adjust SmartPointer
	void* newAddressToReturn = (void*) (((u32)newStart) + sizeof(HeapAllocator<RamMemorySource>::UsedBlockInfo));
	lowestFragmentedBlock->reset(newAddressToReturn);
		
	// Create a new used block info to aid in freeing
	HeapAllocator<RamMemorySource>::UsedBlockInfo* usedBlockToFree = (HeapAllocator<RamMemorySource>::UsedBlockInfo*)(((u32)newAddressToReturn) + usedBlockSize);
	usedBlockToFree->size = freeBlockSize - sizeof(HeapAllocator<RamMemorySource>::UsedBlockInfo);
	
	// Actually free the memory
	void* addressToFree = (void*) (((u32)usedBlockToFree) + sizeof(HeapAllocator<RamMemorySource>::UsedBlockInfo));
	heap.freeBlock(addressToFree);
	
	return true;
}