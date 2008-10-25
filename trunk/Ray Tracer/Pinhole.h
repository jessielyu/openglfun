#ifndef __PINHOLE__
#define __PINHOLE__

/*
 *  Pinhole.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/14/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Camera.h"
#include "Point3D.h"
#include "Vector3D.h"

class Point2D;

class Pinhole: public Camera {
public:
	// constructors etc
	Pinhole(void);
	
	Pinhole(const Point3D e, const Point3D l, const Vector3D u, float distance, float z);
	
	~Pinhole();
	
	void
	set_d(float distance);
	
	void
	set_view_distance(float distance);
	
	void
	set_zoom(float z);
	
	Vector3D
	ray_direction(const Point2D& p) const;
	
	virtual void
	render_scene(World& w);
	
	virtual void
	render_stereo(World& w, float x, int offset);
	
private:
	
	float d;		// View plane distance
	float zoom;		// zoom factor
	
};

inline void
Pinhole::set_d(float distance) {
	d = distance;
}

inline void
Pinhole::set_view_distance(float distance) {
	set_d(distance);
}

inline void
Pinhole::set_zoom(float z) {
	zoom = z;
}

#endif