#ifndef __EMISSIVE__
#define __EMISSIVE__

/*
 *  Emissive.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Material.h"
#include "MyRGBColor.h"

class Emissive: public Material {
private:
	
	float ls;
	MyRGBColor ce;
	
public:
	
	Emissive(void);
	
	Emissive(const Emissive& em);
	
	Emissive&
	operator=(const Emissive& em);
	
	~Emissive(void);
	
	virtual Material*
	clone(void) const;
	
	void
	scale_radiance(const float b);
	
	void
	set_ce(const float r, const float g, const float b);
	
	void
	set_ce(const MyRGBColor& c);
	
	virtual MyRGBColor
	get_Le(ShadeRec& sr) const;
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
	virtual MyRGBColor
	area_light_shade(ShadeRec& sr);
};

inline void
Emissive::scale_radiance(const float b) {
	ls = b;
}

inline void
Emissive::set_ce(const float r, const float g, const float b) {
	ce.r = r; ce.g = g; ce.b = b;
}

inline void
Emissive::set_ce(const MyRGBColor& c) {
	ce.r = c.r; ce.g = c.g; ce.b = c.b;
}

#endif