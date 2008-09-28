/*
 *  ConcaveSphere.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "ConcaveSphere.h"

ConcaveSphere::ConcaveSphere(void) 
:	Sphere()
{}

ConcaveSphere::ConcaveSphere(const ConcaveSphere& cs) 
:	Sphere(cs)
{}

ConcaveSphere&
ConcaveSphere::operator= (const ConcaveSphere& cs) {
	Sphere::operator= (cs);
}

Sphere* 									// Virtual copy constructor
ConcaveSphere::clone(void) const {
	return (new ConcaveSphere(*this));
}

bool 												 
ConcaveSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = -(temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = -(temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	}
	
	return (false);
	
}