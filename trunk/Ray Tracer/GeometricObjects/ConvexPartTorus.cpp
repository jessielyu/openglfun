/*
 *  ConvexPartTorus.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "ConvexPartTorus.h"
#include "Maths.h"

ConvexPartTorus::ConvexPartTorus(void) 
:	GeometricObject(),
	a(2.0),
	b(1),
	bbox(-a - b, a + b, -b, b, -a - b, a + b),
	phi_min(0.0),
	phi_max(TWO_PI),
	theta_min(0.0),
	theta_max(TWO_PI)
{}

ConvexPartTorus::ConvexPartTorus(const double _a, const double _b,	
								 const double azimuth_min, // degrees
								 const double azimuth_max, // degrees
								 const double polar_min,   // degrees from top
								 const double polar_max)
:	GeometricObject(),
	a(_a),
	b(_b),
	bbox(-a - b, a + b, -b, b, -a - b, a + b),
	phi_min(azimuth_min * PI_ON_180),
	phi_max(azimuth_max * PI_ON_180),
	theta_min(polar_min * PI_ON_180),
	theta_max(polar_max * PI_ON_180)
{}

ConvexPartTorus*
ConvexPartTorus::clone(void) const {
	return (new ConvexPartTorus(*this));
}

ConvexPartTorus::ConvexPartTorus(const ConvexPartTorus& torus) 
:	GeometricObject(torus),
a(torus.a),
b(torus.b),
bbox(torus.bbox)
{}

ConvexPartTorus::~ConvexPartTorus(void) {}										

ConvexPartTorus& 
ConvexPartTorus::operator= (ConvexPartTorus& rhs) {
	if (this == &rhs)
		return (*this);
	
	GeometricObject::operator= (rhs);
	
	a = rhs.a;
	b = rhs.b;
	bbox = rhs.bbox;
	
	return (*this);
}

Normal
ConvexPartTorus::compute_normal(const Point3D& p) const {
	Normal normal;
	double param_squared = a * a + b * b;
	
	double x = p.x;
	double y = p.y;
	double z = p.z;
	double sum_squared = x * x + y * y + z * z;
	
	normal.x = 4.0 * x * (sum_squared - param_squared);
	normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
	normal.z = 4.0 * z * (sum_squared - param_squared);
	normal.normalize();
	
	return (normal);
}


bool 																 
ConvexPartTorus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (!bbox.hit(ray))
		return (false);
	
	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;	
	
	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation
	
	// define the coefficients of the quartic equation
	
	double sum_d_sqrd 	= d1 * d1 + d2 * d2 + d3 * d3;
	double e			= x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f			= x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd	= 4.0 * a * a;
	
	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4
	
	// find roots of the quartic equation
	
	int num_real_roots = SolveQuartic(coeffs, roots);
	
	bool	intersected = false;
	double 	t 		 	= kHugeValue;
	
	if (num_real_roots == 0)  // ray misses the torus
		return(false);
	
	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted
	
	for (int j = 0; j < num_real_roots; j++)  
		if (roots[j] > kEpsilon) {
			Vector3D hit = ray.o + roots[j] * ray.d;
			
			float phi = atan2(hit.x, hit.z);
			
			if(phi < 0.0)
				phi+= TWO_PI;
			
			if(phi >= phi_min && phi <= phi_max) {
				Point3D pointA(0,0,a);
				
				Matrix theta_matrix;
				
				theta_matrix.m[0][0] = cos(phi);
				theta_matrix.m[0][2] = -sin(phi);
				theta_matrix.m[2][0] = sin(phi);
				theta_matrix.m[2][2] = cos(phi);
				
				// rotate to our hitpoint
				pointA = theta_matrix * pointA;
				
				Vector3D theta_hit = ray.o + roots[j] * ray.d - pointA;
				
				float theta = atan2(theta_hit.x, theta_hit.y);
				
				if (theta < 0.0)
					theta += TWO_PI;
				
				if(theta >= theta_min && theta <= theta_max) {
					intersected = true;
					if (roots[j] < t)
						t = roots[j];
				}
			}
		}
	
	if(!intersected)
		return (false);
	
	tmin 			 	= t;
	sr.local_hit_point 	= ray.o + t * ray.d;
	sr.normal 		 	= compute_normal(sr.local_hit_point);
	
	return (true);
}

bool 																 
ConvexPartTorus::shadow_hit(const Ray& ray, float& tmin) const {
	if (!bbox.hit(ray))
		return (false);
	
	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;	
	
	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation
	
	// define the coefficients of the quartic equation
	
	double sum_d_sqrd 	= d1 * d1 + d2 * d2 + d3 * d3;
	double e			= x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f			= x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd	= 4.0 * a * a;
	
	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4
	
	// find roots of the quartic equation
	
	int num_real_roots = SolveQuartic(coeffs, roots);
	
	bool	intersected = false;
	double 	t 		 	= kHugeValue;
	
	if (num_real_roots == 0)  // ray misses the torus
		return(false);
	
	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted
	
	for (int j = 0; j < num_real_roots; j++)  
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t)
				t = roots[j];
		}
	
	if(!intersected)
		return (false);
	
	tmin 			 	= t;
	//	sr.local_hit_point 	= ray.o + t * ray.d;
	//	sr.normal 		 	= compute_normal(sr.local_hit_point);
	
	return (true);
}