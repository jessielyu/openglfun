//
//  Memory.h
//  GameEngine
//
//  Created by NoEvilPeople on 6/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <new>  // To overload new and delete
#include <cstdlib>  // For malloc and free

void* operator new (size_t size) throw(std::bad_alloc);

void operator delete(void* p) throw();

void* operator new[](size_t s) throw(std::bad_alloc);

void operator delete[](void *dp) throw();