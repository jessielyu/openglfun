/*
 *  FresnelTransmitter.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "FresnelTransmitter.h"FresnelTransmitter

// ------------------------------------------------------------------- default constructor

FresnelTransmitter::FresnelTransmitter(void)
: 	BTDF(),
	eta_in(1.0),
	eta_out(1.0)
//kt(0.0), 
//ior(1.0)
{}


// ------------------------------------------------------------------- copy constructor

FresnelTransmitter::FresnelTransmitter(const FresnelTransmitter& pt)
: 	BTDF(pt),
	eta_in(pt.eta_in),
	eta_out(pt.eta_out)
//kt(pt.kt), 
//ior(pt.ior)
{}


// ------------------------------------------------------------------- clone

FresnelTransmitter* 
FresnelTransmitter::clone(void) const {
	return (new FresnelTransmitter(*this));
}


// ------------------------------------------------------------------- destructor

FresnelTransmitter::~FresnelTransmitter(void) {}



// ------------------------------------------------------------------- assignment operator

FresnelTransmitter&							
FresnelTransmitter::operator= (const FresnelTransmitter& rhs) {
	if (this == &rhs)
		return (*this);
	
//	kt = rhs.kt;
//	ior = rhs.ior;
	eta_in = rhs.eta_in;
	eta_out = rhs.eta_out;
	
	return (*this);
}


// ------------------------------------------------------------------- tir
// tests for total internal reflection

bool													
FresnelTransmitter::tir(const ShadeRec& sr) const {
	Vector3D wo(-sr.ray.d); 
	float cos_thetai = sr.normal * wo;  
	float eta;// = ior;
	
//	if (cos_thetai < 0.0) 
//		eta = 1.0 / eta; 
	
	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		//cos_thetai = -cos_thetai;
		//n = -n;  					// reverse direction of normal
		eta = eta_out / eta_in;
		//eta = 1.0 / eta; 			// invert ior 
	}
	else
		eta = eta_in / eta_out;
	
	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}	


// ------------------------------------------------------------------- f

MyRGBColor
FresnelTransmitter::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}


// ------------------------------------------------------------------- sample_f
// this computes the direction wt for perfect transmission
// and returns the transmission coefficient
// this is only called when there is no total internal reflection

MyRGBColor
FresnelTransmitter::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const {
	
	Normal n(sr.normal);
	float cos_thetai = n * wo;
	float eta;// = ior;	
	
	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		cos_thetai = -cos_thetai;
		n = -n;  					// reverse direction of normal
		eta = eta_out / eta_in;
		//eta = 1.0 / eta; 			// invert ior 
	}
	else
		eta = eta_in / eta_out;
	
	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;   
	
	//return (kt / (eta * eta) * white / fabs(sr.normal * wt));
	// fresnel(sr) returns kr, kt = 1 - kr per conservation of energy
	return ((1 - fresnel(sr)) / (eta * eta)  * white / fabs(sr.normal * wt));
}

MyRGBColor
FresnelTransmitter::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt, float& pdf) const {
	
	Normal n(sr.normal);
	float cos_thetai = n * wo;
	float eta;// = ior;	
	pdf = fabs(sr.normal * wt);
	
	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		cos_thetai = -cos_thetai;
		n = -n;  					// reverse direction of normal
		eta = eta_out / eta_in;
		//eta = 1.0 / eta; 			// invert ior 
	}
	else
		eta = eta_in / eta_out;
	
	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;   
	
	//return (kt / (eta * eta) * white / fabs(sr.normal * wt));
	// fresnel(sr) returns kr, kt = 1 - kr per conservation of energy
	return ((1 - fresnel(sr)) / (eta * eta)  * white);
}


// ------------------------------------------------------------------- rho

MyRGBColor
FresnelTransmitter::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}

float
FresnelTransmitter::fresnel(const ShadeRec& sr) const {
	Normal normal(sr.normal);
	float ndotd = -normal * sr.ray.d;
	float eta;
	
	if (ndotd < 0.0) { 
		normal = -normal;
		eta = eta_out / eta_in;
	}
	else
		eta = eta_in / eta_out;
	
	float cos_theta_i 		= -normal * sr.ray.d; 
	float temp 				= 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
	float cos_theta_t 		= sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
	float r_parallel 		= (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
	float r_perpendicular 	= (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);
	float kr 				= 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);
	
	return (kr);
}



