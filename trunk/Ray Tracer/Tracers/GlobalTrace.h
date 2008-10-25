#ifndef __GLOBAL_TRACE__
#define __GLOBAL_TRACE__

/*
 *  GlobalTrace.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/24/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Tracer.h"

class GlobalTrace: public Tracer {
public:
	
	GlobalTrace(void);							
	
	GlobalTrace(World* _world_ptr);
	
	~GlobalTrace(void);
	
	virtual MyRGBColor	
	trace_ray(const Ray& ray) const;
	
	virtual MyRGBColor	
	trace_ray(const Ray ray, const int depth) const;
};

#endif
