/*
 *  Texture.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Texture.h"

// ---------------------------------------------------------------- default constructor

Texture::Texture(void) {}


// ---------------------------------------------------------------- copy constructor

Texture::Texture(const Texture& texture) {}


// ---------------------------------------------------------------- assignment operator

Texture& 
Texture::operator= (const Texture& rhs) {
	if (this == &rhs)
		return (*this);
	
	return (*this);
}


// ---------------------------------------------------------------- destructor

Texture::~Texture(void) {}



