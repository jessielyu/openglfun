#ifndef __FAKE_SPHERICAL_LIGHT__
#define __FAKE_SPHERICAL_LIGHT__

/*
 *  FakeSphericalLight.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Light.h"
#include "Vector3D.h"

class FakeSphericalLight: public Light {
public:
	
	FakeSphericalLight(void);
	
	FakeSphericalLight(const FakeSphericalLight& pl);
	
	FakeSphericalLight&
	operator= (const FakeSphericalLight& pl);
	
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
	
	void
	set_location(const Point3D& p);
	
	virtual Vector3D
	get_direction(ShadeRec& sr);
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
	virtual bool
	in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
	void
	set_radius(const float r);
	
private:
	
	float r;		// radius
	float ls;
	MyRGBColor color;
	Point3D location;
};

// ------------------------------------------------------------------------------- scale_radiance

inline void
FakeSphericalLight::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
FakeSphericalLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
FakeSphericalLight::set_color(const MyRGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
FakeSphericalLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline void
FakeSphericalLight::set_location(const float x, const float y, const float z) {
	location.x = x; location.y = y; location.z = z;
}

inline void
FakeSphericalLight::set_location(const Point3D& p) {
	location = p;
}

inline void
FakeSphericalLight::set_radius(const float radius) {
	r = radius;
}

#endif