/*
 *  BTDF.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/25/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "BTDF.h"BTDF

BTDF::BTDF(void) //: sampler_ptr(NULL) 
{}

BTDF::BTDF(const BTDF& brdf) {
//	if (brdf.sampler_ptr) {
//		sampler_ptr = brdf.sampler_ptr->clone(); // should implement this
//	}
//	else {
//		sampler_ptr = NULL;
//	}
}

BTDF&
BTDF::operator= (const BTDF& rhs) {
	if (this == &rhs)
		return (*this);
	
//	if (sampler_ptr) {
//		delete sampler_ptr;
//		sampler_ptr = NULL;
//	}
//	
//	if (rhs.sampler_ptr) {
//		sampler_ptr = rhs.sampler_ptr->clone();	// should implement this
//	}
	
	return (*this);
}


BTDF::~BTDF(void) {
//	if (sampler_ptr) {
//		delete sampler_ptr;
//		sampler_ptr = NULL;
//	}
}

//void
//BTDF::set_sampler(Sampler* sPtr) {
//	sampler_ptr = sPtr;
//	sampler_ptr->map_samples_to_hemisphere(1);	// perfect diffuse
//}

// ------------------------------------------------------------------------ f

MyRGBColor
BTDF::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
	return (black);
}


// ------------------------------------------------------------------------ sample_f

MyRGBColor
BTDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const {
	return (black);
	
}


// ------------------------------------------------------------------------ sample_f

//RGBColor
//BTDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
//	return (black);
//}


// ------------------------------------------------------------------------ rho	

MyRGBColor
BTDF::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}