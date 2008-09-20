#ifndef __POINT_LIGHT__
#define __POINT_LIGHT__

/*
 *  PointLight.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Light.h"
#include "Vector3D.h"

class PointLight: public Light {
public:
	
	PointLight(void);
	
	PointLight(const PointLight& pl);
	
	PointLight&
	operator= (const PointLight& pl);
	
	virtual Light*
	clone(void) const;
	
	void
	scale_radiance(const float b);
	
	void
	set_color(const float c);
	
	void
	set_color(const MyRGBColor& c);
	
	void
	set_color(const float r, const float g, const float b); 
	
	void
	set_location(const float x, const float y, const float z);
	
	virtual Vector3D
	get_direction(ShadeRec& sr);
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
private:
	
	float ls;
	MyRGBColor color;
	Vector3D location;
};

// ------------------------------------------------------------------------------- scale_radiance

inline void
PointLight::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const MyRGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline void
PointLight::set_location(const float x, const float y, const float z) {
	location.x = x; location.y = y; location.z = z;
}

#endif