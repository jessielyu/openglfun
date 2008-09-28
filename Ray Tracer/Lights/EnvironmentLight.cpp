/*
 *  EnvironmentLight.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "EnvironmentLight.h"
#include "World.h"

EnvironmentLight::EnvironmentLight(void)
:	Light(),
sampler_ptr(NULL),
material_ptr(NULL)
{}

EnvironmentLight::EnvironmentLight(const EnvironmentLight& al)
:	Light(al),
	u(al.u),
	v(al.v),
	w(al.w),
	wi(al.wi)
{
	if (al.sampler_ptr)
		sampler_ptr = al.sampler_ptr->clone();
	else
		sampler_ptr = NULL;
	
	if (al.material_ptr)
		material_ptr = al.material_ptr->clone();
	else
		material_ptr = NULL;
}

EnvironmentLight&
EnvironmentLight::operator= (const EnvironmentLight& al) {
	if (this == &al)
		return (*this);
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
	
	if (al.sampler_ptr)
		sampler_ptr = al.sampler_ptr->clone();
	
	if (al.material_ptr)
		material_ptr = al.material_ptr->clone();
	
	u = al.u;
	v = al.v;
	w = al.w;
	wi = al.wi;
	
	return (*this);
}

EnvironmentLight::~EnvironmentLight(void) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}

EnvironmentLight*
EnvironmentLight::clone(void) const {
	return (new EnvironmentLight(*this));
}

void
EnvironmentLight::set_sampler(Sampler* s_ptr) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

void
EnvironmentLight::set_material(Material* material) {
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
	
	material_ptr = material;
}

Vector3D
EnvironmentLight::get_direction(ShadeRec& sr) {
	w = sr.normal;
	v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	u = v ^ w;
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	
	return(wi);
}


bool
EnvironmentLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int num_objects = sr.w.objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		if (sr.w.objects[j]->shadow_hit(ray, t))
			return (true);
	}
	
	return (false);
}

MyRGBColor
EnvironmentLight::L(ShadeRec& sr) {
	return (material_ptr->get_Le(sr));
}


float
EnvironmentLight::pdf(const ShadeRec& sr) const {
	return (sr.normal * wi * invPI);
}