/*
 *  AmbientOccluder.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "AmbientOccluder.h"
#include "World.h"

AmbientOccluder::AmbientOccluder(void) 
:	Ambient(),
	sampler_ptr(NULL)
{}

AmbientOccluder::AmbientOccluder(const AmbientOccluder& amb)
:	Ambient(amb),
	sampler_ptr(amb.sampler_ptr->clone()),
	min_amount(MyRGBColor(0.001))
{}

AmbientOccluder&
AmbientOccluder::operator= (const AmbientOccluder& amb)	{
	if (this == &amb)
		return (*this);
	
	Ambient::operator= (amb);
	
	if (amb.sampler_ptr) {
		if (sampler_ptr) {
			delete sampler_ptr;
			sampler_ptr = NULL;
		}
		
		sampler_ptr = amb.sampler_ptr->clone();
	}
	
	return (*this);
}

AmbientOccluder::~AmbientOccluder(void){
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

void
AmbientOccluder::set_sampler(Sampler* s_ptr) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D
AmbientOccluder::get_direction(ShadeRec& sr){
	Point3D sp = sampler_ptr->sample_hemisphere();
	return (sp.x * u + sp.y * v + sp.z * w);
}

bool
AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int num_objects = sr.w.objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		if (sr.w.objects[j]->shadow_hit(ray, t))
			return (true);
	}
	
	return (false);
}

MyRGBColor
AmbientOccluder::L(ShadeRec& sr) {
	w = sr.normal;
	// jitter the up vector, otherwise normal being vertical will be a problem
	v = w ^ Vector3D(0.0072, 1.0, 0.0034);
	v.normalize();
	u = v ^ w;
	
	Ray shadow_ray;
	shadow_ray.o = sr.hit_point;
	shadow_ray.d = get_direction(sr);
	
	if (in_shadow(shadow_ray, sr))
		return (min_amount * ls * color);
	else
		return (ls * color);
}