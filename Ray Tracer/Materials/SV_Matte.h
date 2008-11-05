#ifndef __SV_MATTE__
#define __SV_MATTE__

/*
 *  SV_Matte.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Material.h"
#include "SV_Lambertian.h"

class SV_Matte: public Material {
public:
	
	SV_Matte(void);
	
	SV_Matte(const SV_Matte& m);
	
	SV_Matte&
	operator= (const SV_Matte& m);
	
	~SV_Matte(void);
	
	virtual Material*
	clone(void) const;
	
	void 
	set_ka(const float k);
	
	void
	set_kd(const float k);
	
	void
	set_cd(Texture* texture);
	
	void
	set_sampler(Sampler* sampl_ptr);
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
	virtual MyRGBColor
	area_light_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	path_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	global_shade(ShadeRec& sr);
	
private:
	
	SV_Lambertian*	ambient_ptr;
	SV_Lambertian* diffuse_ptr;
};

inline void
SV_Matte::set_cd(Texture* c) {
	ambient_ptr->set_cd(c);
	diffuse_ptr->set_cd(c);
}

#endif