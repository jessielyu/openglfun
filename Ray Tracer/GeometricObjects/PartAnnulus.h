#ifndef __PART_ANNULUS__
#define __PART_ANNULUS__

/*
 *  PartAnnulus.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"

class PartAnnulus: public GeometricObject {
public:
	
	PartAnnulus(void);
	
	PartAnnulus(const Point3D c, const Normal n, const float r_min, const float r_max, const float phi_min, const float phi_max);
	
	PartAnnulus(const PartAnnulus& d);
	
	PartAnnulus&
	operator=(const PartAnnulus& d);
	
	virtual PartAnnulus*
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
	float r_max_squared;
	float r_min_squared;
	float r_min;		// for bbox
	float r_max;
	float phi_min;
	float phi_max;
	Normal normal;
};

#endif