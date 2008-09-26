/*
 *  Directional.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Directional.h"
#include "World.h"

Directional::Directional(void)
:	Light(),
	ls(1.0),
	color(1.0),
	direction(0,1,0)
{}

Directional::Directional(const Directional& pl)
:	Light(pl),
	ls(pl.ls),
	color(pl.color),
	direction(pl.direction)
{}

Directional&
Directional::operator= (const Directional& pl) {
	if (this == &pl)
		return (*this);
	
	Light::operator= (pl);
	
	ls = pl.ls;
	color = pl.color;
	direction = pl.direction;
	
	return (*this);
}

Light*
Directional::clone(void) const {
	return (new Directional(*this));
}

Vector3D
Directional::get_direction(ShadeRec& sr) {
	return (direction);
}

MyRGBColor
Directional::L(ShadeRec& sr) {
	return (ls * color);
}

// Modified from point light, infinite distance away
bool
Directional::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int num_objects = sr.w.objects.size();
	//float d = location.distance(ray.o);
	
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t))// && t < d)
			return (true);
	
	return (false);
}