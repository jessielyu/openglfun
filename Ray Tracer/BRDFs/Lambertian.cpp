/*
 *  Lambertian.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Lambertian.h"

Lambertian::Lambertian(void)
:	BRDF(),
	kd(1.0),
	cd(MyRGBColor(0,0,0))
{}

Lambertian::Lambertian(const Lambertian& lamb)
:	BRDF(lamb),
	kd(lamb.kd),
	cd(lamb.cd)
{}

Lambertian&
Lambertian::operator= (const Lambertian& rhs) {
	if (this == &rhs)
		return (*this);
	
	BRDF::operator= (rhs);
	
	kd = rhs.kd;
	cd = rhs.cd;
	
	return (*this);
}

Lambertian::~Lambertian(void) {}

BRDF*
Lambertian::clone(void) const {
	return (new Lambertian(*this));
}


MyRGBColor
Lambertian::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
	return (kd * cd * invPI);
}

MyRGBColor
Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wi, Vector3D& wo) const{
	return (black);
}

MyRGBColor
Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const{
	return (kd * cd);
}