#ifndef __FRESNEL_TRANSMITTER__
#define __FRESNEL_TRANSMITTER__

/*
 *  FresnelTransmitter.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */



#include "BTDF.h"

class FresnelTransmitter: public BTDF {
public:
	
	FresnelTransmitter(void);
	
	FresnelTransmitter(const FresnelTransmitter& pt);
	
	virtual FresnelTransmitter*
	clone(void) const;
	
	~FresnelTransmitter(void);
	
	FresnelTransmitter&							
	operator= (const FresnelTransmitter& rhs);
	
//	void
//	set_kt(const float k);
//	
//	void
//	set_ior(const float eta);
	
	void
	set_eta_in(const float eta);
	
	void
	set_eta_out(const float eta);
	
	bool													
	tir(const ShadeRec& sr) const;
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt, float& pdf) const;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;
	
	float
	fresnel(const ShadeRec& sr) const;
	
	
	
private:
	
//	float	kt;			// transmission coefficient
//	float	ior;		// index of refraction
	
	float eta_in;		// index of refraction in
	float eta_out;		// index of refraction out
};

inline void
FresnelTransmitter::set_eta_in(const float eta) {
	eta_in = eta;
}

inline void
FresnelTransmitter::set_eta_out(const float eta) {
	eta_out = eta;
}

//
//// -------------------------------------------------------------- set_kt
//
//inline void
//FresnelTransmitter::set_kt(const float k) {
//	kt = k;
//}
//
//// -------------------------------------------------------------- set_ior
//
//inline void
//FresnelTransmitter::set_ior(const float eta) {
//	ior = eta;
//}

#endif
