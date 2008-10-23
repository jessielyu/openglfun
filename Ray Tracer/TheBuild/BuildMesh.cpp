/*
 *  BuildMesh.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/20/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */


#include "World.h"
#include "MultipleObjects.h"
#include "Plane.h"

// samplers
#include "Jittered.h"
#include "Pinhole.h"
#include "ThinLens.h"
#include "FishEye.h"
#include "Spherical.h"
#include "StereoCamera.h"
#include "Ambient.h"
#include "PointLight.h"
#include "Matte.h"
#include "RayCast.h"
#include "Directional.h"
//#include "GlossySpecular.h"
#include "Phong.h"
#include "AmbientOccluder.h"
#include "MultiJittered.h"
#include "Emissive.h"
#include "Rectangle.h"
#include "AreaLight.h"
#include "AreaLighting.h"
#include "EnvironmentLight.h"
#include "ConcaveSphere.h"
#include "Grid.h"
#include "Triangle.h"
#include "Disk.h"
#include "Box.h"
#include "OpenCylinder.h"
#include "Torus.h"
#include "FakeSphericalLight.h"
#include "ConvexPartSphere.h"
#include "SolidCylinder.h"
#include "Instance.h"
#include "ConvexPartCylinder.h"
#include "ConvexPartTorus.h"
#include "BeveledCylinder.h"
#include "BeveledBox.h"
#include "PartAnnulus.h"
#include "BeveledWedge.h"
#include "Archway.h"
#include "Rosette.h"
#include "Mesh.h"
#include "Reflective.h"
#include "Whitted.h"

void 												
World::build(void) {
	int num_samples = 512/4;
	
	vp.set_hres(1680/4);//1680
	vp.set_vres(1050/4);//1050
	//vp.set_sampler(new Jittered(num_samples));
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples);
	vp.set_max_depth(2);
	
//	Pinhole* camera_ptr = new Pinhole;
//	camera_ptr->set_eye(Point3D(25, 0, 200)); 
//	camera_ptr->set_lookat(Point3D(-0.75,3.0, 0));
//	camera_ptr->set_d(3000.0);
//	//camera_ptr->compute_uvw();   
//	camera_ptr->set_zoom(2.25);//3 or 3.2
//	camera_ptr->compute_uvw();
//	set_camera(camera_ptr);
	
	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(Point3D(25, 0, 200)); 
	camera_ptr->set_lookat(Point3D(-0.75,3.0, 0));
	camera_ptr->set_d(3000.0);
	//camera_ptr->compute_uvw();   
	camera_ptr->set_zoom(3.0/4);//3 or 3.2
	camera_ptr->compute_uvw();
	set_camera(camera_ptr);
	
	
	tracer_ptr = new Whitted(this);//AreaLighting(this); 
	
	//background_color = MyRGBColor();
	background_color = MyRGBColor(0.4,0.4,0.8);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);

	//FakeSphericalLight
	FakeSphericalLight* light_ptr2 = new FakeSphericalLight;
	light_ptr2->set_location(100.0, 100.0, 200.0);
	light_ptr2->scale_radiance(3.0);
	light_ptr2->set_radius(100.0);
	add_light(light_ptr2);

	// if I push this to 512, get weird artifacts
	MultiJittered* occluder_sampler_ptr = new MultiJittered(MIN(num_samples, 256));
	
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->scale_radiance(1.5);
	ambient_occluder_ptr->set_color(white);
	ambient_occluder_ptr->set_min_amount(0.25);
	ambient_occluder_ptr->set_sampler(occluder_sampler_ptr);
	set_ambient_light(ambient_occluder_ptr);
	
//	Directional* light_ptr1 = new Directional;
//	light_ptr1->set_direction(15, 25, 50);
//	light_ptr1->scale_radiance(6.0); 	
//	add_light(light_ptr1);
//	
//	PointLight* light_ptr3 = new PointLight;
//	light_ptr3->set_location(2, 2, -10.0);
//	light_ptr3->scale_radiance(2.0);
//	add_light(light_ptr3);
	
	MyRGBColor yellow(1, 1, 0);										// yellow
	MyRGBColor brown(0.71, 0.40, 0.16);								// brown
	MyRGBColor darkGreen(0.0, 0.41, 0.41);							// dark_green
	MyRGBColor orange(1, 0.75, 0);									// orange
	MyRGBColor green(0, 0.6, 0.3);									// green
	MyRGBColor lightGreen(0.65, 1, 0.30);							// light green
	MyRGBColor darkYellow(0.61, 0.61, 0);							// dark yellow
	MyRGBColor lightPurple(0.65, 0.3, 1);							// light purple
	MyRGBColor darkPurple(0.5, 0, 1);								// dark purple
	MyRGBColor grey(0.25);											// grey
	
	bool use_grid = true;
	Grid* grid_ptr = NULL;
	
	if (use_grid) {
		grid_ptr = new Grid;
		set_rand_seed(15);
	}
	
	// yellow triangle
	
	Phong* phong1 = new Phong();
	phong1->set_ka(0.25);
	phong1->set_kd(0.75);
	phong1->set_c(1.0,1.00, 0);
	phong1->set_exp_s(5);
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.25); 
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(MyRGBColor(1, 1, 0));
	
	Phong* phong2 = new Phong();
	phong2->set_ka(0.25);
	phong2->set_kd(0.75);
	phong2->set_c(0.0,0.5, 0.41);
	phong2->set_exp_s(5);
	
	Phong* phong4 = new Phong();
	phong4->set_ka(0.25);
	phong4->set_kd(0.75);
	phong4->set_c(darkGreen);
	phong4->set_exp_s(5);
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.25); 
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(MyRGBColor(0.0, 0.5, 0.41));

	
	Phong* phong3 = new Phong();
	phong3->set_ka(0.25);
	phong3->set_kd(0.75);
	phong3->set_c(0.71,0.40, 0.16);
	phong3->set_exp_s(5);
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.25); 
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(MyRGBColor(0.71, 0.40, 0.16));
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->set_ka(0.25); 
	matte_ptr4->set_kd(0.75);
	matte_ptr4->set_cd(orange);
	
	Reflective* reflect_ptr1 = new Reflective;			
	reflect_ptr1->set_ka(0.25); 
	reflect_ptr1->set_kd(0.75);
	reflect_ptr1->set_c(black);
	reflect_ptr1->set_exp_s(100);
	reflect_ptr1->set_kr(0.75);
	reflect_ptr1->set_cr(white);

	
	// Archway(width, height, depth, column_width, double num_blocks, double num_wedges, double rb) {
	//Instance* archway_ptr = new Instance(new Archway(2.0, 2.5, 2.5, .4, 6, 10, .05, matte_ptr3));
	
	//Rosette(num_rings, hole_radius, ring_width, rb, y0,y1,mat_ptr);
	//	Instance* archway_ptr = new Instance(new Rosette(3, .375, .75, .075, 0, .75, matte_ptr3));
	//	archway_ptr->rotate_z(90);
	//	archway_ptr->rotate_y(60);
	//	archway_ptr->translate(0.75, -.375, 0);
	////	archway_ptr->scale(2, 2, 2);
	//	archway_ptr->compute_bounding_box();
	//	//archway_ptr->set_material(phong3);
	//	add_object(archway_ptr);
	//	
	//	Plane* ground = new Plane(Point3D(0,-3.0,0),Normal(0,1,0));
	//	ground->set_material(matte_ptr2);
	//	add_object(ground);
	
//	char* file_name = "../../PLYFiles/penguin_left_eyeball.ply";
//	//char* file_name = "../../PLYFiles/Bunny16k.ply";
//	Grid* mesh_grid_ptr = new Grid(new Mesh);
//	//mesh_grid_ptr->reverse_mesh_normals();
//	mesh_grid_ptr->read_smooth_triangles(file_name);
//	mesh_grid_ptr->set_material(matte_ptr4);
//	mesh_grid_ptr->setup_cells();
//	Instance* instance = new Instance(mesh_grid_ptr);
//	//instance->scale(30, 30, 30);
//	instance->compute_bounding_box();
//	add_object(instance);
	
	char* file_name = "../../PLYFiles/Bunny4k.ply";
	Grid* mesh_grid_ptr = new Grid(new Mesh);
	//mesh_grid_ptr->reverse_mesh_normals();
	mesh_grid_ptr->read_smooth_triangles(file_name);
	mesh_grid_ptr->set_material(reflect_ptr1);
	mesh_grid_ptr->setup_cells();
	Instance* instance = new Instance(mesh_grid_ptr);
	instance->scale(75, 75, 75);
	instance->translate(.5, -5.25, 0);
	instance->compute_bounding_box();
	add_object(instance);	

	
	// Matte material reflection coefficients - common to all materials
	
	float ka = 0.25;
	float kd = 0.75;
	float exp = 0.25;
	
	
	// HAS TO BE LAST
	if (use_grid) {
		grid_ptr->setup_cells();
		add_object(grid_ptr);
	}
}