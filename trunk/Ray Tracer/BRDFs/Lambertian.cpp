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
	kd(0.0),
	cd(0.0)
{}

Lambertian::Lambertian(const Lambertian& lamb)
:	BRDF(lamb),
	kd(lamb.kd),
	cd(lamb.cd)
{
}

Lambertian&
Lambertian::operator= (const Lambertian& rhs) {
	if (this == &rhs)
		return (*this);
	
	BRDF::operator= (rhs);
	
	kd = rhs.kd;
	cd = rhs.cd;
	
	return (*this);
}

Lambertian::~Lambertian(void) {

}

BRDF*
Lambertian::clone(void) const {
	return (new Lambertian(*this));
}


MyRGBColor
Lambertian::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
	return (kd * cd * invPI);
}

MyRGBColor
Lambertian::sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo) const{
	return (black);
}

MyRGBColor
Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const{
	return (kd * cd);
}

MyRGBColor
Lambertian::sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo, float& pdf) const {
	Vector3D w = sr.normal;
	Vector3D v = Vector3D(0.0034, 1.0, 0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;
	
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();
	pdf = sr.normal * wi * invPI;
	
	return (kd * cd * invPI);
}