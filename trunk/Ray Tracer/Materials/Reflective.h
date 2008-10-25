#ifndef __REFLECTIVE__
#define __REFLECTIVE__

/*
 *  Reflective.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Phong.h"
#include "PerfectSpecular.h"

class Reflective: public Phong {	
public:
	
	Reflective(void);										
	
	Reflective(const Reflective& rm);						
	
	Reflective& 
	operator= (const Reflective& rhs);						
	
	virtual Reflective*										
	clone(void) const;				
	
	~Reflective(void);										
	
	void
	set_kr(const float k);
	
	void													
	set_cr(const MyRGBColor& c);
	
	void
	set_cr(const float r, const float g, const float b);
	
	void
	set_cr(const float c);
	
	virtual MyRGBColor										
	shade(ShadeRec& s);
	
	virtual MyRGBColor										
	path_shade(ShadeRec& s);
	
	void
	set_sampler(Sampler* sampl_ptr);
	
	virtual MyRGBColor
	global_shade(ShadeRec& sr);
	
private:
	
	PerfectSpecular* reflective_brdf;		
};


// ---------------------------------------------------------------- set_kr

inline void
Reflective::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const MyRGBColor& c) {
	reflective_brdf->set_cr(c);
	
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const float r, const float g, const float b) {
	reflective_brdf->set_cr(r, g, b);
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const float c) {
	reflective_brdf->set_cr(c);
}

#endif
