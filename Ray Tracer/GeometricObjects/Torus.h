#ifndef __TORUS__
#define __TORUS__

/*
 *  Torus.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/12/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"

class Torus: public GeometricObject {
public:
	
	Torus(void);
	
	Torus(const double a, const double b);
	
	virtual Torus*
	clone(void) const;
	
	Torus(const Torus& torus);
	
	virtual
	~Torus(void); 											
	
	Torus& 
	operator= (Torus& rhs);
	
	Normal
	compute_normal(const Point3D& p) const;
	
	virtual bool
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	
	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const;
	
	virtual BBox
	get_bounding_box(void) const;
	
private:
	
	double	a;		// swept radius
	double	b;		// tube radius
	BBox	bbox;
};

inline BBox
Torus::get_bounding_box(void) const {
	return bbox;
}

#endif