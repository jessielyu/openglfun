//
//  SmartPointer.h
//  GameEngine
//
//  Created by Joseph Conley on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_SmartPointer_h
#define GameEngine_SmartPointer_h

#include <vector>

#include "Assert.h"
#include "Log.h"
#include "Memory.h"
#include "PoolAllocator.h"
#include "singleton.h"

// Pointers that can reference count and be reassigned
template <class T>
class SmartPointer 
{
public:
	explicit SmartPointer(T* p = 0, bool releaseMemory = false, bool useFree = true, SmartPointer<T>* next = 0, SmartPointer<T>* prev = 0) 
	:	mRawPointer(p),
		mPrevOwner(prev),
		mNextOwner(next),
		mReleaseMemory(releaseMemory),
		mUseFree(useFree)
	{
		ASSERT(next != this, "Circular reference!");
		ASSERT(prev != this, "Circular reference!");
	}
	
	~SmartPointer()
	{
		if (mReleaseMemory && mRawPointer &&	// Is the pointer non null?
			!(mNextOwner || mPrevOwner))		// Are we the last owner?
		{
			if (mUseFree)
			{
				free(mRawPointer);
			}
			else
			{
				ASSERT(false, "not implemented.");
				// TODO: fix "Delete void* is undefined warning"
				//delete mRawPointer;
			}
		}
		// Remove yourself from the old lists
		if (mNextOwner)
		{
			mNextOwner->mPrevOwner = mPrevOwner;
		}
		if (mPrevOwner)
		{
			mPrevOwner->mNextOwner = mNextOwner;
		}
	}
	
	// Reset the pointer to another raw address
	void reset(T* p = 0, bool resetJointOwners = true)
	{
		if (mReleaseMemory && mRawPointer &&	// Is the pointer non null?
			mRawPointer != p &&					// Is it not the same pointer we're being passed?
			!(mNextOwner || mPrevOwner))		// Are we the last owner?
		{
			if (mUseFree)
			{
				free(mRawPointer);
			}
			else
			{
				ASSERT(false, "not implemented.");
				// TODO: fix "Delete void* is undefined warning"
				//delete mRawPointer;
			}
		}
		
		// Reset other co-owners of this raw pointer
		if (resetJointOwners)
		{
			SmartPointer<void>* cur = this;
			
			// Reset all other owners of the same pointer (and watch out for circular references)
			while ((cur = cur->mNextOwner) && cur != this) 
			{
				cur->reset(p, false);
			}
			
			cur = this;
			
			while ((cur = cur->mPrevOwner) && cur != this) 
			{
				cur->reset(p, false);
			}
		}
		
		// Finally reset the raw pointer
		mRawPointer = p;
	}
	
	// Reset to a new smart pointer, specifying joint owners
	void reset(T* p, SmartPointer<T>* next, SmartPointer<T>* prev) 
	{
		ASSERT(next != this, "Circular reference!");
		ASSERT(prev != this, "Circular reference!");
		
		if (mReleaseMemory && mRawPointer &&	// Is the pointer non null?
			mRawPointer != p &&					// Is it not the same pointer we're being passed
			!(mNextOwner || mPrevOwner))		// Are we the last owner
		{
			if (mUseFree)
			{
				free(mRawPointer);
			}
			else
			{
				ASSERT(false, "not implemented.");
				// TODO: fix "Delete void* is undefined warning"
				//delete mRawPointer;
			}
		}
		
		// If next owner changed
		if (mNextOwner != next)
		{
			// Remove yourself from the old list
			if (mNextOwner)
			{
				mNextOwner->mPrevOwner = mPrevOwner;
			}
			// Add yourself to the new list
			if (next)
			{
				next->mPrevOwner = this;
			}
			
			mNextOwner = next;
		}
		
		if(mPrevOwner != prev)
		{
			if (mPrevOwner)
			{
				mPrevOwner->mNextOwner = mNextOwner;
			}
			if (prev)
			{
				prev->mNextOwner = this;
			}
			mPrevOwner = prev;
		}		
		
		mRawPointer = p;
	}
	
	void setUseFree(bool useFree = false) {mUseFree = useFree;}

	// TODO: Cannot form a reference to void
	//T& operator*() const {return *mRawPointer;}
	T operator->() const {return mRawPointer;}
	
	T* get() const {return mRawPointer;}
	
	// TODO: Implement
	void swap(SmartPointer & b);
	
	// TODO: Copy constructors

private:

	T* mRawPointer;					// Actual raw pointer
	
	SmartPointer<T>* mPrevOwner;	// Next joint owner
	SmartPointer<T>* mNextOwner;	// Previous joint owner
	
	bool mReleaseMemory;			// Whether or not to release memory if all references are gone
	bool mUseFree;					// Whether to use free or delete to release memory
};

// Handle allocations of Smart Pointers
class SmartPointerAllocator : public Singleton<SmartPointerAllocator>
{
public:
	SmartPointerAllocator();
	
	~SmartPointerAllocator();
	
	void startUp(); 
	
	void shutDown();
		
	SmartPointer<void>* allocateSmartPointer();
	
	bool freeSmartPointer(SmartPointer<void>* pointer);
	
	void printSmartPointerVector();
	
	SmartPointer<void>* getLowestAddressPointerBetween(u32 lowAddress, u32 highAddress);
	
private:
	PoolAllocator* pool;
	std::vector<SmartPointer<void>*> smartPointerTrackingVector;
};

#endif
