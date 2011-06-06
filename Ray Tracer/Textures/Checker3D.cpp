/*
 *  Checker3D.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 11/4/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Checker3D.h"

Checker3D::Checker3D(void)
:	color1(0.0),
	color2(1.0),
	size(1.0) {}

Checker3D::Checker3D(const Checker3D& texture)
:	color1 (texture.color1), 
	color2 (texture.color2), 
	size(1.0) {}

Checker3D*									
Checker3D::clone(void) const {
	return new Checker3D(*this);
}

Checker3D& 											
Checker3D::operator= (const Checker3D& rhs) {
	if (this == &rhs)
		return (*this);
	
	Texture::operator= (rhs);
	
	color1 = rhs.color1;
	color2 = rhs.color2;
	size = rhs.size;
	
	return (*this);
}



MyRGBColor																			
Checker3D::get_color(const ShadeRec& sr) const {
	float eps = -0.000187453738;
	float x = sr.local_hit_point.x + eps;
	float y = sr.local_hit_point.y + eps;
	float z = sr.local_hit_point.z + eps;
	
	if (((int) floor(x / size) + (int) floor(y / size) + (int) floor(z / size)) % 2 == 0)
		return (color1);
	else
		return (color2);
}