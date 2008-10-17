#ifndef __CONVEX_PART_SPHERE__
#define __CONVEX_PART_SPHERE__

/*
 *  ConvexPartSphere.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"

class ConvexPartSphere: public GeometricObject {
public:
	
	Point3D		center;			// 
	double		radius;			//min azimuth angle, degrees, measured counter-clockwise from + z axis 
	double		phi_min;		// 
	double		phi_max;		// 
	double		theta_min;		// min polar angle, degrees, measured down from y axis
	double		theta_max;		// 
	
	double		cos_theta_min;	// 	avoid calculating this a lot
	double		cos_theta_max;	// 	
	
	ConvexPartSphere(void);
	
	ConvexPartSphere(const Point3D c,
					 const double r,
					 const double azimuth_min, // degrees
					 const double azimuth_max, // degrees
					 const double polar_min,   // degrees from top
					 const double polar_max);  // degrees from top
	
	ConvexPartSphere(const Point3D c, const double radius);
	
	virtual ConvexPartSphere*
	clone(void) const;
	
	ConvexPartSphere(const ConvexPartSphere& cp);
	
	virtual
	~ConvexPartSphere(void);
	
	ConvexPartSphere& 
	operator= (const ConvexPartSphere& rhs);
	
	virtual bool
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	
	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const;
	
	virtual BBox
	get_bounding_box(void) const;
	
};

#endif