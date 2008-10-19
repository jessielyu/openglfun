/*
 *  PartAnnulus.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "PartAnnulus.h"

PartAnnulus::PartAnnulus(void) 
:	GeometricObject(),
center(1,1,1),
r_max_squared(9),
r_min_squared(1),
r_min(1),
r_max(3),
phi_min(0.0),
phi_max(TWO_PI),
normal(0,1,0)
{}

PartAnnulus::PartAnnulus(const Point3D c, const Normal n, 
							const float radius_min, const float radius_max, 
							const float p_min, const float p_max)
:	GeometricObject(),
center(c),
r_max_squared(pow(radius_max,2)),
r_min_squared(pow(radius_min,2)),
r_max(radius_max),
r_min(radius_min),
phi_min(p_min*PI_ON_180),
phi_max(p_max*PI_ON_180),
normal(n)
{}

PartAnnulus::PartAnnulus(const PartAnnulus& d)
:	GeometricObject(d),
center(d.center),
r_max_squared(d.r_max_squared),
r_min_squared(d.r_min_squared),
r_min(d.r_min),
r_max(d.r_max),
phi_max(d.phi_max),
phi_min(d.phi_min),
normal(d.normal)
{}

PartAnnulus&
PartAnnulus::operator=(const PartAnnulus& d) {
	if (this == &d)
		return (*this);
	
	GeometricObject::operator= (d);
	
	center = d.center;
	r_max_squared = d.r_max_squared;
	r_min_squared = d.r_min_squared;
	normal = d.normal;
	r_min = d.r_min;
	r_max = d.r_max;
	phi_max = d.phi_max;
	phi_min = d.phi_min;
	
	return (*this);
}

PartAnnulus*
PartAnnulus::clone(void) const {
	return (new PartAnnulus(*this));
}

bool
PartAnnulus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	float t = (center - ray.o) * normal / (ray.d * normal);
	
	if (t <= kEpsilon)
		return (false);
	
	Point3D p = ray.o + t * ray.d;
	
	float d_squared = center.d_squared(p);
	
	if (d_squared < r_max_squared && d_squared > r_min_squared) {
		Vector3D hit = ray.o + t * ray.d - center;
		
		double phi = atan2(hit.x, hit.z);
		if (phi < 0.0)
			phi += TWO_PI;
		
		if (phi >= phi_min && phi <= phi_max) {
				tmin = t;
				sr.normal = normal;
				sr.local_hit_point = p;
				return (true);
		}
		else 
			return (false);
	}
	else
		return (false);
}	

bool
PartAnnulus::shadow_hit(const Ray& ray, float& tmin) const {
	float t = (center - ray.o) * normal / (ray.d * normal);
	
	if (t <= kEpsilon)
		return (false);
	
	Point3D p = ray.o + t * ray.d;
	
	float d_squared = center.d_squared(p);
	
	if (d_squared < r_max_squared && d_squared > r_min_squared) {
		Vector3D hit = ray.o + t * ray.d - center;
		
		double phi = atan2(hit.x, hit.z);
		if (phi < 0.0)
			phi += TWO_PI;
		
		if (phi >= phi_min && phi <= phi_max) {
			tmin = t;
//			sr.normal = normal;
//			sr.local_hit_point = p;
			return (true);
		}
		else 
			return (false);
	}
	else
		return (false);
}	

float
PartAnnulus::d_squared(Point3D p) {
	// is this correct and efficient?
	return (pow((p.distance(center)), 2));
}

BBox
PartAnnulus::get_bounding_box(void) const {
	double delta = 0.0001; 
	
	// This is Circle's bounding box, could be more efficient
	
	return (BBox(Point3D(center.x - r_max - delta, center.y - r_max - delta, center.z - r_max - delta),
				 Point3D(center.x + r_max + delta, center.y + r_max + delta, center.z + r_max + delta)));
}