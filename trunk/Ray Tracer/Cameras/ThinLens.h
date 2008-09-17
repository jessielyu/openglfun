#ifndef __THIN_LENS__
#define __THIN_LENS__

/*
 *  ThinLens.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/15/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Camera.h"
#include "Point2D.h"

class Sampler;

class ThinLens: public Camera {
public:
	
	// constructor
	
	ThinLens(void);
	
	ThinLens(const Point3D e, const Point3D l, const Vector3D u, float lens_radius, float d, float f, float zoom = 1.0);
	
	~ThinLens(void);
	
	void 
	set_lens_radius(float lr);
	
	void
	set_d(float distance);
	
	void
	set_f(float focal);
	
	void
	set_zoom(float z);
	
	void
	set_sampler(Sampler* sp);
	
	Vector3D
	ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;
	
	virtual void
	render_scene(World& w);
	
private:
	
	float lens_radius;
	float d;				// view plane distance
	float f;				// focal plane distance
	float zoom;				// zoom factor
	Sampler* sampler_ptr;
	
};

inline void 
ThinLens::set_lens_radius(float lr){
	lens_radius = lr;
}

inline void
ThinLens::set_d(float distance) {
	d = distance;
}

inline void
ThinLens::set_f(float focal) {
	f = focal;
}

inline void
ThinLens::set_zoom(float z) {
	zoom = z;
}


#endif