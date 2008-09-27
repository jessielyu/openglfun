/*
 *  AreaLight.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "AreaLight.h"
#include "World.h"

AreaLight::AreaLight(void)
:	Light(),
	object_ptr(NULL),
	material_ptr(NULL)
{}

AreaLight::AreaLight(const AreaLight& al)
:	Light(al) {
	if (al.object_ptr)
		object_ptr = al.object_ptr->clone();
	else
		object_ptr = NULL;
	
	if (al.material_ptr)
		material_ptr = al.material_ptr->clone();
	else
		material_ptr = NULL;
}

AreaLight&
AreaLight::operator= (const AreaLight& al) {
	if (this == &al)
		return (*this);
	
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}
	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
	
	if (al.object_ptr)
		object_ptr = al.object_ptr->clone();
	
	if (al.material_ptr)
		material_ptr = al.material_ptr->clone();
	
	return (*this);
}

AreaLight::~AreaLight(void) {
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}
	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}
	
AreaLight*
AreaLight::clone(void) const {
	return (new AreaLight(*this));
}

Vector3D
AreaLight::get_direction(ShadeRec& sr) {
	sample_point = object_ptr->sample();
	light_normal = object_ptr->get_normal(sample_point);
	wi = sample_point - sr.hit_point;
	
	return (wi);
}
	

bool
AreaLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int num_objects = sr.w.objects.size();
	float ts = (sample_point - ray.o) * ray.d;
	
	for(int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < ts)
			return true;
	
	return (false);
}

MyRGBColor
AreaLight::L(ShadeRec& sr) {
	float ndotd = -light_normal * wi;
	
	if (ndotd > 0.0)
		return (material_ptr->get_Le(sr));
	else
		return (black);
}

float
AreaLight::G(const ShadeRec& sr) const {
	float ndotd = -light_normal * wi;
	float d2 = sample_point.d_squared(sr.hit_point);
	
	return (ndotd / d2);
}
	

float
AreaLight::pdf(const ShadeRec& sr) const {
	return (object_ptr->pdf(sr));
}