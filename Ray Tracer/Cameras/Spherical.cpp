/*
 *  Spherical.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Spherical.h"
#include "MyRGBColor.h"

Spherical::Spherical(void)
:	Camera(),
	lambda_max(90.0),
	psi_max(90.0)
{}

Spherical::Spherical(const Point3D e, const Point3D l, const Vector3D u, const float lambda, const float psi) 
:	Camera(e, l, u),
	lambda_max(lambda),
	psi_max(psi)
{}

Spherical::~Spherical(void) {}

Vector3D
Spherical::ray_direction(const Point2D& pp, const int hres, const int vres, const float s) const {
	// compute normalized device coordinates
	
	Point2D pn( 2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);
	
	// compute angles lambda and phi (in radians)
	
	float lambda = pn.x * lambda_max * PI_ON_180;
	float psi = pn.y * psi_max * PI_ON_180;
	
	// compute spherical azimuth and polar angles
	
	float phi = PI - lambda;
	float theta = 0.5 * PI -psi;
	
	float sin_phi = sin(phi);
	float cos_phi = cos(phi);
	float sin_theta = sin(theta);
	float cos_theta = cos(theta);
	
	Vector3D dir = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w;
	
	return (dir);
}

void
Spherical::render_scene(World& wr) { 	
	MyRGBColor L;
	ViewPlane vp(wr.vp);
	int hres = vp.hres;
	int vres = vp.vres;
	float s = vp.s;
	Ray ray;
	int depth = 0;
	Point2D sp;				// sample point in [0,1] x [0,1]
	Point2D pp;				// sample point on the pixel
	//float r_squared;		// sum of squares of normalized device coordinates
	
	ray.o = eye;
	
	for(int r = 0; r < vres; r++) 
		for (int c = 0; c < hres; c++) {
			L = black;
			
			for (int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = s * (c - 0.5 * hres + sp.x);
				pp.y = s * (r - 0.5 * vres + sp.y);
				ray.d = ray_direction(pp, hres, vres, s);//, r_squared);
				
				//if(r_squared <= 1.0)
					L += wr.tracer_ptr->trace_ray(ray, depth);
			}
			
			L /= vp.num_samples;
			L *= exposure_time;
			wr.display_pixel(r, c, L);
		}
}