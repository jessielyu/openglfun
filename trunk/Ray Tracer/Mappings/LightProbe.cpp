/*
 *  LightProbe.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/29/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "LightProbe.h"




LightProbe::LightProbe(void)
:	map_type(regular) {}



LightProbe::LightProbe(const LightProbe& sm) 
:	map_type(sm.map_type) {}



LightProbe& 
LightProbe::operator= (const LightProbe& rhs) {
	if (this == &rhs)
		return (*this);
	
	map_type == rhs.map_type;
	
	return (*this);
}



LightProbe::~LightProbe (void) {} 



LightProbe*								
LightProbe::clone(void) const {
	return (new LightProbe(*this));
}	

void
LightProbe::get_texel_coordinates(const Point3D& local_hit_point, 
									const int xres, const int yres, int& row, int& column) const {
	float alpha;
	
	// compute 
	float x = local_hit_point.x, y = local_hit_point.y, z = local_hit_point.z;
	
	if (map_type == panoramic)
		alpha = acos(-z);
	else if (map_type == regular)
		alpha = acos(z);
	
	float d = sqrt(x * x + y * y);	
	float sin_beta = y / d;
	float cos_beta = x / d;
	
	// map theta and phi to u, v (range is 0 to 1)
	
	float r = alpha * invPI;
	float u = (1.0 + r * cos_beta) * 0.5;
	float v = (1.0 + r * sin_beta) * 0.5;
	
	// map u and v to texel coordinates
	
	column = (int) ((xres - 1) * u);
	row = (int) ((yres - 1) * v);
}