#ifndef __GLOSSY_REFLECTOR__
#define __GLOSSY_REFLECTOR__

/*
 *  GlossyReflector.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/23/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Phong.h"
#include "GlossySpecular.h"

class GlossyReflector: public Phong {	
public:
	
	GlossyReflector(void);										
	
	GlossyReflector(const GlossyReflector& rm);						
	
	GlossyReflector& 
	operator= (const GlossyReflector& rhs);						
	
	virtual GlossyReflector*										
	clone(void) const;				
	
	~GlossyReflector(void);		
	
	void
	set_samples(const int num_samples, const float exp);
	
	void
	set_kr(const float k);
	
	void													
	set_cr(const MyRGBColor& c);
	
	void
	set_cr(const float r, const float g, const float b);
	
	void
	set_cr(const float c);
	
	void
	set_exponent(const float exp);
	
	virtual MyRGBColor										
	shade(ShadeRec& s);
	
	virtual MyRGBColor
	area_light_shade(ShadeRec& sr);

private:
	
	GlossySpecular* glossy_specular_brdf;		
};

inline void
GlossyReflector::set_samples(const int num_samples, const float exp) {
	glossy_specular_brdf->set_samples(num_samples, exp);
}


// ---------------------------------------------------------------- set_kr

inline void
GlossyReflector::set_kr(const float k) {
	glossy_specular_brdf->set_ks(k);
}


// ---------------------------------------------------------------- set_cr

inline void
GlossyReflector::set_cr(const MyRGBColor& c) {
	glossy_specular_brdf->set_cs(c);
	
}


// ---------------------------------------------------------------- set_cr

inline void
GlossyReflector::set_cr(const float r, const float g, const float b) {
	glossy_specular_brdf->set_cs(r, g, b);
}


// ---------------------------------------------------------------- set_cr

inline void
GlossyReflector::set_cr(const float c) {
	glossy_specular_brdf->set_cs(c);
}

inline void
GlossyReflector::set_exponent(const float exp) {
	glossy_specular_brdf->set_exp(exp);
}

#endif
