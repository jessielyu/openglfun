#ifndef __AMBIENT__
#define __AMBIENT__

/*
 *  Ambient.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Light.h"

class Ambient: public Light {
public:
	
	Ambient(void);
	
	Ambient(const Ambient& amb);
	
	virtual Light*
	clone(void) const;
	
	Ambient&
	operator= (const Ambient& rhs);
	
	~Ambient(void);
	
	void
	scale_radiance(const float b);
	
	void
	set_color(const float c);
	
	void
	set_color(const MyRGBColor& c);
	
	void
	set_color(const float r, const float g, const float b); 
	
	virtual Vector3D
	get_direction(ShadeRec& sr);
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
	virtual bool
	in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
private:
	
	float ls;
	MyRGBColor color;
	
};

// ------------------------------------------------------------------------------- scale_radiance

inline void
Ambient::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const MyRGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline bool
Ambient::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	return false;
}

#endif