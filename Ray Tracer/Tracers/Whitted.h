#ifndef __WHITTED__
#define __WHITTED__

/*
 *  Whitted.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Tracer.h"

class Whitted: public Tracer {
public:
	
	Whitted(void);							
	
	Whitted(World* _world_ptr);
	
	~Whitted(void);
	
	virtual MyRGBColor	
	trace_ray(const Ray& ray) const;
	
	virtual MyRGBColor	
	trace_ray(const Ray ray, const int depth) const;
};

#endif
