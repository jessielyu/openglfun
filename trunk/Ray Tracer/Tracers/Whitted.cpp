/*
 *  Whitted.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Whitted.h"
#include "World.h"
#include "Material.h"

// -------------------------------------------------------------------- default constructor

Whitted::Whitted(void)
: Tracer()
{}


// -------------------------------------------------------------------- constructor

Whitted::Whitted(World* _worldPtr)
: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

Whitted::~Whitted(void) {}


// -------------------------------------------------------------------- trace_ray

MyRGBColor	
Whitted::trace_ray(const Ray& ray) const {
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
Whitted::trace_ray(const Ray ray, const int depth) const {
	
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
		
		if (sr.hit_an_object)   {
			sr.depth = depth;
			sr.ray = ray;
			return (sr.material_ptr->shade(sr));   
		}
		else
			return (world_ptr->background_color);
	}
}

MyRGBColor
Whitted::trace_ray(const Ray ray, double& tmin, const int depth) const {
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));    
		
		if (sr.hit_an_object) {
			sr.depth 	= depth;
			sr.ray 		= ray;	
			tmin		= sr.t;     // required for colored transparency 
			
			return (sr.material_ptr->shade(sr));   
		}
		else {
			tmin = kHugeValue;
			
			return (world_ptr->background_color);
		}
	}
}

