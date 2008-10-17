#ifndef __SOLID_CYLINDER__
#define __SOLID_CYLINDER__

/*
 *  SolidCylinder.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Compound.h"

class SolidCylinder: public Compound {
public:
	
	SolidCylinder(void);
	
	SolidCylinder(const float bottom, const float top, const float radius);
	
	SolidCylinder(const SolidCylinder& cc);
	
	SolidCylinder&
	operator= (const SolidCylinder& cc);
	
	virtual SolidCylinder*
	clone(void) const;
	
	virtual bool
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	
	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const;

	virtual BBox
	get_bounding_box(void) const;
	
private:
	BBox bbox;
};

#endif