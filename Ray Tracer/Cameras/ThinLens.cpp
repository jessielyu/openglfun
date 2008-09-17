/*
 *  ThinLens.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/15/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "ThinLens.h"
#include "Sampler.h"
#include "Ray.h"
#include "World.h"

ThinLens::ThinLens(void) 
:	Camera(),
	lens_radius(1.0),
	d(100),
	f(100),
	zoom(1.0),
	sampler_ptr(NULL)
{}

ThinLens::ThinLens(const Point3D e, const Point3D l, const Vector3D u, float lr, float distance, float focal, float z)
:	Camera(e, l, u),
	lens_radius(lr),
	d(distance),
	f(focal),
	zoom(z),
	sampler_ptr(NULL)
{}

ThinLens::~ThinLens(void) {
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

void
ThinLens::set_sampler(Sampler* sp) {
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_unit_disk();
}

Vector3D
ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const {
	Point2D p;
	p.x = pixel_point.x * f/d;
	p.y = pixel_point.y * f/d;
	
	Vector3D dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - f * w;
	dir.normalize();
	
	return (dir);
}

void
ThinLens::render_scene(World& w) {
	MyRGBColor L;
	Ray ray;
	ViewPlane vp(w.vp);
	int depth = 0;
	
	Point2D sp;		// sample point in [0,1] x [0,1]
	Point2D pp;		// sample point on a pixel
	Point2D dp;		// sample point on a unit disk
	Point2D lp;		// sample point on a lens
	
	vp.s /= zoom;
	
	for (int r = 0; r < vp.vres - 1; r++)		// up
		for (int c = 0; c < vp.hres - 1; c++) {	// across
			for (int n = 0; n < vp.num_samples; n++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - vp.hres / 2.0 + sp.x);
				pp.y = vp.s * (r - vp.vres / 2.0 + sp.y);
				
				dp = sampler_ptr->sample_unit_disk();
				lp = dp * lens_radius;
				
				ray.o = eye + lp.x * u + lp.y * v;
				ray.d = ray_direction(pp, lp);
				L += w.tracer_ptr->trace_ray(ray, depth);
			}
			
			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		}
	
	
			
}