/*
 *  PathTrace.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/23/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "PathTrace.h"
#include "World.h"
#include "Material.h"

// -------------------------------------------------------------------- default constructor

PathTrace::PathTrace(void)
: Tracer()
{}


// -------------------------------------------------------------------- constructor

PathTrace::PathTrace(World* _worldPtr)
: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

PathTrace::~PathTrace(void) {}


// -------------------------------------------------------------------- trace_ray

MyRGBColor	
PathTrace::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
	
	if (sr.hit_an_object)   {
		sr.ray = ray;
		return (sr.material_ptr->shade(sr));   
	}
	else
		return (world_ptr->background_color);
}

// --------------------------------------- DEPTH NOT USED YET 

MyRGBColor	
PathTrace::trace_ray(const Ray ray, const int depth) const {
	
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
		
		if (sr.hit_an_object)   {
			sr.depth = depth;
			sr.ray = ray;
			return (sr.material_ptr->path_shade(sr));   
		}
		else
			return (world_ptr->background_color);
	}
}

