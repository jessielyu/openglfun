#ifndef __FRESNEL_REFLECTOR__
#define __FRESNEL_REFLECTOR__

/*
 *  FresnelReflector.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "BRDF.h"

class FresnelReflector: public BRDF {
public:
	FresnelReflector(void);
	
	FresnelReflector(const FresnelReflector& lamb);
	
	FresnelReflector&
	operator= (const FresnelReflector& rhs);
	
	~FresnelReflector(void);
	
	virtual BRDF*
	clone(void) const;
	
//	void
//	set_kr(const float the_kr);
//	
//	void
//	set_cr(const MyRGBColor cr);
//	
//	void
//	set_cr(const float r, const float g, const float b);
	
	void
	set_eta_in(const float eta);
	
	void
	set_eta_out(const float eta);
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr,  Vector3D& wr, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr,  Vector3D& wr, const Vector3D& wo, float& pdf) const;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;
	
	float
	fresnel(const ShadeRec& sr) const;
	
private:
	
//	float kr;
//	MyRGBColor cr;
	float eta_in;
	float eta_out;
};

inline void
FresnelReflector::set_eta_in(const float eta) {
	eta_in = eta;
}

inline void
FresnelReflector::set_eta_out(const float eta) {
	eta_out = eta;
}

//inline void
//FresnelReflector::set_kr(const float the_kr) {
//	kr = the_kr;
//}
//
//inline void
//FresnelReflector::set_cr(const MyRGBColor the_cr) {
//	cr = the_cr;
//}
//
//inline void
//FresnelReflector::set_cr(const float r, const float g, const float b) {
//	cr.r = r; cr.g = g; cr.b = b;
//}

#endif