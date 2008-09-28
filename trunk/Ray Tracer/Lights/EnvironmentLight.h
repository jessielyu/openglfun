#ifndef __ENVIRONMENT_LIGHT__
#define __ENVIRONMENT_LIGHT__

/*
 *  EnvironmentLight.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Light.h"
#include "Material.h"
#include "Sampler.h"

class EnvironmentLight: public Light {
public:
	
	EnvironmentLight(void);
	
	EnvironmentLight(const EnvironmentLight& al);
	
	EnvironmentLight&
	operator= (const EnvironmentLight& al);
	
	~EnvironmentLight(void);
	
	EnvironmentLight*
	clone(void) const;
	
	void
	set_sampler(Sampler* sampler);
	
	void
	set_material(Material* material);
	
	virtual Vector3D
	get_direction(ShadeRec& sr);
	
	virtual bool
	in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
	virtual float
	pdf(const ShadeRec& sr) const;
	
	
	
private:
	
	Sampler* sampler_ptr;
	Material* material_ptr;			// emissive material
	Vector3D u, v, w;				
	Vector3D wi;					// unit vector from hit point to sample point
	
};

#endif