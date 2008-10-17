/*
 *  ConvexPartSphere.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "ConvexPartSphere.h"

ConvexPartSphere::ConvexPartSphere(void) 
:	GeometricObject(),
	center(0.0),
	radius(1.0),
	phi_min(0.0),
	phi_max(TWO_PI),
	theta_min(0.0),
	theta_max(PI),
	cos_theta_min(1.0),
	cos_theta_max(-1.0)
{}

ConvexPartSphere::ConvexPartSphere(const Point3D c,
				 const double r,
				 const double azimuth_min, // degrees
				 const double azimuth_max, // degrees
				 const double polar_min,   // degrees from top
				 const double polar_max)  // degrees from top
:	GeometricObject(),
	center(c),
	radius(r),
	phi_min(azimuth_min * PI_ON_180),
	phi_max(azimuth_max * PI_ON_180),
	theta_min(polar_min * PI_ON_180),
	theta_max(polar_max * PI_ON_180),
	cos_theta_min(cos(theta_min)),
	cos_theta_max(cos(theta_max))
{}

ConvexPartSphere::ConvexPartSphere (const Point3D 	c, 
									const double 	r)
: 	GeometricObject(),
	center(c),
	radius(r),
	phi_min(0.0),
	phi_max(TWO_PI),
	theta_min(0.0),
	theta_max(PI),
	cos_theta_min(1.0),
	cos_theta_max(-1.0)
{}

ConvexPartSphere*
ConvexPartSphere::clone(void) const {
	return (new ConvexPartSphere(*this));
}

ConvexPartSphere::ConvexPartSphere (const ConvexPartSphere& ps)
: 	GeometricObject(ps),
	center(ps.center),
	radius(ps.radius),
	phi_min(ps.phi_min),
	phi_max(ps.phi_max),
	theta_min(ps.theta_min),
	theta_max(ps.theta_max),
	cos_theta_min(ps.cos_theta_min),
	cos_theta_max(ps.cos_theta_max) 
{}

ConvexPartSphere::~ConvexPartSphere(void) {}

ConvexPartSphere& 
ConvexPartSphere::operator= (const ConvexPartSphere& rhs)		
{
	if (this == &rhs)
		return (*this);
	
	GeometricObject::operator=(rhs);
	
	center 			= rhs.center;
	radius			= rhs.radius;
	phi_min			= rhs.phi_min;
	phi_max			= rhs.phi_max;
	theta_min		= rhs.theta_min;
	theta_max		= rhs.theta_max;
	cos_theta_min	= rhs.cos_theta_min;
	cos_theta_max	= rhs.cos_theta_max; 
	
	return (*this);
}

//bool
//ConvexPartSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
//	double t;
//	Vector3D temp = ray.o - center;
//	double a = ray.d * ray.d;
//	double b = 2.0 * temp * ray.d;
//	double c = temp * temp - radius * radius;
//	double disc = b * b - 4.0 * a * c;
//	
//	if (disc < 0.0)
//		return false;
//	else {
//		double e = sqrt(disc);
//		double denom = 2.0 * a;
//		t = (-b - e / denom);	// small root
//		
//		if (t > kEpsilon) {
//			Vector3D hit = ray.o + t * ray.d - center;
//			
//			float phi = atan2(hit.x, hit.z);
//			if (phi < 0.0)
//				phi += TWO_PI;
//			
//			if (hit.y <= radius * cos_theta_min && hit.y >= radius * cos_theta_max && phi >= phi_min && phi <= phi_max) {
//				tmin = t;
//				sr.normal = (temp + t * ray.d) / radius;	// points out
//				
//				if (-ray.d * sr.normal < 0.0)	// reverse normal if it hit the inside
//					sr.normal = -sr.normal;
//				sr.local_hit_point = ray.o + tmin * ray.d;
//				return (true);
//			}
//		}
//		
//		t = (-b + e / denom); // large root
//		
//		if (t > kEpsilon) {
//			Vector3D hit = ray.o + t * ray.d - center;
//			
//			float phi = atan2(hit.x, hit.z);
//			if (phi < 0.0)
//				phi += TWO_PI;
//			
//			if (hit.y <= radius * cos_theta_min && hit.y >= radius * cos_theta_max && phi >= phi_min && phi <= phi_max) {
//				tmin = t;
//				sr.normal = (temp + t * ray.d) / radius;	// points out
//				
//				if (-ray.d * sr.normal < 0.0)	// reverse normal if it hit the inside
//					sr.normal = -sr.normal;
//				sr.local_hit_point = ray.o + tmin * ray.d;
//				return (true);
//			}
//		}
//	}
//	
//	return (false);
//}
//
//bool
//ConvexPartSphere::shadow_hit(const Ray& ray, float& tmin) const {
//	double t;
//	Vector3D temp = ray.o - center;
//	double a = ray.d * ray.d;
//	double b = 2.0 * temp * ray.d;
//	double c = temp * temp - radius * radius;
//	double disc = b * b - 4.0 * a * c;
//	
//	if (disc < 0.0)
//		return false;
//	else {
//		double e = sqrt(disc);
//		double denom = 2.0 * a;
//		t = (-b - e / denom);	// small root
//		
//		if (t > kEpsilon) {
//			Vector3D hit = ray.o + t * ray.d - center;
//			
//			float phi = atan2(hit.x, hit.z);
//			if (phi < 0.0)
//				phi += TWO_PI;
//			
//			if (hit.y <= radius * cos_theta_min && hit.y >= radius * cos_theta_max && phi >= phi_min && phi <= phi_max) {
//				tmin = t;
//				//sr.normal = (temp + t * ray.d) / r;	// points out
////				
////				if (-ray.d * sr.normal < 0.0)	// reverse normal if it hit the inside
////					sr.normal = -sr.normal;
////				sr.local_hit_point = ray.o + tmin * ray.d;
//				return (true);
//			}
//		}
//		
//		t = (-b + e / denom); // large root
//		
//		if (t > kEpsilon) {
//			Vector3D hit = ray.o + t * ray.d - center;
//			
//			float phi = atan2(hit.x, hit.z);
//			if (phi < 0.0)
//				phi += TWO_PI;
//			
//			if (hit.y <=radius * cos_theta_min && hit.y >= radius * cos_theta_max && phi >= phi_min && phi <= phi_max) {
//				tmin = t;
////				sr.normal = (temp + t * ray.d) / r;	// points out
////				
////				if (-ray.d * sr.normal < 0.0)	// reverse normal if it hit the inside
////					sr.normal = -sr.normal;
////				sr.local_hit_point = ray.o + tmin * ray.d;
//				return (true);
//			}
//		}
//	}
//	
//	return (false);
//}


bool 															 
ConvexPartSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3D  	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc 	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			Vector3D hit = ray.o + t * ray.d - center;
			
			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;
			
			if (hit.y <= radius * cos_theta_min && 	
				hit.y >= radius * cos_theta_max && 	
				phi >= phi_min && phi <= phi_max) {
				
				tmin = t;				
				
				sr.normal = (temp + t * ray.d) / radius;   // points outwards
				
				if (-ray.d * sr.normal < 0.0)	// reverse normal if it hit the inside
					sr.normal = -sr.normal;
				
				sr.local_hit_point = ray.o + tmin * ray.d;				
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			Vector3D hit = ray.o + t * ray.d - center;
			
			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;
			
			if (hit.y <= radius * cos_theta_min && 	
				hit.y >= radius * cos_theta_max && 	
				phi >= phi_min && phi <= phi_max) {
				
				tmin = t;				
				sr.normal = (temp + t * ray.d) / radius;   // points outwards
				
				if (-ray.d * sr.normal < 0.0)	// reverse normal if it hit the inside
					sr.normal = -sr.normal;
				
				sr.local_hit_point = ray.o + tmin * ray.d;				
				return (true);
			}
		} 
	}
	
	return (false);
}



bool 															 
ConvexPartSphere::shadow_hit(const Ray& ray, float& tmin) const {
	double 		t;
	Vector3D  	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc 	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			Vector3D hit = ray.o + t * ray.d - center;
			
			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;
			
			if (hit.y <= radius * cos_theta_min && 	
				hit.y >= radius * cos_theta_max && 	
				phi >= phi_min && phi <= phi_max) {
				
				tmin = t;				
//				sr.normal = (temp + t * ray.d) / radius;   // points outwards
//				sr.local_hit_point = ray.o + tmin * ray.d;				
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			Vector3D hit = ray.o + t * ray.d - center;
			
			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;
			
			if (hit.y <= radius * cos_theta_min && 	
				hit.y >= radius * cos_theta_max && 	
				phi >= phi_min && phi <= phi_max) {
				
				tmin = t;				
//				sr.normal = (temp + t * ray.d) / radius;   // points outwards
//				sr.local_hit_point = ray.o + tmin * ray.d;				
				return (true);
			}
		} 
	}
	
	return (false);
}

BBox
ConvexPartSphere::get_bounding_box(void) const {
	double delta = 0.0001; 
	
	// This is from Sphere, could be more efficient
	
	return (BBox(Point3D(center.x - radius - delta, center.y - radius - delta, center.z - radius - delta),
				 Point3D(center.x + radius + delta, center.y + radius + delta, center.z + radius + delta)));
}
