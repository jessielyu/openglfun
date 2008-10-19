/*
 *  ConcavePartCylinder.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "ConcavePartCylinder.h"

ConcavePartCylinder::ConcavePartCylinder(void) 
:	ConvexPartCylinder()
{}

ConcavePartCylinder::ConcavePartCylinder(const double bottom, const double top, const double r, 
									   const double azimuth_min, // degrees
									   const double azimuth_max) // degrees)
:	ConvexPartCylinder(bottom, top, r, azimuth_min, azimuth_max)
{}

ConcavePartCylinder::ConcavePartCylinder(const ConcavePartCylinder& c) 
:	ConvexPartCylinder(c)
{}

ConcavePartCylinder*
ConcavePartCylinder::clone(void) const {
	return (new ConcavePartCylinder(*this));
}

ConcavePartCylinder&
ConcavePartCylinder::operator= (const ConcavePartCylinder& c) {
	if (this == &c)
		return (*this);
	
	ConvexPartCylinder::operator= (c);
	
	return (*this);
}

bool 															 
ConcavePartCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;
	
	double a = dx * dx + dz * dz;  	
	double b = 2.0 * (ox * dx + oz * dz);					
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;
	
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {
				
				Vector3D hit = ray.o + t * ray.d;
				
				double phi = atan2(hit.x, hit.z);
				if (phi < 0.0)
					phi += TWO_PI;
				
				if (phi >= phi_min && phi <= phi_max) {
					
					tmin = t;
					sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
					
					// test for hitting from outside
					
					if (ray.d * sr.normal > 0.0)
						sr.normal = -sr.normal;
					
					sr.local_hit_point = ray.o + tmin * ray.d;
					
					return (true);
				}
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {
				
				Vector3D hit = ray.o + t * ray.d;
				
				double phi = atan2(hit.x, hit.z);
				if (phi < 0.0)
					phi += TWO_PI;
				
				if (phi >= phi_min && phi <= phi_max) {
					
					tmin = t;
					sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
					
					// test for hitting inside surface
					
					if (ray.d * sr.normal > 0.0)
						sr.normal = -sr.normal;
					
					sr.local_hit_point = ray.o + tmin * ray.d;
					
					return (true);
				}
			}
		} 
	}
	
	return (false);			
}