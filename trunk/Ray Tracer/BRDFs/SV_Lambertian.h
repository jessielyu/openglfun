#ifndef __SV_LAMBERTIAN__
#define __SV_LAMBERTIAN__

/*
 *  SV_Lambertian.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "BRDF.h"
#include "Sampler.h"
#include "Texture.h"

class SV_Lambertian: public BRDF {
public:
	SV_Lambertian(void);
	
	SV_Lambertian(const SV_Lambertian& lamb);
	
	SV_Lambertian&
	operator= (const SV_Lambertian& rhs);
	
	~SV_Lambertian(void);
	
	virtual BRDF*
	clone(void) const;
	
	void
	set_kd(const float the_kd);
	
	void
	set_cd(Texture* texture);
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo, float& pdf) const;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;
	
	
private:
	
	float kd;		// diffuse coefficient
	Texture* cd;	// diffuse color
};

inline void
SV_Lambertian::set_kd(const float the_kd) {
	kd = the_kd;
}

inline void
SV_Lambertian::set_cd(Texture* texture) {
	cd = texture;
}

#endif