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

GameManager::GameManager(void)
{	
	int totalSize = 16;
//	int individualSize = 8;//sizeof(int);
	
	StackAllocator* stack = new StackAllocator(totalSize);
	
	PoolAllocator* pool = new PoolAllocator(32, 8);
	
	char* test1 = (char*) pool->useBlock();
	//char* test1 = (char*) stack->alloc(individualSize);
//	int* test1 = (int*) stack->alloc(individualSize);

//	*test1 = 1000;
	
	test1[0] = '1';
	test1[1] = '2';
	test1[2] = '3';
	test1[3] = '4';
	test1[4] = '5';
	test1[5] = '6';
	test1[6] = '7';
	test1[7] = 0;
	
	printf("%s\n", test1);
	//printf("%d\n", *test1);
	
	char* test2 = (char*) pool->useBlock();
	//char* test2 = (char*) stack->alloc(individualSize);
	//int* test2 = (int*) stack->alloc(individualSize);
	
	//*test2 = 2000;
	
	test2[0] = 'a';
	test2[1] = 'b';
	test2[2] = 'c';
	test2[3] = 'd';
	test2[4] = 'e';
	test2[5] = 'f';
	test2[6] = 'g';
	test2[7] = 0;
	
	printf("%s\n", test1);
	printf("%s\n", test2);
	
//	printf("%d\n", *test1);
//	printf("%d\n", *test2);
	
	pool->freeBlock(test2);
	//stack->freeToMarker((StackAllocator::Marker)test2);
	test2 = NULL;
	
	char* test3 = (char*) pool->useBlock();
	//char* test3 = (char*) stack->alloc(individualSize);
	//int* test3 = (int*) stack->alloc(individualSize);
	
//	*test3 = 3000;
	
	
	
//	printf("%d\n", *test1);
//	printf("%d\n", *test3);
	
	test3[0] = 'z';
	test3[1] = 'y';
	test3[2] = 'x';
	test3[3] = 'w';
	test3[4] = 'v';
	test3[5] = 'u';
	test3[6] = 't';
	test3[7] = 0;
	
	printf("%s\n", test1);
	printf("%s\n", test3);
	
	stack->clear();
	
	pool->freeBlock(test1);
	pool->freeBlock(test3);
	
	delete stack;
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