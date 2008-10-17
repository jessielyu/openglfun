/*
 *  SolidCylinder.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "SolidCylinder.h"
#include "Disk.h"
#include "OpenCylinder.h"

SolidCylinder::SolidCylinder(void)
:	Compound(),
	bbox(Point3D(-1,-1,-1), Point3D(1,1,1)) {
	objects.push_back(new Disk(Point3D(0,-1,0), 1, Normal(0, -1, 0)));
	objects.push_back(new Disk(Point3D(0,1,0), 1, Normal(0,1,0)));
	objects.push_back(new OpenCylinder(-1, 1, 1));
}

SolidCylinder::SolidCylinder(const float bottom, const float top, const float radius)
:	Compound(),
	bbox(Point3D(-radius, bottom, -radius), Point3D(radius, top, radius)) {
	objects.push_back(new Disk(Point3D(0,bottom,0), radius, Normal(0, -1, 0)));
	objects.push_back(new Disk(Point3D(0,top,0), radius, Normal(0,1,0)));
	objects.push_back(new OpenCylinder(bottom, top, radius));
}

SolidCylinder::SolidCylinder(const SolidCylinder& cc)
:	Compound(cc),
	bbox(cc.bbox) {}

SolidCylinder&
SolidCylinder::operator= (const SolidCylinder& cc) {
	if (this == &cc)
		return (*this);
	
	Compound::operator= (cc);
	
	bbox = cc.bbox;
	
	return (*this);
}

SolidCylinder*
SolidCylinder::clone(void) const {
	return (new SolidCylinder(*this));
}

bool
SolidCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

bool
SolidCylinder::shadow_hit(const Ray& ray, float& tmin) const {
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

BBox
SolidCylinder::get_bounding_box(void) const {
	return bbox;
}