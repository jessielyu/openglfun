/*
 *  SV_Lambertian.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "SV_Lambertian.h"

SV_Lambertian::SV_Lambertian(void)
:	BRDF(),
kd(0.0),
cd(NULL)
{}

SV_Lambertian::SV_Lambertian(const SV_Lambertian& lamb)
:	BRDF(lamb),
kd(lamb.kd),
cd(lamb.cd)
{
}

SV_Lambertian&
SV_Lambertian::operator= (const SV_Lambertian& rhs) {
	if (this == &rhs)
		return (*this);
	
	BRDF::operator= (rhs);
	
	kd = rhs.kd;
	
	if (cd) {
		delete cd;
		cd = NULL;
	}
	
	if (rhs.cd)
		cd = rhs.cd;
	
	return (*this);
}

SV_Lambertian::~SV_Lambertian(void) {
	if (cd) {
		delete cd;
		cd = NULL;
	}
}

BRDF*
SV_Lambertian::clone(void) const {
	return (new SV_Lambertian(*this));
}


MyRGBColor
SV_Lambertian::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
	return (kd * cd->get_color(sr) * invPI);
}

MyRGBColor
SV_Lambertian::sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo) const{
	return (black);
}

MyRGBColor
SV_Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const{
	return (kd * cd->get_color(sr));
}

MyRGBColor
SV_Lambertian::sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo, float& pdf) const {
	Vector3D w = sr.normal;
	Vector3D v = Vector3D(0.0034, 1.0, 0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;
	
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();
	pdf = sr.normal * wi * invPI;
	
	return (kd * cd->get_color(sr) * invPI);
}