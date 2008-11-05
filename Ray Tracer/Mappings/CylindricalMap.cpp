/*
 *  CylindricalMap.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "CylindricalMap.h"Cylindrical


CylindricalMap::CylindricalMap(void) {}



CylindricalMap::CylindricalMap(const CylindricalMap& sm) {}



CylindricalMap& 
CylindricalMap::operator= (const CylindricalMap& rhs) {
	if (this == &rhs)
		return (*this);
	
	return (*this);
}



CylindricalMap::~CylindricalMap (void) {} 



CylindricalMap*								
CylindricalMap::clone(void) const {
	return (new CylindricalMap(*this));
}	

void
CylindricalMap::get_texel_coordinates(const Point3D& local_hit_point, 
									const int xres, const int yres, int& row, int& column) const {
	// compute phi
	float phi = atan2(local_hit_point.x, local_hit_point.z);
	
	if (phi < 0.0)
		phi += TWO_PI;
	
	// map phi to u, , y to v (range is 0 to 1)
	
	float u = phi * invTWO_PI;
	float v = (local_hit_point.y + 1) / 2;
	
	// map u and v to texel coordinates
	
	column = (int) ((xres - 1) * u);
	row = (int) ((yres - 1) * v);
}