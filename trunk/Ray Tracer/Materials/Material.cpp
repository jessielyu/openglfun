/*
 *  Material.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Material.h"
#include "Constants.h"

Material::Material(void) {}

Material::Material(const Material& m) {}

Material&
Material::operator= (const Material& m) {
	if (this == &m)
		return *this;
	
	return *this;
}

Material::~Material(void) {}
	

MyRGBColor
Material::shade(ShadeRec& sr) {
	return (black);
}
	
MyRGBColor
Material::area_light_shade(ShadeRec& sr){
	return (black);
}

MyRGBColor
Material::path_shade(ShadeRec& sr){
	return (black);
}

MyRGBColor
Material::global_shade(ShadeRec& sr){
	return (black);
}

MyRGBColor
Material::get_Le(ShadeRec& sr) const {
	return (black);
}