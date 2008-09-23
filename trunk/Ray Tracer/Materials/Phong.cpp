/*
 *  Phong.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Phong.h"
#include "World.h"

Phong::Phong(void) 
:	Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian),
	specular_brdf(new GlossySpecular)
{}

Phong::Phong(const Phong& rhs)
:	Material(rhs) {	
	
	if (rhs.ambient_brdf)
		ambient_brdf = (Lambertian*)rhs.ambient_brdf->clone();
	else
		ambient_brdf = NULL;
	
	if (rhs.diffuse_brdf)
		diffuse_brdf = (Lambertian*)rhs.diffuse_brdf->clone();
	else
		diffuse_brdf = NULL;
	
	if (rhs.specular_brdf)
		specular_brdf = (GlossySpecular*)rhs.specular_brdf->clone();
	else
		specular_brdf = NULL;
}

Phong::~Phong(void) {
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
	
	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}
	
}

Phong&
Phong::operator= (const Phong& p) {
	if (this == &p)
		return (*this);
	
	Material::operator= (p);
	
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
	
	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}
	
	if (p.ambient_brdf)
		ambient_brdf = (Lambertian*)p.ambient_brdf->clone();
	
	if (p.diffuse_brdf)
		diffuse_brdf = (Lambertian*)p.diffuse_brdf->clone();
	
	if (p.specular_brdf)
		specular_brdf = (GlossySpecular*)p.specular_brdf->clone();
}

Material*
Phong::clone(void) const {
	return (new Phong(*this));
}


MyRGBColor
Phong::shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	MyRGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;
		
		if (ndotwi > 0.0)
			L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi;
	}
	
	return (L);
}

void
Phong::set_ka(const float ka) {
	if (ambient_brdf)
		ambient_brdf->set_kd(ka);
}

void
Phong::set_kd(const float kd) {
	if (diffuse_brdf)
		diffuse_brdf->set_kd(kd);
}

void
Phong::set_ks(const float ks) {
	if (specular_brdf)
		specular_brdf->set_ks(ks);
}

void
Phong::set_ca(const float r, const float g, const float b) {
	if (ambient_brdf)
		ambient_brdf->set_cd(r, g, b);
}

void
Phong::set_cd(const float r, const float g, const float b) {
	if (diffuse_brdf)
		diffuse_brdf->set_cd(r,g,b);
}

void
Phong::set_cs(const float r, const float g, const float b) {
	if (specular_brdf)
		specular_brdf->set_cs(r, g, b);
}

void
Phong::set_exp_s(const float exp_s){
	if (specular_brdf)
		specular_brdf->set_exp(exp_s);
}

void 
Phong::set_k(const float k) {
	if (ambient_brdf)
		ambient_brdf->set_kd(k);
	
	if (diffuse_brdf)
		diffuse_brdf->set_kd(k);
	
	if (specular_brdf)
		specular_brdf->set_ks(k);
}

void
Phong::set_c(const float r, const float g, const float b) {
	if (ambient_brdf)
		ambient_brdf->set_cd(r,g,b);
	
	if (diffuse_brdf)
		diffuse_brdf->set_cd(r,g,b);
	
	if (specular_brdf)
		specular_brdf->set_cs(r,g,b);
}

void
Phong::set_c(const MyRGBColor& c) {
	if (ambient_brdf)
		ambient_brdf->set_cd(c);
	
	if (diffuse_brdf)
		diffuse_brdf->set_cd(c);
	
	if (specular_brdf)
		specular_brdf->set_cs(c);
}