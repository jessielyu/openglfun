#ifndef __MESH_TRIANGLE__
#define __MESH_TRIANGLE__

/*
 *  MeshTriangle.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"
#include "Mesh.h"

class MeshTriangle: GeometricObject {
public:
	Mesh* mesh_ptr;					// data stored here
	int	index0, index1, index2;		// indices into the data
	Normal	normal;
	float area;	// required for translucency?
	
	MeshTriangle(void);
	
	MeshTriangle(Mesh* _mesh_ptr, const int i1, const int i2, const int i3);
	
	virtual MeshTriangle*
	clone(void) const = 0;
	
	MeshTriangle(const MeshTriangle& mt);
	
	virtual
	~MeshTriangle(void);
	
	MeshTriangle&
	operator= (const MeshTriangle& mt);
	
	virtual bool
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
	
	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const;
	
	void
	compute_normal(const bool reverse_normal);
	
	virtual Normal
	get_normal(void) const;
	
	virtual BBox
	get_bounding_box(void) const;

protected:
	
	float
	interpolate_u(const float beta, const float gamma) const;
	
	float
	interpolate_v(const float beta, const float gamma) const;
	
};

#endif