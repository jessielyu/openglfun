#ifndef __OPEN_CYLINDER__
#define __OPEN_CYLINDER__

/*
 *  OpenCylinder.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/12/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"

class OpenCylinder: public GeometricObject {
public:
	
	OpenCylinder(void);
	
	OpenCylinder(const double bottom, const double top, const double radius);
	
	OpenCylinder(const OpenCylinder& c);
	
	virtual OpenCylinder*
	clone(void) const;
	
	OpenCylinder&
	operator= (const OpenCylinder& c);
	
	virtual
	~OpenCylinder(void);
	
	virtual bool
	hit(const Ray& ray, double& t, ShadeRec& sr) const;
	
	virtual bool
	shadow_hit(const Ray& ray, float& t) const;
	
	virtual BBox
	get_bounding_box(void) const;
	
protected:
	
	double y0;				// bottom
	double y1;				// top
	double radius;			
	double inv_radius;		// 1 / radius
};

#endif