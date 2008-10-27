/*
 *  FresnelReflector.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *FresnelReflector
 */

#include "FresnelReflector.h"

FresnelReflector::FresnelReflector(void)
:	BRDF(),
	eta_in(1.0),
	eta_out(1.0)
//kr(1.0),
//cr(MyRGBColor(1.0,1.0,1.0))
{}

FresnelReflector::FresnelReflector(const FresnelReflector& lamb)
:	BRDF(lamb),
	eta_in(lamb.eta_in),
	eta_out(lamb.eta_out)
//kr(lamb.kr),
//cr(lamb.cr)
{}

FresnelReflector&
FresnelReflector::operator= (const FresnelReflector& rhs) {
	if (this == &rhs)
		return (*this);
	
	BRDF::operator= (rhs);
	
	eta_in = rhs.eta_in;
	eta_out = rhs.eta_out;
//	kr = rhs.kr;
//	cr = rhs.cr;
	
	return (*this);
}

FresnelReflector::~FresnelReflector(void) {}

BRDF*
FresnelReflector::clone(void) const {
	return (new FresnelReflector(*this));
}


MyRGBColor
FresnelReflector::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
	//return (kr * cr * invPI);
	return BRDF::f(sr, wi, wo);
}

MyRGBColor
FresnelReflector::sample_f(const ShadeRec& sr,  Vector3D& wr, const Vector3D& wo) const{
	float ndotwo = sr.normal * wo;
	wr = -wo + 2.0 * sr.normal * ndotwo; 
	
	return (fresnel(sr) * white / fabs(sr.normal * wr));
}

// for global lighting
MyRGBColor
FresnelReflector::sample_f(const ShadeRec& sr,  Vector3D& wr, const Vector3D& wo, float& pdf) const {
	float ndotwo = sr.normal * wo;
	wr = -wo + 2.0 * sr.normal * ndotwo;
	//pdf = sr.normal * wr;
	pdf = fabs(sr.normal * wr);	// maybe this instead?
	
	// assuming this is correct based on the other sample_f
	return(fresnel(sr) * white);
	//return (kr * cr);
}

MyRGBColor
FresnelReflector::rho(const ShadeRec& sr, const Vector3D& wo) const{
	//return (kr * cr);
	return BRDF::rho(sr, wo);
}

float
FresnelReflector::fresnel(const ShadeRec& sr) const {
	Normal normal(sr.normal);
	float ndotd = -normal * sr.ray.d;
	float eta;
	
	if (ndotd < 0.0) { 
		normal = -normal;
		eta = eta_out / eta_in;
	}
	else
		eta = eta_in / eta_out;
	
	float cos_theta_i 		= -normal * sr.ray.d; 
	float temp 				= 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
	float cos_theta_t 		= sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
	float r_parallel 		= (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
	float r_perpendicular 	= (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);
	float kr 				= 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);
	
	
	return (kr);
}