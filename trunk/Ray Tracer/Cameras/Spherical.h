#ifndef __SPHERICAL__
#define __SPHERICAL__

/*
 *  Spherical.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Camera.h"
#include "Point2D.h"
#include "World.h"

class Spherical: public Camera {
public:
	
	Spherical(void);
	
	Spherical(const Point3D e, const Point3D l, const Vector3D u, const float lambda, const float psi);
	
	~Spherical(void);
	
	void
	set_lambda_max(const float lambda);
	
	void
	set_psi_max(const float psi);
	
	Vector3D
	ray_direction(const Point2D& pp, const int hres, const int vres, const float s) const;
	
	void
	render_scene(World& wr);
	
private:
	
	float lambda_max;		// Max angle on the u, w plane measured counterclockwise from the view direction
	float psi_max;			// Max up from the view plane
};

inline 	void
Spherical::set_lambda_max(const float lambda) {
	lambda_max = lambda;
}	

inline void
Spherical::set_psi_max(const float psi) {
	psi_max = psi;
}

#endif