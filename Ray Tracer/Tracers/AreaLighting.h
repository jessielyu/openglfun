#ifndef __AREA_LIGHTING__
#define __AREA_LIGHTING__

/*
 *  AreaLighting.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Tracer.h"

class AreaLighting: public Tracer {
public:
	
	AreaLighting(void);							
	
	AreaLighting(World* _world_ptr);
	
	~AreaLighting(void);
	
	virtual MyRGBColor	
	trace_ray(const Ray& ray) const;
	
	virtual MyRGBColor	
	trace_ray(const Ray ray, const int depth) const;
	
	virtual MyRGBColor
	trace_ray(const Ray ray, double& tmin, const int depth) const;
};

#endif
