
#ifndef __PERFECT_TRANSMITTER__
#define __PERFECT_TRANSMITTER__

/*
 *  PerfectTransmitter.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/25/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

// this implements perfect specular transmission for transparent materials

#include "BTDF.h"

class PerfectTransmitter: public BTDF {
public:
	
	PerfectTransmitter(void);
	
	PerfectTransmitter(const PerfectTransmitter& pt);
	
	virtual PerfectTransmitter*
	clone(void) const;
	
	~PerfectTransmitter(void);
	
	PerfectTransmitter&							
	operator= (const PerfectTransmitter& rhs);
	
	void
	set_kt(const float k);
	
	void
	set_ior(const float eta);
	
	bool													
	tir(const ShadeRec& sr) const;
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;
	
private:
	
	float	kt;			// transmission coefficient
	float	ior;		// index of refraction
};


// -------------------------------------------------------------- set_kt

inline void
PerfectTransmitter::set_kt(const float k) {
	kt = k;
}

// -------------------------------------------------------------- set_ior

inline void
PerfectTransmitter::set_ior(const float eta) {
	ior = eta;
}

#endif
