/*
 *  Emissive.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Emissive.h"
#include "Constants.h"

Emissive::Emissive(void)
:	Material(),
	ls(1.0),
	ce(white)
{}

Emissive::Emissive(const Emissive& em) 
:	Material(em),
	ls(em.ls),
	ce(em.ce)
{}
	

Emissive&
Emissive::operator=(const Emissive& em) {
	if (this == &em)
		return (*this);
	
	ls = em.ls;
	ce = em.ce;
	
	return (*this);
}

Material*
Emissive::clone(void) const {
	return (new Emissive(*this));
}

Emissive::~Emissive(void) {}

MyRGBColor
Emissive::get_Le(ShadeRec& sr) const {
	return (ls*ce);
}

MyRGBColor
Emissive::shade(ShadeRec& sr) {
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls* ce);
	else
		return (black);
}

MyRGBColor
Emissive::area_light_shade(ShadeRec& sr) {
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls* ce);
	else
		return (black);
}