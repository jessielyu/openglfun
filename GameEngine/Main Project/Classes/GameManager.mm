//
//  GameManager.cpp
//  SimpleSample
//
//  Created by NoEvilPeople on 5/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GameManager.h"

#import <UIKit/UIKit.h>

#include <stdio.h>

#include "ConstantsAndMacros.h"
#include "OpenGLCommon.h"
#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "HeapAllocator.h"
#include "test_class.h"
#include "Assert.h"
#include "Log.h"
#include "DefragmentableHeapAllocator.h"
#include "SmartPointer.h"
#include "RamMemorySource.h"

GameManager::GameManager(void)
{	
	int stack_totalSize = 16;
	int stack_individualSize = sizeof(int);
	
	RamMemorySource ramSource;
	
	StackAllocator<RamMemorySource>* stack = new StackAllocator<RamMemorySource>(stack_totalSize, &ramSource);
	
	//char* test1 = (char*) stack->alloc(stack_individualSize);
	int* stack_test1 = (int*) stack->alloc(stack_individualSize);
	
	*stack_test1 = 1000;
	
//	stack_test1[0] = '1';
//	stack_test1[1] = '2';
//	stack_test1[2] = '3';
//	stack_test1[3] = '4';
//	stack_test1[4] = '5';
//	stack_test1[5] = '6';
//	stack_test1[6] = '7';
//	stack_test1[7] = 0;
	
	printf("%d\n", *stack_test1);	
	
	//char* test2 = (char*) stack->alloc(stack_individualSize);
	int* stack_test2 = (int*) stack->alloc(stack_individualSize);
	
	*stack_test2 = 2000;
	
//	stack_test2[0] = 'a';
//	stack_test2[1] = 'b';
//	stack_test2[2] = 'c';
//	stack_test2[3] = 'd';
//	stack_test2[4] = 'e';
//	stack_test2[5] = 'f';
//	stack_test2[6] = 'g';
//	stack_test2[7] = 0;
	
	printf("%d\n", *stack_test1);
	printf("%d\n", *stack_test2);
	
	//char* test3 = (char*) stack->alloc(stack_individualSize);
	int* stack_test3 = (int*) stack->alloc(stack_individualSize);
	
	*stack_test3 = 3000;
	
//	stack_test3[0] = 'z';
//	stack_test3[1] = 'y';
//	stack_test3[2] = 'x';
//	stack_test3[3] = 'w';
//	stack_test3[4] = 'v';
//	stack_test3[5] = 'u';
//	stack_test3[6] = 't';
//	stack_test3[7] = 0;
	
	printf("%d\n", *stack_test1);
	printf("%d\n", *stack_test3);

	stack->freeToMarker((StackAllocator<RamMemorySource>::Marker)stack_test2);
	
	printf("%d\n", *stack_test1);
	
	stack->clear();
	delete stack;
	
	// POOL ALLOCATOR TEST
	
	int pool_totalSize = 32;
	int pool_individualSize = 8;//sizeof(int);
	int pool_alignmentSize = 64;
	
	PoolAllocator* pool = new PoolAllocator(pool_totalSize, pool_individualSize, pool_alignmentSize);
	
	char* pool_test1 = (char*) pool->useBlock();

	
	pool_test1[0] = '1';
	pool_test1[1] = '2';
	pool_test1[2] = '3';
	pool_test1[3] = '4';
	pool_test1[4] = '5';
	pool_test1[5] = '6';
	pool_test1[6] = '7';
	pool_test1[7] = 0;
	
	printf("%s\n", pool_test1);

	
	char* pool_test2 = (char*) pool->useBlock();

	
	pool_test2[0] = 'a';
	pool_test2[1] = 'b';
	pool_test2[2] = 'c';
	pool_test2[3] = 'd';
	pool_test2[4] = 'e';
	pool_test2[5] = 'f';
	pool_test2[6] = 'g';
	pool_test2[7] = 0;
	
	printf("%s\n", pool_test1);
	printf("%s\n", pool_test2);
	
	
	pool->freeBlock(pool_test2);

	pool_test2 = NULL;
	
	char* pool_test3 = (char*) pool->useBlock();
	
	pool_test3[0] = 'z';
	pool_test3[1] = 'y';
	pool_test3[2] = 'x';
	pool_test3[3] = 'w';
	pool_test3[4] = 'v';
	pool_test3[5] = 'u';
	pool_test3[6] = 't';
	pool_test3[7] = 0;
	
	printf("%s\n", pool_test1);
	printf("%s\n", pool_test3);
	
	pool->freeBlock(pool_test1);
	pool->freeBlock(pool_test3);
	
	
	delete pool;
	
	HeapAllocator* heap = new HeapAllocator(32 + 16);
	
	LOG("Empty Heap");
	heap->printFreeList();
	
	u32* heapTest1 = (u32*)heap->useBlock(8);
	
	LOG("1 block allocated");
	heap->printFreeList();
	
	u32* heapTest2 = (u32*)heap->useBlock(8);
	
	LOG("2 blocks allocated");
	heap->printFreeList();
	
	u32* heapTest3 = (u32*)heap->useBlock(8);
	
	LOG("3 blocks allocated");
	heap->printFreeList();
	
	u32* heapTest4 = (u32*)heap->useBlock(8);
	ASSERT(heapTest4, "heapTest4 is NULL");
	
	LOG("4 blocks allocated");
	heap->printFreeList();
	
	heap->freeBlock(heapTest1);
	heapTest1 = NULL;
	
	LOG("Block 1 Unallocated");
	heap->printFreeList();
	
	heap->freeBlock(heapTest3);
	heapTest3 = NULL;
	
	LOG("Block 3 Unallocated");
	heap->printFreeList();
	
	heap->freeBlock(heapTest2);
	heapTest2 = NULL;
	
	LOG("Block 2 Unallocated");
	heap->printFreeList();
	
	LOG("Block 4 Unallocated");
	heap->freeBlock(heapTest4);
	heapTest4 = NULL;
	
	heap->printFreeList();
	
	delete heap;
	
	DefragmentableHeapAllocator* defragHeap = new DefragmentableHeapAllocator(32 + 16);
	
	SmartPointerAllocator::Instance().startUp();
	
	LOG("Empty Heap");
	heap->printFreeList();
	
	
	SmartPointer<char>* defragTestArray[4];
	
	defragTestArray[0] = (SmartPointer<char>*) defragHeap->useBlock(8);
	
	LOG("1 block allocated");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	
	defragTestArray[1] = (SmartPointer<char>*) defragHeap->useBlock(8);
	
	LOG("2 blocks allocated");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	
	defragTestArray[2] = (SmartPointer<char>*) defragHeap->useBlock(8);
	
	LOG("3 blocks allocated");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	
	defragTestArray[3] = (SmartPointer<char>*) defragHeap->useBlock(8);
	ASSERT(defragTestArray[3], "heapTest4 is NULL");
	
	LOG("4 blocks allocated");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	LOG("*** Smart Pointer Raw Contents:");
	for (int i = 1; i < 5; ++i)
	{
		std::sprintf(defragTestArray[i-1]->get(), "Test 0%d", i);
		LOG("Raw value of smart pointer %d: %s", i, defragTestArray[i-1] ? defragTestArray[i-1]->get() : "NULL");
	}
	LOG("*** End Smart Pointer Raw Contents\n");
	
	defragHeap->freeBlock((SmartPointer<void>*)defragTestArray[0]);
	defragTestArray[0] = NULL;
	
	LOG("Block 1 Unallocated");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	LOG("*** Smart Pointer Raw Contents:");
	for (int i = 0; i < 4; ++i)
	{
		LOG("Raw value of smart pointer %d: %s", i, defragTestArray[i] ? defragTestArray[i]->get() : "NULL");
	}
	LOG("*** End Smart Pointer Raw Contents\n");
	
	// Returns false when defragmentation done
	while (defragHeap->defragmentOneBlock()) {	}
	LOG("Heap defragmented.");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	LOG("*** Smart Pointer Raw Contents:");
	for (int i = 0; i < 4; ++i)
	{
		LOG("Raw value of smart pointer %d: %s", i, defragTestArray[i] ? defragTestArray[i]->get() : "NULL");
	}
	LOG("*** End Smart Pointer Raw Contents\n");
	
	defragHeap->freeBlock((SmartPointer<void>*)defragTestArray[2]);
	defragTestArray[2] = NULL;
	
	LOG("Block 3 Unallocated");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	LOG("*** Smart Pointer Raw Contents:");
	for (int i = 0; i < 4; ++i)
	{
		LOG("Raw value of smart pointer %d: %s", i, defragTestArray[i] ? defragTestArray[i]->get() : "NULL");
	}
	LOG("*** End Smart Pointer Raw Contents\n");
	
	defragHeap->defragmentOneBlock();
	LOG("Defragmented 1 Block");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	LOG("*** Smart Pointer Raw Contents:");
	for (int i = 0; i < 4; ++i)
	{
		LOG("Raw value of smart pointer %d: %s", i, defragTestArray[i] ? defragTestArray[i]->get() : "NULL");
	}
	LOG("*** End Smart Pointer Raw Contents\n");
	
	defragHeap->freeBlock((SmartPointer<void>*)defragTestArray[1]);
	defragTestArray[1] = NULL;
	
	LOG("Block 2 Unallocated");
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	LOG("*** Smart Pointer Raw Contents:");
	for (int i = 0; i < 4; ++i)
	{
		LOG("Raw value of smart pointer %d: %s", i, defragTestArray[i] ? defragTestArray[i]->get() : "NULL");
	}
	LOG("*** End Smart Pointer Raw Contents\n");
	
	LOG("Block 4 Unallocated");
	defragHeap->freeBlock((SmartPointer<void>*)defragTestArray[3]);
	defragTestArray[3] = NULL;
	
	defragHeap->printFreeList();
	SmartPointerAllocator::Instance().printSmartPointerVector();
	LOG("*** Smart Pointer Raw Contents:");
	for (int i = 0; i < 4; ++i)
	{
		LOG("Raw value of smart pointer %d: %s", i, defragTestArray[i] ? defragTestArray[i]->get() : "NULL");
	}
	LOG("*** End Smart Pointer Raw Contents\n");
	
	delete defragHeap;
	
	SmartPointerAllocator::Instance().shutDown();
}

/////////////////////////////////////
/////////////////////////////////////

void GameManager::Init(EAGLContext* pContext, GLuint renderBuffer, GLuint frameBuffer, GLuint depthBuffer, CGRect bounds)
{
    TestClass::Instance().Init(pContext, renderBuffer, frameBuffer, depthBuffer, bounds);
}

/////////////////////////////////////
/////////////////////////////////////

void GameManager::Destroy(void)
{
	///--- clean up something before exiting
    TestClass::Instance().Cleanup();
}

/////////////////////////////////////
/////////////////////////////////////

void GameManager::Update(void)
{
    TestClass::Instance().Update();
}