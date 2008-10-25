/*
 *  GlossySpecular.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GlossySpecular.h"
#include "MultiJittered.h"

GlossySpecular::GlossySpecular(void)
:	BRDF(),
ks(1.0),
cs(MyRGBColor(0,0,0)),
exp(1.0),
sampler_ptr(NULL)
{}

GlossySpecular::GlossySpecular(const GlossySpecular& lamb)
:	BRDF(lamb),
ks(lamb.ks),
cs(lamb.cs),
exp(1.0)
{
	if (lamb.sampler_ptr)
		sampler_ptr = lamb.sampler_ptr->clone();
	else
		sampler_ptr = NULL;
}

GlossySpecular&
GlossySpecular::operator= (const GlossySpecular& rhs) {
	if (this == &rhs)
		return (*this);
	
	BRDF::operator= (rhs);
	
	ks = rhs.ks;
	cs = rhs.cs;
	exp = rhs.exp;
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();
	
	return (*this);
}

GlossySpecular::~GlossySpecular(void) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

BRDF*
GlossySpecular::clone(void) const {
	return (new GlossySpecular(*this));
}

// just Phong
MyRGBColor
GlossySpecular::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
	MyRGBColor L;
	float ndotwi = sr.normal * wi;
	Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
	float rdotwo = r * wo;
	
	if (rdotwo > 0.0)
		L = ks * pow(rdotwo, exp);
	
	return (L);
}

MyRGBColor
GlossySpecular::sample_f(const ShadeRec& sr,Vector3D& wi, const Vector3D& w0) const {
	return (black);
}

MyRGBColor
GlossySpecular::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const {
	
	float ndotwo = sr.normal * wo;
	Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection
	
	Vector3D w = r;								
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w; 
	u.normalize();
	Vector3D v = u ^ w;
	
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;			// reflected ray direction
	
	if (sr.normal * wi < 0.0) 						// reflected ray is below tangent plane
		wi = -sp.x * u - sp.y * v + sp.z * w;
	
	float phong_lobe = pow(r * wi, exp);
	pdf = phong_lobe * (sr.normal * wi);
	
	return (ks * cs * phong_lobe);
	
}

MyRGBColor
GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const{
	return (black);
}

void
GlossySpecular::set_samples(const int num_samples, const float exp) {
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}