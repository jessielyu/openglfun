#ifndef __GLOSSY_SPECULAR__
#define __GLOSSY_SPECULAR__

/*
 *  GlossySpecular.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "BRDF.h"

class GlossySpecular: public BRDF {
public:
	GlossySpecular(void);
	
	GlossySpecular(const GlossySpecular& lamb);
	
	GlossySpecular&
	operator= (const GlossySpecular& rhs);
	
	~GlossySpecular(void);
	
	virtual BRDF*
	clone(void) const;
	
	void
	set_ks(const float the_ks);
	
	void
	set_exp(const float the_exp);
	
	void
	set_cs(const MyRGBColor cd);

	void
	set_cs(const float r, const float g, const float b);
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wi, Vector3D& wo) const;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;
	
private:
	
	float ks;
	MyRGBColor cs;		// specular color
	float exp;			// specular exponent
//	Sampler* sampler_ptr;
};

inline void
GlossySpecular::set_ks(const float the_ks) {
	ks = the_ks;
}

inline void
GlossySpecular::set_cs(const MyRGBColor the_cs) {
	cs = the_cs;
}

inline void
GlossySpecular::set_cs(const float r, const float g, const float b) {
	cs.r = r; cs.g = g, cs.b = b;
}

inline void
GlossySpecular::set_exp(const float the_exp) {
	exp = the_exp;
}

#endif