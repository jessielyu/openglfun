#ifndef __BTDF__
#define __BTDF__

/*
 *  BTDF.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/25/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "MyRGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"
#include "Sampler.h"

class BTDF {
public:
	
	BTDF(void);
	
	BTDF(const BTDF& brdf);
	
	virtual BTDF*
	clone(void)const = 0;
	
	BTDF&
	operator= (const BTDF& rhs);
	
	virtual
	~BTDF(void);
	
//	void
//	set_sampler(Sampler* sPtr);
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const = 0;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const = 0;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const = 0;
	
//protected:
//	
//	Sampler* sampler_ptr;
};



#endif