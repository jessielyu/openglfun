/*
 *  Matte.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Matte.h"
#include "World.h"

Matte::Matte(void)
:	Material(),
	ambient_ptr(new Lambertian),
	diffuse_ptr(new Lambertian)
{}
 
Matte::Matte(const Matte& m) 
:	Material(m) {
	if (m.ambient_ptr)
		ambient_ptr = (Lambertian*)m.ambient_ptr->clone();
	else
		ambient_ptr = NULL;
	
	if (m.diffuse_ptr)
		diffuse_ptr = (Lambertian*)m.diffuse_ptr->clone();
	else
		ambient_ptr = NULL;
}

Matte::~Matte(void) {
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
	if (diffuse_ptr) {
		delete diffuse_ptr;
		diffuse_ptr = NULL;
	}
}

Matte& 
Matte::operator= (const Matte& m) {
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
		ambient_ptr = (Lambertian*)m.ambient_ptr->clone();
	
	
	if (m.diffuse_ptr)
		diffuse_ptr = (Lambertian*)m.diffuse_ptr->clone();
	
	return (*this);
}

Material*
Matte::clone(void) const {
	return (new Matte(*this));
}

void
Matte::set_ka(const float ka) {
	ambient_ptr->set_kd(ka);
}

void
Matte::set_kd(const float kd) {
	diffuse_ptr->set_kd(kd);
}

void
Matte::set_cd(const MyRGBColor& c) {
	ambient_ptr->set_cd(c);
	diffuse_ptr->set_cd(c);
}

MyRGBColor
Matte::shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	MyRGBColor L = ambient_ptr->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int numLights = sr.w.lights.size();
	
	for(int j = 0; j < numLights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;
		
		if (ndotwi > 0.0)
			L+=diffuse_ptr->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
	}
	
	return (L);
}


