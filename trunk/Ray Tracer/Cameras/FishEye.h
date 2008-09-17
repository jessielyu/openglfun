#ifndef __FISH_EYE__
#define __FISH_EYE__

/*
 *  FishEye.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/16/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Camera.h"
#include "Point2D.h"

class FishEye: public Camera {
public:
	
	FishEye(void);
	
	FishEye(const Point3D e, const Point3D l, const Vector3D u, const float psi);
	
	~FishEye(void);
	
	void
	set_psi_max(const float psi);
	
	Vector3D 
	ray_direction(const Point2D& p, const int hres, const int vres, const float s, float& r) const;
	
	virtual void
	render_scene(World& w);
	
	virtual void
	render_stereo(World& w, float x, int offset);
	
private:
	
	float psi_max;		// in degrees
	
};

inline void
FishEye::set_psi_max(const float psi) {
	psi_max = psi;
}


#endif