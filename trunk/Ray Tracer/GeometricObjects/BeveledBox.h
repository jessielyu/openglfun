#ifndef __BEVELED_BOX__
#define __BEVELED_BOX__

/*
 *  BeveledBox.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Compound.h"

class BeveledBox: public Compound {
public:
	
	BeveledBox(void);
	
	BeveledBox(const Point3D p0, const Point3D p1, const float rb, const bool wireframe);
	
	BeveledBox(const BeveledBox& cc);
	
	BeveledBox&
	operator= (const BeveledBox& cc);
	
	virtual BeveledBox*
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