/*
 *  RectangularMap.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "RectangularMap.h"


RectangularMap::RectangularMap(void) {}



RectangularMap::RectangularMap(const RectangularMap& sm) {}



RectangularMap& 
RectangularMap::operator= (const RectangularMap& rhs) {
	if (this == &rhs)
		return (*this);
	
	return (*this);
}



RectangularMap::~RectangularMap (void) {} 



RectangularMap*								
RectangularMap::clone(void) const {
	return (new RectangularMap(*this));
}	

void
RectangularMap::get_texel_coordinates(const Point3D& local_hit_point, 
									const int xres, const int yres, int& row, int& column) const {
	
	float u = (local_hit_point.z + 1) / 2;
	float v = (local_hit_point.x + 1) / 2;
	
	column = (int) ((xres - 1) * u);
	row = (int) ((yres - 1) * v);
}