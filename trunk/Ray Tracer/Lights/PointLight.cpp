/*
 *  PointLight.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "PointLight.h"

PointLight::PointLight(void)
:	Light(),
	ls(1.0),
	color(1.0),
	location(0)
{}

PointLight::PointLight(const PointLight& pl)
:	Light(pl),
	ls(pl.ls),
	color(pl.color),
	location(pl.location)
{}

PointLight&
PointLight::operator= (const PointLight& pl) {
	if (this == &pl)
		return (*this);

	Light::operator= (pl);
	
	ls = pl.ls;
	color = pl.color;
	location = pl.location;
	
	return (*this);
}

Light*
PointLight::clone(void) const {
	return (new PointLight(*this));
}

Vector3D
PointLight::get_direction(ShadeRec& sr) {
	return ((location - sr.hit_point).hat());
}

MyRGBColor
PointLight::L(ShadeRec& sr) {
	return (ls * color);
}