/*
 *  Compound.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Compound.h"

Compound::Compound(void) 
:	GeometricObject()
{}

Compound*
Compound::clone(void) const {
	return (new Compound(*this));
}

Compound::Compound(const Compound& c) 
:	GeometricObject(c) {
	copy_objects(c.objects);
}

Compound::~Compound(void) {
	delete_objects();
}

Compound&
Compound::operator= (const Compound& c) {
	if (this == &c)
		return (*this);
	
	GeometricObject::operator= (c);
	
	copy_objects(c.objects);
	
	return (*this);
}

void
Compound::set_material(Material* mat_ptr) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(mat_ptr);
}

void
Compound::add_object(GeometricObject* obj_ptr) {
	objects.push_back(obj_ptr);
}

bool
Compound::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double t;
	Normal normal;
	Point3D local_hit_point;
	bool hit = false;
	tmin = kHugeValue;
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			hit				= true;
			tmin			= t;
			material_ptr	= objects[j]->get_material();
			normal			= sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	
	if (hit) {
		sr.t				= tmin;
		sr.normal			= normal;
		sr.local_hit_point	= local_hit_point;
	}
	
	return (hit);
}

bool
Compound::shadow_hit(const Ray& ray, float& tmin) const {
	float t;
//	Normal normal;
//	Point3D local_hit_point;
	bool hit = false;
	tmin = kHugeValue;
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->shadow_hit(ray, t) && (t < tmin)) {
			hit				= true;
			tmin			= t;
			//material_ptr	= objects[j]->get_material();
			//normal			= sr.normal;
			//local_hit_point = sr.local_hit_point;
		}
	
//	if (hit) {
//		sr.t				= tmin;
//		sr.normal			= normal;
//		sr.local_hit_point	= local_hit_point;
//	}
	
	return (hit);
}

void
Compound::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		if (objects[j]) {
			delete objects[j];
			objects[j] = NULL;
		}
	}
	
	objects.erase(objects.begin(), objects.end());
}

void
Compound::copy_objects(const std::vector<GeometricObject*>& rhs_objects) {
	
	delete_objects();
	
	int num_objects = rhs_objects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_objects[j]->clone());
	
}