#ifndef __STEREO_CAMERA__
#define __STEREO_CAMERA__

/*
 *  StereoCamera.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Camera.h"
#include "World.h"

typedef enum {
	parallel,
	transverse
}	ViewingType;

class StereoCamera: public Camera {
public:
	
	// constructors
	
	StereoCamera(void);
	
	StereoCamera(const Point3D e, const Point3D l, const Vector3D u, const int gap, const float beta,
				 Camera* left, Camera* right, ViewingType view = parallel);
	
	StereoCamera(const StereoCamera& s);
	
	StereoCamera& operator= (const StereoCamera& s);
	
	~StereoCamera(void);
	
	void
	set_viewing(ViewingType view);
	
	void
	set_pixel_gap(const int gap);
	
	void 
	set_beta(const float b);
	
	void 
	set_right_camera_ptr(Camera* right);
	
	void
	set_left_camera_ptr(Camera* left);
	
	void
	setup_cameras(void);
	
	virtual void
	render_scene(World& wr);
	
	virtual void
	render_stereo(World& w, float x, int offset);
	
private:

	ViewingType viewing;			// type of viewing
	int pixel_gap;					// gap (in pixels) between images
	float beta;						// stereo separation angle
	Camera* left_camera_ptr;		// left eye camera
	Camera* right_camera_ptr;		// right eye camera
	
};

inline void
StereoCamera::set_viewing(ViewingType view) {
	viewing = view;
}

inline void
StereoCamera::set_pixel_gap(const int gap) {
	pixel_gap = gap;
}

inline void 
StereoCamera::set_beta(const float b) {
	beta = b;
}

#endif