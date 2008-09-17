/*
 *  FishEye.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/16/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "FishEye.h"
//#include "Point2D.h"
#include "ViewPlane.h"
#include "World.h"
//#include <math.h>

FishEye::FishEye(void) 
:	Camera(),
	psi_max(100)
{}

FishEye::FishEye(const Point3D e, const Point3D l, const Vector3D u, const float psi)
:	Camera(e, l, u),
	psi_max(psi)
{}

FishEye::~FishEye(void) {}

Vector3D 
FishEye::ray_direction(const Point2D& pp, const int hres, const int vres, const float s, float& r_squared) const {
	
	// compute normalized device coordinates
	
	Point2D pn(2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);
	r_squared = pn.x * pn. x + pn.y * pn.y;
	
	if (r_squared <= 1.0) {
		float r			= sqrt(r_squared);
		float psi		= r * psi_max * PI_ON_180;
		float sin_psi	= sin(psi);
		float cos_psi	= cos(psi);
		float sin_alpha	= pn.y / r;
		float cos_alpha = pn.x / r;
		Vector3D dir = sin_psi * cos_alpha * u + sin_psi * sin_alpha * v - cos_psi * w;
		
		return (dir);
	}
	else
		return (Vector3D(0.0));
}

void
FishEye::render_scene(World& wr) {
	MyRGBColor L;
	ViewPlane vp(wr.vp);
	int hres = vp.hres;
	int vres = vp.vres;
	float s = vp.s;
	Ray ray;
	int depth = 0;
	Point2D sp;				// sample point in [0,1] x [0,1]
	Point2D pp;				// sample point on the pixel
	float r_squared;		// sum of squares of normalized device coordinates
	
	ray.o = eye;
	
	for(int r = 0; r < vres; r++) 
		for (int c = 0; c < hres; c++) {
			L = black;
			
			for (int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = s * (c - 0.5 * hres + sp.x);
				pp.y = s * (r - 0.5 * vres + sp.y);
				ray.d = ray_direction(pp, hres, vres, s, r_squared);
				
				if(r_squared <= 1.0)
					L += wr.tracer_ptr->trace_ray(ray, depth);
			}
			
			L /= vp.num_samples;
			L *= exposure_time;
			wr.display_pixel(r, c, L);
		}
}

void
FishEye::render_stereo(World& w, float x, int offset) {}
	
