#ifndef __AMBIENT_OCCLUDER__
#define __AMBIENT_OCCLUDER__

/*
 *  AmbientOccluder.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Ambient.h"
#include "Sampler.h"

class AmbientOccluder: public Ambient {
public:
	
	AmbientOccluder(void);
	
	AmbientOccluder(const AmbientOccluder& amb);
	
	AmbientOccluder&
	operator= (const AmbientOccluder& amb);
	
	~AmbientOccluder(void);
	
	void
	set_sampler(Sampler* s_ptr);
	
	virtual Vector3D
	get_direction(ShadeRec& sr);
	
	virtual bool
	in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
	void
	set_min_amount(const float min);
	
private:
	
	Vector3D u, v, w;			// Used to form an orthonormal basis
	Sampler* sampler_ptr;		// To sample the hemisphere around a point
	MyRGBColor min_amount;		// Used to shade parts that are occluded
//	float ls;					// light brightness
};

inline void
AmbientOccluder::set_min_amount(const float min) {
	min_amount.r = min_amount.g = min_amount.b = min;
}

#endif