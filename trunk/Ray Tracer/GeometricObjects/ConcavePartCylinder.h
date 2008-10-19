#ifndef __CONCAVE_PART_CYLINDER__
#define __CONCAVE_PART_CYLINDER__

/*
 *  ConcavePartCylinder.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "ConvexPartCylinder.h"

class ConcavePartCylinder: public ConvexPartCylinder {
public:
	
	ConcavePartCylinder(void);
	
	ConcavePartCylinder(const double bottom, const double top, const double radius, const double azimuth_min, // degrees
					   const double azimuth_max);
	
	ConcavePartCylinder(const ConcavePartCylinder& c);
	
	virtual ConcavePartCylinder*
	clone(void) const;
	
	ConcavePartCylinder&
	operator= (const ConcavePartCylinder& c);
	
	virtual bool
	hit(const Ray& ray, double& t, ShadeRec& sr) const;
};

#endif