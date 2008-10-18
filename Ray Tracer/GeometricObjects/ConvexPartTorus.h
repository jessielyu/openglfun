#ifndef __CONVEX_PART_TORUS__
#define __CONVEX_PART_TORUS__

/*
 *  ConvexPartTorus.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"

class ConvexPartTorus: public GeometricObject {
public:
	
	ConvexPartTorus(void);
	
	ConvexPartTorus(const double a, const double b,	
					const double azimuth_min, // degrees
					const double azimuth_max, // degrees
					const double polar_min,   // degrees from top
					const double polar_max);  // degrees from top);
	
	virtual ConvexPartTorus*
	clone(void) const;
	
	ConvexPartTorus(const ConvexPartTorus& torus);
	
	virtual
	~ConvexPartTorus(void); 											
	
	ConvexPartTorus& 
	operator= (ConvexPartTorus& rhs);
	
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
	double		phi_min;		// 
	double		phi_max;		// 
	double		theta_min;		// min polar angle, degrees, measured counter clockwise from xz plane
	double		theta_max;		// 
	
//	double		cos_theta_min;	// 	avoid calculating this a lot
//	double		cos_theta_max;	// 
};

inline BBox
ConvexPartTorus::get_bounding_box(void) const {
	return bbox;
}

#endif