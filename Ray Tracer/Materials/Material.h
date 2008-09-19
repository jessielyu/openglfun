#ifndef __MATERIAL__
#define __MATERIAL__

/*
 *  Material.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Material.h"
#include "ShadeRec.h"
#include "MyRGBColor.h"

class Material {
public:
	Material(void);
	
	Material(const Material& m);
	
	Material&
	operator= (const Material& m);
	
	virtual Material*
	clone(void) const = 0;
	
	~Material(void);
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
	virtual MyRGBColor
	area_light_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	path_shade(ShadeRec& sr);
};

#endif