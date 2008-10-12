#ifndef __DISK__
#define __DISK__

/*
 *  Disk.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/12/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"

class Disk: public GeometricObject {
public:
	
	Disk(void);
	
	Disk(Point3D c, float r, Normal n);
	
	Disk(const Disk& d);
	
	Disk&
	operator=(const Disk& d);
	
	virtual Disk*
	clone(void) const;
	
	virtual bool
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	
	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const;
	
	float
	d_squared(Point3D p);
	
	virtual BBox
	get_bounding_box(void) const;
	
private:
	Point3D center;
	float r_squared;
	float radius;		// for bbox
	Normal normal;
};

#endif