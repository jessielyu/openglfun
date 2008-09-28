#ifndef __CONCAVE_SPHERE__
#define __CONCAVE_SPHERE__

/*
 *  ConcaveSphere.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Sphere.h"

class ConcaveSphere: public Sphere {
public:
	ConcaveSphere(void);
	
	ConcaveSphere(const ConcaveSphere& cs);
	
	ConcaveSphere&
	operator= (const ConcaveSphere& cs);
	
	virtual Sphere* 									// Virtual copy constructor
	clone(void) const;
	
	virtual bool 												 
	hit(const Ray& ray, double& t, ShadeRec& s) const;	
	
};

#endif