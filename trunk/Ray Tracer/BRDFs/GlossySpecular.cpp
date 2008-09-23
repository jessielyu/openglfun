/*
 *  GlossySpecular.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GlossySpecular.h"

GlossySpecular::GlossySpecular(void)
:	BRDF(),
ks(1.0),
cs(MyRGBColor(0,0,0)),
exp(1.0)
{}

GlossySpecular::GlossySpecular(const GlossySpecular& lamb)
:	BRDF(lamb),
ks(lamb.ks),
cs(lamb.cs),
exp(1.0)
{}

GlossySpecular&
GlossySpecular::operator= (const GlossySpecular& rhs) {
	if (this == &rhs)
		return (*this);
	
	BRDF::operator= (rhs);
	
	ks = rhs.ks;
	cs = rhs.cs;
	exp = rhs.exp;
	
	return (*this);
}

GlossySpecular::~GlossySpecular(void) {}

BRDF*
GlossySpecular::clone(void) const {
	return (new GlossySpecular(*this));
}


MyRGBColor
GlossySpecular::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
	MyRGBColor L;
	float ndotwi = sr.normal * wi;
	Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
	float rdotwo = r * wo;
	
	if (rdotwo > 0.0)
		L = ks * pow(rdotwo, exp);
	
	return (L);
}

MyRGBColor
GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& wi, Vector3D& wo) const{
	return (black);
}

MyRGBColor
GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const{
	return (black);
}