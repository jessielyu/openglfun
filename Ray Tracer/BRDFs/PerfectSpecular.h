#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__

/*
 *  PerfectSpecular.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "BRDF.h"

class PerfectSpecular: public BRDF {
public:
	PerfectSpecular(void);
	
	PerfectSpecular(const PerfectSpecular& lamb);
	
	PerfectSpecular&
	operator= (const PerfectSpecular& rhs);
	
	~PerfectSpecular(void);
	
	virtual BRDF*
	clone(void) const;
	
	void
	set_kr(const float the_kr);
	
	void
	set_cr(const MyRGBColor cr);
	
	void
	set_cr(const float r, const float g, const float b);
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo, float& pdf) const;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;
	
private:
	
	float kr;	// reflectance coefficient
	MyRGBColor cr;	// reflectance color
};

inline void
PerfectSpecular::set_kr(const float the_kr) {
	kr = the_kr;
}

inline void
PerfectSpecular::set_cr(const MyRGBColor the_cr) {
	cr = the_cr;
}

inline void
PerfectSpecular::set_cr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}

#endif