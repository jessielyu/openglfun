/*
 *  PlaneChecker.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 11/4/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "PlaneChecker.h"

PlaneChecker::PlaneChecker(void)
:	color1(0.0),
	color2(1.0),
	outline_color(0.5),
	size(1.0),
	outline_width(0.1) {}

PlaneChecker::PlaneChecker(const PlaneChecker& texture)
:	color1 (texture.color1), 
	color2 (texture.color2), 
	outline_color(texture.outline_color),
	size(texture.size),
	outline_width(texture.outline_width) {}

PlaneChecker*									
PlaneChecker::clone(void) const {
	return new PlaneChecker(*this);
}

PlaneChecker& 											
PlaneChecker::operator= (const PlaneChecker& rhs) {
	if (this == &rhs)
		return (*this);
	
	Texture::operator= (rhs);
	
	color1 = rhs.color1;
	color2 = rhs.color2;
	outline_color = rhs.outline_color;
	size = rhs.size;
	outline_width = rhs.outline_width;
	
	return (*this);
}



MyRGBColor																			
PlaneChecker::get_color(const ShadeRec& sr) const {
//	float x = sr.local_hit_point.x;
//	float z = sr.local_hit_point.z;
//	int ix = floor(x / size);
//	int iz = floor(z / size);
//	float fx = x / size - ix;
//	float fz = z / size - iz;
//	float width = 0.5 * outline_width / size;
//	bool in_outline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);
//	
//	
//	if ((ix + iz) % 2 == 0) {
//		if (!in_outline)
//			return (color1);
//	}
//	else {
//		if (!in_outline)
//			return (color2);
//	}
//	
//	return (outline_color);
	float x = sr.local_hit_point.x;
	float z = sr.local_hit_point.z;
	int ix = floor(x / size);
	int iz = floor(z / size);
	float fx = x / size - ix;
	float fz = z / size - iz;
	float width = 0.5 * outline_width / size; 
	bool in_outline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);
	
	if ((ix + iz) % 2 == 0) {
		if (!in_outline)	
			return (color1);
	}
	else {
		if (!in_outline)	
			return (color2);
	}
	
	return (outline_color);
}