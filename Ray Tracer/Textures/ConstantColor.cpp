/*
 *  ConstantColor.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "ConstantColor.h"

ConstantColor::ConstantColor(void)
:	color(1.0) {}

ConstantColor::ConstantColor(const ConstantColor& texture)
: color (texture.color) {}

ConstantColor*									
ConstantColor::clone(void) const {
	return new ConstantColor(*this);
}

ConstantColor& 											
ConstantColor::operator= (const ConstantColor& rhs) {
	if (this == &rhs)
		return (*this);
	
	Texture::operator= (rhs);
	
	color = rhs.color;
	
	return (*this);
}

									

MyRGBColor																			
ConstantColor::get_color(const ShadeRec& sr) const {
	return color;
}