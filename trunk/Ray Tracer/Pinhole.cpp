/*
 *  Pinhole.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/14/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Pinhole.h"
#include "MyRGBColor.h"
#include "ViewPlane.h"
#include "World.h"

Pinhole::Pinhole(void)
	:	Camera(),
		d (10.0),
		zoom(1.0) {}

Pinhole::Pinhole(const Point3D e, const Point3D l, const Vector3D u, float distance, float z)
	:	Camera(e, l, u),
		d(distance),
		zoom(z) {}

void
Pinhole::render_scene(World& w) {
	MyRGBColor L;
	ViewPlane vp(w.vp);
	Ray ray;
	int depth = 0;			// recursion depth
	Point2D sp;				// sample point in [0, 1] x [0, 1]
	Point2D pp;				// sample point on a pixel
	
	vp.s /= zoom;
	ray.o = eye;
	
	for (int r = 0; r < vp.vres; r++)	// up 
		for (int c = 0; c < vp.hres; c++) {
			L = black;
			
			for (int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
				ray.d = ray_direction(pp);
				
				// Should be trace_ray(ray, depth), but that function is not there yet
				L += w.tracer_ptr->trace_ray(ray);
				
			}
			
			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		}
}

Vector3D
Pinhole::ray_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();
	return(dir);
}