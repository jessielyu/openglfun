/*
 *  PerfectSpecular.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "PerfectSpecular.h"PerfectSpecular

PerfectSpecular::PerfectSpecular(void)
:	BRDF(),
kr(1.0),
cr(MyRGBColor(1.0,1.0,1.0))
{}

PerfectSpecular::PerfectSpecular(const PerfectSpecular& lamb)
:	BRDF(lamb),
kr(lamb.kr),
cr(lamb.cr)
{}

PerfectSpecular&
PerfectSpecular::operator= (const PerfectSpecular& rhs) {
	if (this == &rhs)
		return (*this);
	
	BRDF::operator= (rhs);
	
	kr = rhs.kr;
	cr = rhs.cr;
	
	return (*this);
}

PerfectSpecular::~PerfectSpecular(void) {}

BRDF*
PerfectSpecular::clone(void) const {
	return (new PerfectSpecular(*this));
}


MyRGBColor
PerfectSpecular::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
	//return (kr * cr * invPI);
	return BRDF::f(sr, wi, wo);
}

MyRGBColor
PerfectSpecular::sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo) const{
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo;
	
	return (kr * cr / fabs(sr.normal * wi));
}

// for global lighting
MyRGBColor
PerfectSpecular::sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo, float& pdf) const {
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo;
	pdf = sr.normal * wi;
	
	return (kr * cr);
}

MyRGBColor
PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& wo) const{
	//return (kr * cr);
	return BRDF::rho(sr, wo);
}