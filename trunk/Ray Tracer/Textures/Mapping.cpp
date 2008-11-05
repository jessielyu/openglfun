/*
 *  Mapping.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Mapping.h"

// ---------------------------------------------------------------- default constructor

Mapping::Mapping(void) {}


// ---------------------------------------------------------------- copy constructor

Mapping::Mapping(const Mapping& m) {}


// ---------------------------------------------------------------- assignment operator

Mapping& 
Mapping::operator= (const Mapping& rhs) {
	if (this == &rhs)
		return (*this);
	
	return (*this);
}


// ---------------------------------------------------------------- destructor

Mapping::~Mapping(void) {} 

