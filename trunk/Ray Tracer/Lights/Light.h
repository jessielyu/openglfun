#ifndef __LIGHT__
#define __LIGHT__

/*
 *  Light.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Vector3D.h"
#include "MyRGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"

class Light {
public:
	
	Light(void);
	
	Light(const Light& l);
	
	Light&
	operator= (const Light& rhs); 
	
	virtual Light*
	clone(void) const = 0;
	
	virtual
	~Light(void);
	
	virtual Vector3D
	get_direction(ShadeRec& sr) = 0;
	
	virtual float
	G(const ShadeRec& sr) const;
	
	virtual float
	pdf(const ShadeRec& sr) const;
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
	bool
	casts_shadows();
	
	virtual bool
	in_shadow(const Ray& ray, const ShadeRec& sr) const = 0;
	
protected:
	
	bool shadows;
	
};

inline bool
Light::casts_shadows() {
	return shadows;
}

inline float
Light::G(const ShadeRec& sr) const {
	return 1.0;
}

inline float
Light::pdf(const ShadeRec& sr) const{
	return 1.0;
}

#endif