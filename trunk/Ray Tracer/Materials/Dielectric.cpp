/*
 *  Dielectric.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Dielectric.h"
#include "World.h"

Dielectric::Dielectric(void)
:	fresnel_brdf(new FresnelReflector),
	fresnel_btdf(new FresnelTransmitter),
	cf_in(1.0),
	cf_out(1.0) {}

Dielectric::Dielectric(const Dielectric& trans)
:	fresnel_brdf(trans.fresnel_brdf),
	fresnel_btdf(trans.fresnel_btdf), 
	cf_in(trans.cf_in),
	cf_out(trans.cf_out) {}

Dielectric*
Dielectric::clone(void) const {
	return (new Dielectric(*this));
}

Dielectric&
Dielectric::operator= (const Dielectric& trans) {
	if (this == &trans)
		return (*this);
	
	if (fresnel_brdf)
	{
		delete fresnel_brdf;
		fresnel_brdf = NULL;
	}
	
	if (fresnel_btdf) {
		delete fresnel_btdf;
		fresnel_btdf = NULL;
	}
	
	if (trans.fresnel_brdf)
		fresnel_brdf = trans.fresnel_brdf;
	
	if (trans.fresnel_btdf)
		fresnel_btdf = trans.fresnel_btdf;
	
	cf_in = trans.cf_in;
	cf_out = trans.cf_out;
	
	return (*this);
}

MyRGBColor
Dielectric::shade(ShadeRec& sr) {
			
	MyRGBColor L(Phong::shade(sr));
	
	Vector3D 	wi;
	Vector3D 	wo(-sr.ray.d);
	MyRGBColor 	fr = fresnel_brdf->sample_f(sr, wi, wo);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi); 
	double 		t;
	MyRGBColor 	Lr, Lt;
	float 		ndotwi =  sr.normal * wi;
	
	if(fresnel_btdf->tir(sr)) {								// total internal reflection
		if (ndotwi < 0.0) {  	
			// reflected ray is inside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			L += cf_in.powc(t) * Lr;   						// inside filter color
		}
		else {				
			// reflected ray is outside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1  
			L += cf_out.powc(t) * Lr;   					// outside filter color
		}
	}
	else { 													// no total internal reflection
		Vector3D wt;
		MyRGBColor ft = fresnel_btdf->sample_f(sr, wo, wt);  	// computes wt
		Ray transmitted_ray(sr.hit_point, wt);
		float ndotwt = sr.normal * wt;
		
		if (ndotwi < 0.0) {
			// reflected ray is inside
			
			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf_in.powc(t) * Lr;     					// inside filter color
			
			// transmitted ray is outside
			
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf_out.powc(t) * Lt;   					// outside filter color
		}
		else {				
			// reflected ray is outside
			
			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi); 
			L += cf_out.powc(t) * Lr;						// outside filter color
			
			// transmitted ray is inside
			
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf_in.powc(t) * Lt; 						// inside filter color
		}		
	}	
	
	return (L);
	
}


// THIS METHOD NEEDS WORK

MyRGBColor
Dielectric::area_light_shade(ShadeRec& sr) {
	
	return shade(sr);
	
	MyRGBColor L(Phong::area_light_shade(sr));
	
	Vector3D 	wi;
	Vector3D 	wo(-sr.ray.d);
	MyRGBColor 	fr = fresnel_brdf->sample_f(sr, wi, wo);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi); 
	double 		t;
	MyRGBColor 	Lr, Lt;
	float 		ndotwi =  sr.normal * wi;
	
	int num_lights = sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		
		wi - sr.w.lights[j]->get_direction(sr);
		ndotwi = sr.normal * wi;
		
		if(fresnel_btdf->tir(sr)) {								// total internal reflection
			if (ndotwi < 0.0) {  	
				// reflected ray is inside
				
				Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
				// GUESS
				L += (cf_in.powc(t) * Lr) * sr.w.lights[j]->G(sr) * fabs(ndotwi) / sr.w.lights[j]->pdf(sr);   						// inside filter color
			}
			else {				
				// reflected ray is outside
				
				Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1  
				L += (cf_out.powc(t) * Lr)  * sr.w.lights[j]->G(sr) * fabs(ndotwi) / sr.w.lights[j]->pdf(sr);   					// outside filter color
			}
		}
		else { 													// no total internal reflection
			Vector3D wt;
			MyRGBColor ft = fresnel_btdf->sample_f(sr, wo, wt);  	// computes wt
			Ray transmitted_ray(sr.hit_point, wt);
			float ndotwt = sr.normal * wt;
			
			if (ndotwi < 0.0) {
				// reflected ray is inside
				
				Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
				L += (cf_in.powc(t) * Lr) * sr.w.lights[j]->G(sr) * fabs(ndotwi) / sr.w.lights[j]->pdf(sr);     					// inside filter color
				
				// transmitted ray is outside
				
				Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
				L += (cf_out.powc(t) * Lt) * sr.w.lights[j]->G(sr) * fabs(ndotwi) / sr.w.lights[j]->pdf(sr);   					// outside filter color
			}
			else {				
				// reflected ray is outside
				
				Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi); 
				L += (cf_out.powc(t) * Lr) * sr.w.lights[j]->G(sr) * fabs(ndotwi) / sr.w.lights[j]->pdf(sr);						// outside filter color
				
				// transmitted ray is inside
				
				Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
				L += (cf_in.powc(t) * Lt)  * sr.w.lights[j]->G(sr) * fabs(ndotwi) / sr.w.lights[j]->pdf(sr); 						// inside filter color
			}		
		}
	}
	
	return (L);
	
}


MyRGBColor
Dielectric::path_shade(ShadeRec& sr) {
	
	MyRGBColor L(Phong::shade(sr));
	
	Vector3D 	wi;
	Vector3D 	wo(-sr.ray.d);
	float reflective_pdf;
	MyRGBColor 	fr = fresnel_brdf->sample_f(sr, wi, wo, reflective_pdf);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi); 
	double 		t;
	MyRGBColor 	Lr, Lt;
	float 		ndotwi =  sr.normal * wi;
	
	if(fresnel_btdf->tir(sr)) {								// total internal reflection
		if (ndotwi < 0.0) {  	
			// reflected ray is inside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) / reflective_pdf;
			L += cf_in.powc(t) * Lr;   						// inside filter color
		}
		else {				
			// reflected ray is outside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) / reflective_pdf;   // kr = 1  
			L += cf_out.powc(t) * Lr;   					// outside filter color
		}
	}
	else { 													// no total internal reflection
		Vector3D wt;
		float transmissive_pdf;
		MyRGBColor ft = fresnel_btdf->sample_f(sr, wo, wt, transmissive_pdf);  	// computes wt
		Ray transmitted_ray(sr.hit_point, wt);
		float ndotwt = sr.normal * wt;
		
		if (ndotwi < 0.0) {
			// reflected ray is inside
			
			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi) / reflective_pdf;
			L += cf_in.powc(t) * Lr;     					// inside filter color
			
			// transmitted ray is outside
			
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt) / transmissive_pdf; 
			L += cf_out.powc(t) * Lt;   					// outside filter color
		}
		else {				
			// reflected ray is outside
			
			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi) / reflective_pdf; 
			L += cf_out.powc(t) * Lr;						// outside filter color
			
			// transmitted ray is inside
			
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt) / transmissive_pdf; 
			L += cf_in.powc(t) * Lt; 						// inside filter color
		}		
	}	
	
	return (L);
	
}




Dielectric::~Dielectric(void) {
	if (fresnel_brdf)
	{
		delete fresnel_brdf;
		fresnel_brdf = NULL;
	}
	
	if (fresnel_btdf) {
		delete fresnel_btdf;
		fresnel_btdf = NULL;
	}
}