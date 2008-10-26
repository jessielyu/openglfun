/*
 *  Transparent.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/25/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Transparent.h"
#include "World.h"

Transparent::Transparent(void)
:	reflective_brdf(new PerfectSpecular),
	specular_btdf(new PerfectTransmitter) {
	//	reflective_brdf->set_cr(white);
}

Transparent::Transparent(const Transparent& trans)
:	reflective_brdf(trans.reflective_brdf),
	specular_btdf(trans.specular_btdf) {}

Transparent*
Transparent::clone(void) const {
	return (new Transparent(*this));
}

Transparent&
Transparent::operator= (const Transparent& trans) {
	if (this == &trans)
		return (*this);
	
	if (reflective_brdf)
	{
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
	
	if (specular_btdf) {
		delete specular_btdf;
		specular_btdf = NULL;
	}
	
	if (trans.reflective_brdf)
		reflective_brdf = trans.reflective_brdf;
	
	if (trans.specular_btdf)
		specular_btdf = trans.specular_btdf;
	
	return (*this);
}

MyRGBColor
Transparent::shade(ShadeRec& sr) {
	MyRGBColor L(Phong::shade(sr));
	
	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	MyRGBColor fr = reflective_brdf->sample_f(sr, wi, wo);
	Ray reflected_ray(sr.hit_point, wi);
	
	if(specular_btdf->tir(sr))
		L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth +1);
	else {
		Vector3D wt;
		MyRGBColor ft = specular_btdf->sample_f(sr, wo, wt);
		Ray transmitted_ray(sr.hit_point, wt);
		
		L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * fabs(sr.normal * wi);
		L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1) * fabs(sr.normal * wt);
	}
	
	return (L);
}

Transparent::~Transparent(void) {
	if (reflective_brdf)
	{
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
	
	if (specular_btdf) {
		delete specular_btdf;
		specular_btdf = NULL;
	}
}