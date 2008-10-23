#ifndef __MESH__
#define __MESH__

/*
 *  Mesh.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
#include <vector>
#include "Point3D.h"
#include "Normal.h"

class Mesh {
public:
	
	std::vector<Point3D> vertices;
	std::vector<int> indices;
	std::vector<Normal> normals;
	std::vector<std::vector<int> > vertex_faces; // faces shared by each vertex
	std::vector<float> u;	// texture coordinates
	std::vector<float> v;
	int num_vertices;
	int num_triangles;
	
};

#endif