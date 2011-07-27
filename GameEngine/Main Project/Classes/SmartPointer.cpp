//
//  SmartPointer.cpp
//  GameEngine
//
//  Created by Joseph Conley on 7/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SmartPointer.h"

#define SMART_POINTER_MAX_NUM 100	// Maximum amount of space to reserve for smart pointers

SmartPointerAllocator::SmartPointerAllocator()
: pool(NULL) 
{
	
}

SmartPointerAllocator::~SmartPointerAllocator()
{
	if (pool)
	{
		shutDown();
	}
}

// Set up the global pool and tracking vector for smart pointers
void SmartPointerAllocator::startUp() 
{
	ASSERT(!pool, "Pool allocator has already been started!");
	
	if (!pool)
	{
		// Void type should cover our bases since smart pointers only store pointers to their type, and pointers are the same size
		pool = new PoolAllocator(SMART_POINTER_MAX_NUM*sizeof(SmartPointer<void>), sizeof(SmartPointer<void>)); 
		
		// Allocate space to globally track smart pointers (to enable things like defragmenting in-use memory)
		smartPointerTrackingVector.reserve(SMART_POINTER_MAX_NUM);
	}
}

// Release the global pool 
void SmartPointerAllocator::shutDown() 
{
	ASSERT(pool, "Pool allocator already freed!");
	
	if (pool)
	{
		delete pool;	// Pool will ASSERT if not all pointers freed
	}
}

// Allocate a smart pointer from our pool and track it in the global vector
SmartPointer<void>* SmartPointerAllocator::allocateSmartPointer()
{
	SmartPointer<void>* ptr = (SmartPointer<void>*) pool->useBlock();
	
	// Have to use free with void* (but we won't let the smart pointer manage memory anyway here)
	ptr->setUseFree(true);
	
	smartPointerTrackingVector.push_back(ptr);
	
	return ptr;
}

// Deallocate a smart pointer and remove it from the global tracking vector
bool SmartPointerAllocator::freeSmartPointer(SmartPointer<void>* pointer)
{
	std::vector<SmartPointer<void>*>::iterator it;
	
	bool itemFound = false;
	
	for (it = smartPointerTrackingVector.begin(); it != smartPointerTrackingVector.end(); it++)
	{
		SmartPointer<void>* item = *it;
		
		if (item && item == pointer)
		{
			smartPointerTrackingVector.erase(it);
			
			itemFound = true;
			
			break;
		}
	}
	
	ASSERT(itemFound, "Item not found in global smart pointer list!");
	
	return pool->freeBlock((void*)pointer) & itemFound;
}

// Print the contents of our global smart pointer tracking vector
void SmartPointerAllocator::printSmartPointerVector()
{
	LOG("*** Smart Pointer Global List Contents:");
	
	std::vector<SmartPointer<void>*>::iterator it;
	
	u32 pointerNum = 0;
	
	for (it = smartPointerTrackingVector.begin(); it != smartPointerTrackingVector.end(); it++)
	{
		SmartPointer<void>* item = *it;
		
		LOG("Pointer Number: %d", pointerNum);
		LOG("Real Pointer Address: %X", (u32) item->get());
		
		++pointerNum;
	}
	
	LOG("*** End Heap Free List Contents\n");
}


// Find the smart pointer with the lowest address between two given pointers (useful for defragmenting)
SmartPointer<void>* SmartPointerAllocator::getLowestAddressPointerBetween(u32 lowAddress, u32 highAddress)
{
	std::vector<SmartPointer<void>*>::iterator it;
	
	SmartPointer<void>* lowestPointerInRegion = NULL;
	
	for (it = smartPointerTrackingVector.begin(); it != smartPointerTrackingVector.end(); it++)
	{
		SmartPointer<void>* item = *it;
		
		u32 pointerAddress = (u32)item->get();
		
		if ((u32)pointerAddress > lowAddress && (u32)pointerAddress < highAddress)
		{
			if (!lowestPointerInRegion || 
				(pointerAddress < (const u32)lowestPointerInRegion->get()))
			{
				lowestPointerInRegion = item;
			}
		}
	}
	
	return lowestPointerInRegion;
}

