#ifndef __TRANSPARENT__
#define __TRANSPARENT__

/*
 *  Transparent.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/25/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"

class Transparent: public Phong {
public:
	
	Transparent(void);
	
	Transparent(const Transparent& trans);
	
	virtual Transparent*
	clone(void) const;
	
	Transparent&
	operator= (const Transparent& trans);
	
	~Transparent(void);
	
	void
	set_ks(const float k);
	
	void
	set_exp(const float exponent);
	
	void
	set_ior(const float i);
	
	void
	set_kr(const float k);
	
	void 
	set_kt(const float k);
	
	void
	set_cr(const MyRGBColor cr);
	
	void
	set_cr(const float r, const float g, const float b);
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
private:
	
	PerfectSpecular* reflective_brdf;
	PerfectTransmitter* specular_btdf;
};

inline void
Transparent::set_ks(const float k) {
	Phong::set_ks(k);
	//reflective_brdf->set_kr(k);
}

inline void
Transparent::set_exp(const float exponent) {
	Phong::set_exp_s(exponent);
	//reflective_brdf->set_exp(exponent);
}

inline void
Transparent::set_ior(const float i) {
	specular_btdf->set_ior(i);
}

inline void
Transparent::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}

inline void 
Transparent::set_kt(const float k) {
	specular_btdf->set_kt(k);
}

inline void
Transparent::set_cr(const MyRGBColor cr) {
	//Phong::set_cr(cr);
	reflective_brdf->set_cr(cr);
}

inline void
Transparent::set_cr(const float r, const float g, const float b) {
	//Phong::set_cr(r,g,b);
	reflective_brdf->set_cr(r,g,b);
}

#endif