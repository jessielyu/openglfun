/*
 *  SphericalMap.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "SphericalMap.h"


SphericalMap::SphericalMap(void) {}



SphericalMap::SphericalMap(const SphericalMap& sm) {}



SphericalMap& 
SphericalMap::operator= (const SphericalMap& rhs) {
	if (this == &rhs)
		return (*this);
	
	return (*this);
}



SphericalMap::~SphericalMap (void) {} 



SphericalMap*								
SphericalMap::clone(void) const {
	return (new SphericalMap(*this));
}	

void
SphericalMap::get_texel_coordinates(const Point3D& local_hit_point, 
									const int xres, const int yres, int& row, int& column) const {
	// compute theata and phi
	float theta = acos(local_hit_point.y);
	float phi = atan2(local_hit_point.x, local_hit_point.z);
	
	if (phi < 0.0)
		phi += TWO_PI;
	
	// map theta and phi to u, v (range is 0 to 1)
	
	float u = phi * invTWO_PI;
	float v = 1.0 - theta * invPI;
	
	// map u and v to texel coordinates
	
	column = (int) ((xres - 1) * u);
	row = (int) ((yres - 1) * v);
}