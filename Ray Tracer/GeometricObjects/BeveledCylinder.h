#ifndef __BEVELED_CYLINDER__
#define __BEVELED_CYLINDER__

/*
 *  BeveledCylinder.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Compound.h"

class BeveledCylinder: public Compound {
public:
	
	BeveledCylinder(void);
	
	BeveledCylinder(const float bottom, const float top, const float radius, const float bevel_radius);
	
	BeveledCylinder(const BeveledCylinder& cc);
	
	BeveledCylinder&
	operator= (const BeveledCylinder& cc);
	
	virtual BeveledCylinder*
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