/*
 *  GlossyReflector.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/23/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GlossyReflector.h"
#include "World.h"

// ---------------------------------------------------------------- default constructor

GlossyReflector::GlossyReflector (void)
:	Phong(),
glossy_specular_brdf(new GlossySpecular)
{}


// ---------------------------------------------------------------- copy constructor

GlossyReflector::GlossyReflector(const GlossyReflector& rm)
: 	Phong(rm) {
	
	if(rm.glossy_specular_brdf)
		glossy_specular_brdf = (GlossySpecular*)rm.glossy_specular_brdf->clone(); 
	else  
		glossy_specular_brdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

GlossyReflector& 
GlossyReflector::operator= (const GlossyReflector& rhs) {
	if (this == &rhs)
		return (*this);
	
	Phong::operator=(rhs);
	
	if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}
	
	if (rhs.glossy_specular_brdf)
		glossy_specular_brdf = (GlossySpecular*) rhs.glossy_specular_brdf->clone();
	
	return (*this);
}


// ---------------------------------------------------------------- clone

GlossyReflector*										
GlossyReflector::clone(void) const {
	return (new GlossyReflector(*this));
}	


// ---------------------------------------------------------------- destructor

GlossyReflector::~GlossyReflector(void) {
	if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}
}

MyRGBColor
GlossyReflector::area_light_shade(ShadeRec& sr) {
	MyRGBColor L(Phong::area_light_shade(sr));	// direct illumination
	
	Vector3D wo(-sr.ray.d);
	Vector3D wi;
	float pdf;
	MyRGBColor fr(glossy_specular_brdf->sample_f(sr, wi, wo, pdf));
	Ray reflected_ray(sr.hit_point, wi);
	
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
	
	return (L);
}

MyRGBColor
GlossyReflector::shade(ShadeRec& sr) {
	return Phong::shade(sr);
}