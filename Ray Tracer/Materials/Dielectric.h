#ifndef __DIELECTRIC__
#define __DIELECTRIC__

/*
 *  Dielectric.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Phong.h"
#include "FresnelReflector.h"
#include "FresnelTransmitter.h"

class Dielectric: public Phong {
public:
	
	Dielectric(void);
	
	Dielectric(const Dielectric& trans);
	
	virtual Dielectric*
	clone(void) const;
	
	Dielectric&
	operator= (const Dielectric& trans);
	
	~Dielectric(void);
	
	void
	set_ks(const float k);
	
	void
	set_exp(const float exponent);
	
//	void
//	set_ior(const float i);
//	
//	void
//	set_kr(const float k);
//	
//	void 
//	set_kt(const float k);
//	
//	void
//	set_cr(const MyRGBColor cr);
//	
//	void
//	set_cr(const float r, const float g, const float b);
	
	void
	set_eta_in(const float eta);
	
	void
	set_eta_out(const float eta);
	
	void 
	set_cf_in(const MyRGBColor& c);
	
	void 
	set_cf_out(const MyRGBColor& c);
	
	void 
	set_cf_in(const float r, const float b, const float g);
	
	void 
	set_cf_out(const float r, const float b, const float g);
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
	virtual MyRGBColor
	area_light_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	path_shade(ShadeRec& sr);
	
private:
	
	MyRGBColor cf_in;	// interior filter color
	MyRGBColor cf_out;	// exterior filter color
	
	FresnelReflector* fresnel_brdf;
	FresnelTransmitter* fresnel_btdf;
};

inline void
Dielectric::set_ks(const float k) {
	Phong::set_ks(k);
	//reflective_brdf->set_kr(k);
}

inline void
Dielectric::set_exp(const float exponent) {
	Phong::set_exp_s(exponent);
	//reflective_brdf->set_exp(exponent);
}

inline void
Dielectric::set_eta_in(const float eta) {
	fresnel_brdf->set_eta_in(eta);
	fresnel_btdf->set_eta_in(eta);
}
	

inline void
Dielectric::set_eta_out(const float eta) {
	fresnel_brdf->set_eta_out(eta);
	fresnel_btdf->set_eta_out(eta);
}

inline void 
Dielectric::set_cf_in(const MyRGBColor& c) {
	cf_in = c;
}

inline void 
Dielectric::set_cf_out(const MyRGBColor& c) {
	cf_out = c;
}

inline void 
Dielectric::set_cf_in(const float r, const float b, const float g) {
	cf_in = MyRGBColor(r, g, b);
}

inline void 
Dielectric::set_cf_out(const float r, const float b, const float g) {
	cf_out = MyRGBColor(r, b, g);
}

//inline void
//Dielectric::set_ior(const float i) {
//	specular_btdf->set_ior(i);
//}
//
//inline void
//Dielectric::set_kr(const float k) {
//	reflective_brdf->set_kr(k);
//}
//
//inline void 
//Dielectric::set_kt(const float k) {
//	specular_btdf->set_kt(k);
//}

//inline void
//Dielectric::set_cr(const MyRGBColor cr) {
//	//Phong::set_cr(cr);
//	fresnel_brdf->set_cr(cr);
//}

//inline void
//Dielectric::set_cr(const float r, const float g, const float b) {
//	//Phong::set_cr(r,g,b);
//	fresnel_brdf->set_cr(r,g,b);
//}

#endif