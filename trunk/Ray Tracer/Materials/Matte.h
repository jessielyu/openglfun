#ifndef __MATTE__
#define __MATTE__

/*
 *  Matte.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Material.h"
#include "Lambertian.h"

class Matte: public Material {
public:
	
	Matte(void);
	
	Matte(const Matte& m);
	
	Matte&
	operator= (const Matte& m);
	
	~Matte(void);
	
	virtual Material*
	clone(void) const;
	
	void 
	set_ka(const float k);
	
	void
	set_kd(const float k);
	
	void
	set_cd(const MyRGBColor& c);
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
	virtual MyRGBColor
	area_light_shade(ShadeRec& sr);
	
private:
	
	Lambertian*	ambient_ptr;
	Lambertian* diffuse_ptr;
};

#endif