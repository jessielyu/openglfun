/*
 *  Disk.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/12/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Disk.h"

Disk::Disk(void) 
:	GeometricObject(),
	center(1,1,1),
	r_squared(9),
	radius(3),
	normal(0,0,1)
{}

Disk::Disk(Point3D c, float r, Normal n) 
:	GeometricObject(),
	center(c),
	r_squared(pow(r,2)),
	radius(r),
	normal(n)
{}

Disk::Disk(const Disk& d)
:	GeometricObject(d),
	center(d.center),
	r_squared(d.r_squared),
	radius(d.radius),
	normal(d.normal)
{}

Disk&
Disk::operator=(const Disk& d) {
	if (this == &d)
		return (*this);
	
	center = d.center;
	r_squared = d.r_squared;
	normal = d.normal;
	radius = d.radius;
	
	return (*this);
}

Disk*
Disk::clone(void) const {
	return (new Disk(*this));
}

bool
Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	float t = (center - ray.o) * normal / (ray.d * normal);
	
	if (t <= kEpsilon)
		return (false);
	
	Point3D p = ray.o + t * ray.d;
	
	if (center.d_squared(p) < r_squared) {
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = p;
		return (true);
	}
	else
		return (false);
}	

bool
Disk::shadow_hit(const Ray& ray, float& tmin) const {
	float t = (center - ray.o) * normal / (ray.d * normal);
	
	if (t <= kEpsilon)
		return (false);
	
	Point3D p = ray.o + t * ray.d;
	
	if (center.d_squared(p) < r_squared) {
		tmin = t;
//		sr.normal = normal;
//		sr.local_hit_point = p;
		return (true);
	}
	else
		return (false);
}	

float
Disk::d_squared(Point3D p) {
	// is this correct and efficient?
	return (pow((p.distance(center)), 2));
}

BBox
Disk::get_bounding_box(void) const {
	double delta = 0.0001; 
	
	// This is Circle's bounding box, could be more efficient
	
	return (BBox(Point3D(center.x - radius - delta, center.y - radius - delta, center.z - radius - delta),
				 Point3D(center.x + radius + delta, center.y + radius + delta, center.z + radius + delta)));
}