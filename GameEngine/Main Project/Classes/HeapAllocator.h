//
//  HeapAllocator.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_HeapAllocator_h
#define GameEngine_HeapAllocator_h

#include <stdio.h>

#include "Assert.h"
#include "Log.h"
#include "Types.h"

template <class MemorySource>
class HeapAllocator
{
	template <class T> friend class DefragmentableHeapAllocator;
	
public:
	
	// Allocate a new pool of total size poolSize in bytes, and of individual block size of blockSize, also in bytes
	HeapAllocator(u32 size_bytes, u32 baseAlignment = 0)
	:	mHeapStart(NULL),
	mHeapSize(size_bytes),
	mFreeListStart(NULL),
	mBaseAlignmentOffset(baseAlignment)
	{
		// Must be large enough to hold a pointer and a size
		if (size_bytes < sizeof(FreeBlockInfo))
		{
			ASSERT(size_bytes >= sizeof(FreeBlockInfo), "Size must be >= sizeof(FreeBlockInfo) (%d bytes)", sizeof(FreeBlockInfo));
			return;
		}
		
		void* ptr;
		
		// If there is a an alignment requirement
		if (baseAlignment != 0)
		{
			// Allocate for the worst case, extra size equal to the alignment
			void* rawPtr = MemorySource::malloc(size_bytes + baseAlignment);
			
			// Call a helper function to find the first aligned address in the range we allocated
			ptr = (void*) Helper::MemoryAlignment::alignAddress((u32)rawPtr, baseAlignment);
			
			// Store the offset so we know how much to free
			mBaseAlignmentOffset = ((u32)ptr) - ((u32)rawPtr);
		}
		else
		{
			// Allocate total bytes
			ptr = MemorySource::malloc(size_bytes);
			
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
		mHeapStart = ptr;
		
		// Memory address right after the pool
		void* endMemoryAddress = (void*)(((u32)mHeapStart) + (size_bytes));
		
		// Zero out all the memory
		// Maybe this should only happen in debug?
		u32* temp_ptr = (u32*)ptr;
		while (temp_ptr != endMemoryAddress)
		{
			*temp_ptr = 0;
			
			++temp_ptr;
		}
		
		// Fill out the information about the first (and only for the time being) free block
		// And store it at the start of the heap
		mFreeListStart = (FreeBlockInfo*) ptr;
		mFreeListStart->next_ptr = NULL;		// This is the start and end of the heap for now
		mFreeListStart->size = size_bytes;	// And it contains the entire heap for now
	}
	
	// Deallocate 
	~HeapAllocator()
	{
#ifdef DEBUG
		// Verify all memory has been properly freed
		u32 freeSpace = 0;
		
		// Traverse the list, counting how many elements there are
		// Note: remember to set item's next pointers to NULL when returning them to the list
		while (mFreeListStart != NULL)
		{
			//Add up free space
			freeSpace += mFreeListStart->size;
			
			// Go to next item in the list
			mFreeListStart = mFreeListStart->next_ptr;
		}
		
		// Ensure the free space now is the same as when the heap was created
		ASSERT(freeSpace == mHeapSize, "Not all memory has been freed!");
#endif
		
		void* ptrToFree = NULL;
		
		// If we had an alignment, push the address to free back to the start of the allocated memory
		if (mBaseAlignmentOffset != 0)
		{
			ptrToFree = (void*)( ((u32)mHeapStart) - mBaseAlignmentOffset );
		}
		else
		{
			ptrToFree = mHeapStart;
		}
		
		ASSERT(ptrToFree, "Can't release memory!");
		
		// Free the heap memory
		if (ptrToFree)
		{
			MemorySource::free(ptrToFree);
		}
	}
	
	// Return a block from the free list for use
	void* useBlock(u32 requested_size_bytes, u32 alignment = 0 )
	{
		ASSERT(mFreeListStart, "mFreeListStart is NULL! Out of Memory?");
		
		FreeBlockInfo* candidateBlock = mFreeListStart;
		FreeBlockInfo* candidateBlockPrev = NULL;
		
		u32 totalRequiredSize = requested_size_bytes + sizeof(UsedBlockInfo) + alignment;
		
		while (candidateBlock != NULL)
		{
			// If this block is large enough to fulfil the request
			// Exact size is fine
			if (candidateBlock->size == totalRequiredSize)
			{
				// Middle or end of the list
				if (candidateBlockPrev)
				{
					// Skip over this item in the list
					candidateBlockPrev->next_ptr = candidateBlock->next_ptr;
				}
				// Start of the list
				else
				{
					ASSERT(mFreeListStart == candidateBlock, "This pointer is expected to be the start of the list, but it's not.");
					
					// Move the start of the list
					mFreeListStart = candidateBlock->next_ptr;
				}
				
				break;
			}
			// But we don't want to leave less bits free than we need to store tracking information
			// If it is large enough, we split the current block and return part
			else if (candidateBlock->size - sizeof(FreeBlockInfo) >= totalRequiredSize)
			{			
				// Create a new block at the location of the start of the current block moved up by the required size
				FreeBlockInfo* newBlockFromRemainder = (FreeBlockInfo*) (((u32)candidateBlock) + totalRequiredSize);
				
				// For debug
				//ASSERT((void*)newBlockFromRemainder > mFreeListStart, "New block is before start of heap.");
				//ASSERT((u32)newBlockFromRemainder <= ((u32)mHeapStart) + mHeapSize, "New block starts after heap.");
				
				// Set new block's fields
				newBlockFromRemainder->size = candidateBlock->size - totalRequiredSize;
				newBlockFromRemainder->next_ptr = candidateBlock->next_ptr;
				
				// For debug
				//ASSERT( ((u32)newBlockFromRemainder) + newBlockFromRemainder->size <= ((u32)mHeapStart) + mHeapSize, "New block extends past end of heap.");
				
				// Middle or end of the list
				if (candidateBlockPrev)
				{
					// Point previous block to our new block
					candidateBlockPrev->next_ptr = newBlockFromRemainder;
				}
				// Start of the list
				else
				{
					ASSERT(mFreeListStart == candidateBlock, "This pointer is expected to be the start of the list, but it's not.");
					
					// Move the start of the list
					mFreeListStart = newBlockFromRemainder;
				}
				
				break;
			}
			// If the leftover portion of this block would be too small to track,
			// Just try the next block
			else
			{
				candidateBlock = findNextSufficientlyLargeBlock(candidateBlock->next_ptr, requested_size_bytes, candidateBlockPrev);
			}
		}
		
		void* ptrToRtn = NULL;
		
		// Ensure we have a block to return
		if (candidateBlock)
		{
			void* alignedPtr = NULL;
			u32 alignmentOffset = 0;
			
			ptrToRtn = (void*) (((u32)candidateBlock) + sizeof(UsedBlockInfo));
			
			// Handle requested alignment
			if (alignment)
			{
				alignedPtr = (void*) Helper::MemoryAlignment::alignAddress((u32)ptrToRtn, alignment);	
				alignmentOffset = ((u32)alignedPtr) - ((u32)ptrToRtn);
				ptrToRtn = alignedPtr;
			}
			
			// Store the requested size and alignment offset for freeing later
			UsedBlockInfo* usedBlockInfo = (UsedBlockInfo*) (((u32)candidateBlock) + alignmentOffset);
			
			// For Debug
			//ASSERT((u32)usedBlockInfo == ((u32)ptrToRtn) - sizeof(UsedBlockInfo), "Storage location for UsedBlockInfo is incorrect!");
			
			usedBlockInfo->size = requested_size_bytes + alignment;
			usedBlockInfo->alignmentOffset = alignmentOffset;
		}
		
		ASSERT(ptrToRtn, "No available memory to fulfil this request.");
		
		// For Debug
		// ASSERT(ptrToRtn >= mHeapStart && ptrToRtn < (void*)( ((u32)mHeapStart) + mHeapSize), "Pointer to return does not belong to this heap.");
		
		return ptrToRtn;
	}

	
	// Put an unused block back on the free list
	bool freeBlock(const void* ptr)
	{
		ASSERT(ptr, "Pointer to free is NULL!");
		ASSERT(ptr >= mHeapStart && ptr < (void*)(((u32)mHeapStart) + mHeapSize), "Pointer to free does not belong to this heap.");
		
		// Push the ptr back by sizeof(UsedBlockInfo) to get the UsedBlockInfo
		UsedBlockInfo* usedBlockInfo = (UsedBlockInfo*) (((u32)ptr) - sizeof(UsedBlockInfo));
		
		// Push the UsedBlockInfo ptr back by alignmentOffset to get the original memory start address, where we will store the FreeBlockInfo
		FreeBlockInfo* real_ptr = (FreeBlockInfo*) (void*)(((u32)usedBlockInfo) - usedBlockInfo->alignmentOffset);
		
		// Store the size to free as the new free block's size (plus the size stored to track the used amount)
		real_ptr->size = usedBlockInfo->size + sizeof(UsedBlockInfo);
		
		ASSERT((((u32)real_ptr) + real_ptr->size) <= (((u32)mHeapStart) + mHeapSize), "The block to free extends beyond the end of this heap.");
		
		ASSERT(real_ptr->size < mHeapSize, "Size to free is too large.");
		
		if (real_ptr && real_ptr >= mHeapStart && 
			(((u32)real_ptr) + real_ptr->size) <= (((u32)mHeapStart) + mHeapSize))
		{
			// Find nearest free blocks
			FreeBlockInfo* prev = NULL;
			FreeBlockInfo* next = NULL;
			
			// Block to free starts before free list
			if (mFreeListStart > real_ptr)
			{
				next = mFreeListStart;
				
				// This block will now be the start of our free list
				mFreeListStart = real_ptr;  // (we'll worry about where this points to next a little later)
			}
			// Block to free is after start of the free list
			else if (mFreeListStart < real_ptr)
			{
				// If free list is currently empty, then this newly freed block becomes our entire new free list
				if (mFreeListStart == NULL)
				{
					mFreeListStart = real_ptr;
					mFreeListStart->next_ptr = NULL;
				}
				else
				{			
					prev = mFreeListStart;
					
					while (prev->next_ptr && prev->next_ptr < real_ptr)
					{
						prev = prev->next_ptr;
					}
					
					next = prev->next_ptr;
				}
			}
			
			if (prev)
			{
				ASSERT(((u32)prev) + prev->size <= (u32)real_ptr, "The previous block overlaps the block to free.");
				
				// Previous block is adjacent
				if (((u32)prev) + prev->size == (u32)real_ptr)
				{
					// Merge the blocks
					prev->size += real_ptr->size;
					
					// If we merged the block to free with the previous block,
					// Then consider the previous block as the block to free
					// (For below when we are considering the next block)
					real_ptr = prev;
				}
				// Otherwise they are just neighbors in the list
				else
				{
					prev->next_ptr = real_ptr;
				}
			}
			if (next)
			{
				ASSERT(((u32)real_ptr) + real_ptr->size <= (u32)next, "The block to free overlaps the next block.");
				
				// Next block is adjacent
				if (((u32)real_ptr) + real_ptr->size == (u32)next)
				{
					// Merge the blocks
					real_ptr->size += next->size;
					
					// Point to the block after next now
					real_ptr->next_ptr = next->next_ptr;
				}
				// Otherwise they are just neighbors in the list
				else
				{
					real_ptr->next_ptr = next;
				}
			}
			else
			{
				// Next is null
				real_ptr->next_ptr = NULL;
			}
			
			return true;
		}
		
		return false;
	}
	
	// Print out contents of free list
	void printFreeList() const
	{
		FreeBlockInfo* currentBlock = mFreeListStart;
		
		u32 heapEnd = (((u32)mHeapStart) + mHeapSize);
		
		LOG("*** Heap Free List Contents:");
		LOG("Heap Start: %X: ", (u32)mHeapStart);
		LOG("Heap Size: %d: ", mHeapSize);
		LOG("Heap End: %X: ", heapEnd);
		
		int blockNum = 0;
		
		while (currentBlock != NULL)
		{
			u32 blockEnd = ((u32)currentBlock) + currentBlock->size;
			
			if (currentBlock < mHeapStart && blockEnd > heapEnd)
			{
				ASSERT(currentBlock >= mHeapStart && blockEnd <= heapEnd, "Current block does not belong to this heap.");
				return;
			}
			
			LOG("Block Number: %d", blockNum);
			LOG("Block Address: %X", (u32)currentBlock);
			LOG("Block Size: %d", currentBlock->size);
			LOG("Block End: %X", blockEnd);
			
			currentBlock = currentBlock->next_ptr;
			++blockNum;
		}
		
		LOG("*** End Heap Free List Contents\n");
	}
	
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
		u8 alignmentOffset;
	};
	
	// Find next sufficiently large memory block
	FreeBlockInfo* findNextSufficientlyLargeBlock(HeapAllocator::FreeBlockInfo* startBlock, u32 necessarySize, FreeBlockInfo*& prev_ptr)
	{
		if (&prev_ptr != NULL)
		{
			// For the first item in the list, there is no previous item
			prev_ptr = NULL;
		}
		
		while (startBlock != NULL) 
		{
			// Requested size + space to store information about the used block
			if (startBlock->size >= necessarySize)
			{
				return startBlock;
			}
			else 
			{
				prev_ptr = startBlock;
				startBlock = startBlock->next_ptr;
			}
		}
		
		return NULL;
	}
	
	void* mHeapStart;		// Starting memory address of the heap
	
	u32 mHeapSize;			// Size of the pool (in total)
	u32 mBaseAlignmentOffset;	// How many bytes we moved up the base address to achieve the requested alignment (necessary for freeing)
	
	FreeBlockInfo* mFreeListStart;	// Start of the free list
};

#endif