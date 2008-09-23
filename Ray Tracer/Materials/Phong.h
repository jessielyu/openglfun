#ifndef __PHONG__
#define __PHONG__

/*
 *  Phong.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong: public Material {
public:
	
	Phong(void);
	
	Phong(const Phong&);
	
	Phong&
	operator= (const Phong&);
	
	~Phong(void);
	
	virtual Material*
	clone(void) const;
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
	void
	set_ka(const float ka);
	
	void
	set_kd(const float kd);
	
	void
	set_ks(const float ks);
	
	void
	set_ca(const float r, const float g, const float b);
	
	void
	set_cd(const float r, const float g, const float b);
	
	void
	set_cs(const float r, const float g, const float b);
	
	void
	set_exp_s(const float exp_s);
	
	void 
	set_k(const float k);
	
	void
	set_c(const float r, const float g, const float b);
	
	void
	set_c(const MyRGBColor& c);
	
private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};

#endif