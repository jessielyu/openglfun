/*
 *  StereoCamera.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "StereoCamera.h"

StereoCamera::StereoCamera(void)
:	Camera(),
	viewing(parallel),
	pixel_gap(5),
	beta(10),
	left_camera_ptr(NULL),
	right_camera_ptr(NULL)
{}


StereoCamera::StereoCamera(const Point3D e, const Point3D l, const Vector3D u, const int gap, const float b,
			 Camera* left, Camera* right, ViewingType view) 
:	Camera(e, l, u),
	viewing(view),
	pixel_gap(5),
	beta(b),
	left_camera_ptr(left),
	right_camera_ptr(right)
{}

StereoCamera::StereoCamera(const StereoCamera& s) {
//:	Camera(s.get_eye(), s.get_lookat(), s.get_up()),
//	viewing(s.viewing),
//	pixel_gap(s.pixel_gap),
//	beta(s.beta),
//{
//	right_camera_ptr(*s.right_camera_ptr);
//	left_camera_ptr(*s.left_camera_ptr);
}

StereoCamera& StereoCamera::operator= (const StereoCamera& s)
{
//	eye = s.get_eye();
//	lookat = s.get_lookat();
//	up = s.get_up();
//	viewing = s.viewing;
//	pixel_gap = s.pixel_gap;
//	beta = s.beta;
//	right_camera_ptr = new Camera(s.right_camera_ptr);
//	left_camera_ptr = new Camera(s.left_camera_ptr);
}

StereoCamera::~StereoCamera(void){
	if (right_camera_ptr) {
		delete right_camera_ptr;
		right_camera_ptr = NULL;
	}
	if (left_camera_ptr) {
		delete left_camera_ptr;
		left_camera_ptr = NULL;
	}
}

void 
StereoCamera::set_right_camera_ptr(Camera* right) {
	if (right_camera_ptr) {
		delete right_camera_ptr;
		right_camera_ptr = NULL;
	}
	right_camera_ptr = right;
}

void
StereoCamera::set_left_camera_ptr(Camera* left) {
	if (left_camera_ptr) {
		delete left_camera_ptr;
		left_camera_ptr = NULL;
	}
}

void 
StereoCamera::setup_cameras(void) {
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);	// half the camera separation
	
	left_camera_ptr->set_eye(eye - x * u);
	left_camera_ptr->set_lookat(lookat - x * u);
	left_camera_ptr->compute_uvw();
	
	right_camera_ptr->set_eye(eye + x * u);
	right_camera_ptr->set_lookat(lookat + x * u);
	right_camera_ptr->compute_uvw();
}

void StereoCamera::render_scene(World& w) {
	ViewPlane vp = w.vp;
	int hres = vp.hres;
	int vres = vp.vres;
	
	double r = eye.distance (lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);
	
	if (viewing == parallel) {
		// left view on left
		left_camera_ptr->render_stereo(w, x, 0);
		// right view on right
		right_camera_ptr->render_stereo(w, -x, hres + pixel_gap);
	}
	
	if (viewing == transverse) {
		// right view on left
		right_camera_ptr->render_stereo(w, -x, 0);
		// left view on right
		left_camera_ptr->render_stereo(w, x, hres + pixel_gap);
	}
}

void
StereoCamera::render_stereo(World& w, float x, int offset) {}
		
