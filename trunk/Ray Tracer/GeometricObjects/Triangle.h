#ifndef __TRIANGLE__
#define __TRIANGLE__

/*
 *  Triangle.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/8/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"

class Triangle: public GeometricObject {
public:
	Point3D v0, v1, v2;
	Normal normal;
	
	Triangle(void);
	
	Triangle(const Point3D& a, const Point3D& b, const Point3D& c);
	
	Triangle(const Triangle& tri);
	
	Triangle&
	operator=(const Triangle& tri);
	
	Triangle*
	clone(void) const;
	
	virtual bool 
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	
	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const;
	
	virtual BBox
	get_bounding_box(void) const;
};

#endif