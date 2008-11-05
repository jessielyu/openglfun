/*
 *  SV_Matte.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "SV_Matte.h"
#include "World.h"

SV_Matte::SV_Matte(void)
:	Material(),
ambient_ptr(new SV_Lambertian),
diffuse_ptr(new SV_Lambertian)
{}

SV_Matte::SV_Matte(const SV_Matte& m) 
:	Material(m) {
	if (m.ambient_ptr)
		ambient_ptr = (SV_Lambertian*)m.ambient_ptr->clone();
	else
		ambient_ptr = NULL;
	
	if (m.diffuse_ptr)
		diffuse_ptr = (SV_Lambertian*)m.diffuse_ptr->clone();
	else
		ambient_ptr = NULL;
}

SV_Matte::~SV_Matte(void) {
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
	if (diffuse_ptr) {
		delete diffuse_ptr;
		diffuse_ptr = NULL;
	}
}

SV_Matte& 
SV_Matte::operator= (const SV_Matte& m) {
	if (this == &m)
		return (*this);
	
	Material::operator= (m);
	
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
	if (diffuse_ptr) {
		delete diffuse_ptr;
		diffuse_ptr = NULL;
	}
	
	if (m.ambient_ptr)
		ambient_ptr = (SV_Lambertian*)m.ambient_ptr->clone();
	
	
	if (m.diffuse_ptr)
		diffuse_ptr = (SV_Lambertian*)m.diffuse_ptr->clone();
	
	return (*this);
}

Material*
SV_Matte::clone(void) const {
	return (new SV_Matte(*this));
}

void
SV_Matte::set_sampler(Sampler* sampl_ptr) {
	
	ambient_ptr->set_sampler(sampl_ptr);
	diffuse_ptr->set_sampler(sampl_ptr->clone());
}

void
SV_Matte::set_ka(const float ka) {
	ambient_ptr->set_kd(ka);
}

void
SV_Matte::set_kd(const float kd) {
	diffuse_ptr->set_kd(kd);
}



MyRGBColor
SV_Matte::shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	MyRGBColor L = ambient_ptr->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int numLights = sr.w.lights.size();
	
	for(int j = 0; j < numLights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;
		
		if (ndotwi > 0.0)	{
			bool in_shadow = false;
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadow_ray(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
			}
			
			if (!in_shadow)
				L+=diffuse_ptr->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
		}
	}
	
	return (L);
}

MyRGBColor
SV_Matte::area_light_shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	MyRGBColor L = ambient_ptr->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;
		
		if (ndotwi > 0.0) {
			bool in_shadow = false;
			
			if (!shadows)
				;
			else {		
				bool in_shadow = false;
				if (sr.w.lights[j]->casts_shadows()) {
					Ray shadow_ray(sr.hit_point, wi);
					in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
				}
			}
			
			if (!in_shadow)
				L += diffuse_ptr->f(sr, wo, wi) * sr.w.lights[j]->L(sr) *
				sr.w.lights[j]->G(sr) * ndotwi /
				sr.w.lights[j]->pdf(sr);
		}
	}
	return (L);
}

MyRGBColor
SV_Matte::path_shade(ShadeRec& sr) {
	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	MyRGBColor f = diffuse_ptr->sample_f(sr, wi, wo, pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point, wi);
	
	return (f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf);
}

MyRGBColor
SV_Matte::global_shade(ShadeRec& sr) {
	MyRGBColor L;
	
	if (sr.depth == 0)
		L = area_light_shade(sr);
	
	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	MyRGBColor f = diffuse_ptr->sample_f(sr, wi, wo, pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point, wi);
	L += f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf;
	
	return (L);
}
