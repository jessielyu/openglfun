/*
 *  BuildTransparent.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/25/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

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
#include "GlossySpecular.h"
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
#include "Plane.h"
#include "GlossyReflector.h"
#include "PathTrace.h"
#include "GlobalTrace.h"
#include "Transparent.h"

//void 												
//World::build(void){
//	int num_samples = 16;
//	
//	vp.set_hres(400);	  		
//	vp.set_vres(400);
//	vp.set_samples(num_samples);
//	//vp.set_max_depth(2);		// for 27.13(a)
//	//vp.set_max_depth(4);		// for 27.13(b)		
//	vp.set_max_depth(10);		// for 27.13(c) & 27.14
//	
//	background_color = MyRGBColor(0.0, 0.3, 0.25);
//	//background_color = (black);
//	
//	tracer_ptr = new Whitted(this);//AreaLighting(this);
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(0.0);
//	set_ambient_light(ambient_ptr);
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(-8, 5.5, 40);   
//	pinhole_ptr->set_lookat(1, 4, 0);    
//	pinhole_ptr->set_view_distance(2400.0);  
//	pinhole_ptr->set_zoom(2.0/3.0);
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr);
//	
//	
//	// point light 
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(40, 50, 0); 
//	light_ptr1->scale_radiance(4.5);
//	light_ptr1->set_shadows(true);
//	add_light(light_ptr1);
//	
//	
//	// point light 
//	
//	PointLight* light_ptr2 = new PointLight;
//	light_ptr2->set_location(-10, 20, 10); 
//	light_ptr2->scale_radiance(4.5);
//	light_ptr2->set_shadows(true);
//	add_light(light_ptr2);
//	
//	
//	// directional light 
//	
//	Directional* light_ptr3 = new Directional;
//	light_ptr3->set_direction(-1, 0, 0); 
//	light_ptr3->scale_radiance(4.5);
//	light_ptr3->set_shadows(true);
//	add_light(light_ptr3);
//	
//	
//	// transparent sphere
//	
//	Transparent* glass_ptr = new Transparent;
//	glass_ptr->set_ks(0.2);
//	glass_ptr->set_exp(2000.0);
//	//glass_ptr->set_ior(0.75);
//	//glass_ptr->set_ior(1.0);
//	//glass_ptr->set_ior(1.1);			// for Figure 27.14(a)	
//		glass_ptr->set_ior(1.5);			// for Figure 27.14(b)
//	glass_ptr->set_kr(0.1);
//	glass_ptr->set_kt(0.9);
//	
//	glass_ptr->set_ca(0.0,0.0,0.0);
//	glass_ptr->set_cd(0.0,0.0,0.0);
//	glass_ptr->set_cs(0.0,0.0,0.0);
//	
////	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 4.5, 0.0), 3.0);
////	sphere_ptr1->set_material(glass_ptr);
////	add_object(sphere_ptr1);
//	
//	double bottom 	= 0.0;
//	double top 		= 4.5;
//	double radius 	= 3;
//	
//	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
//	cylinder_ptr->set_material(glass_ptr);
//	add_object(cylinder_ptr);
//	
////	char* file_name = "../../PLYFiles/Bunny4k.ply";
////	Grid* mesh_grid_ptr = new Grid(new Mesh);
////	//mesh_grid_ptr->reverse_mesh_normals();
////	mesh_grid_ptr->read_smooth_triangles(file_name);
////	mesh_grid_ptr->set_material(glass_ptr);
////	mesh_grid_ptr->setup_cells();
////	Instance* instance = new Instance(mesh_grid_ptr);
////	instance->scale(60, 60, 60);
////	instance->translate(2.0, -1.75, 0);
////	instance->compute_bounding_box();
////	add_object(instance);	
//	
//	
//	// red sphere
//	
//	Reflective*	reflective_ptr = new Reflective;
//	reflective_ptr->set_ka(0.3);
//	reflective_ptr->set_kd(0.3); 
//	reflective_ptr->set_cd(red); 
//	reflective_ptr->set_ks(0.2);
//	reflective_ptr->set_exp(2000.0);
//	reflective_ptr->set_kr(0.25);
//	
//	Sphere* sphere_ptr2 = new Sphere(Point3D(4, 4, -6), 3);
//	sphere_ptr2->set_material(reflective_ptr);
	
//	add_object(sphere_ptr2);
//	
//	
////	Checker3D* checker_ptr = new Checker3D;
////	checker_ptr->set_size(4);
////	checker_ptr->set_color1(0.75);  
////	checker_ptr->set_color2(white);	
////	
////	SV_Matte* sv_matte_ptr = new SV_Matte;		
////	sv_matte_ptr->set_ka(0.5);
////	sv_matte_ptr->set_kd(0.35);
////	sv_matte_ptr->set_cd(checker_ptr);	
//	
//	Matte* white_matte_ptr = new Matte;
//	white_matte_ptr->set_ka(0.5);
//	white_matte_ptr->set_kd(0.35);
//	white_matte_ptr->set_cd(white);	
//	
//	// rectangle
//	
//	Point3D p0(-20, 0, -100);
//	Vector3D a(0, 0, 120);
//	Vector3D b(40, 0, 0);
//	
//	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, Normal(0,1,0)); 
//	rectangle_ptr->set_material(white_matte_ptr);
//	rectangle_ptr->set_shadows(true);
//	add_object(rectangle_ptr);		
//	
////	Plane* plane_ptr = new Plane(p0, Normal(0,1,0));
////	plane_ptr->set_material(white_matte_ptr);
////	plane_ptr->set_shadows(true);
////	add_object(plane_ptr);
//}

//void
//World::build(void){
//	int num_samples = 16;
//	
//	vp.set_hres(400);	  		
//	vp.set_vres(400);
//	vp.set_samples(num_samples);		
//	vp.set_max_depth(5);		
//	
//	background_color = MyRGBColor(0.0, 0.3, 0.25);
//	
//	tracer_ptr = new Whitted(this);
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(0.25);
//	set_ambient_light(ambient_ptr);
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(-5, 5.5, 35);      
//	pinhole_ptr->set_lookat(1.25, 3.5, 0);     
//	pinhole_ptr->set_view_distance(2400.0);  
//	pinhole_ptr->set_zoom(2.0/3.0);
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr);
//	
//	
//	// point light 
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(40, 50, 0); 
//	light_ptr1->scale_radiance(4.0);
//	light_ptr1->set_shadows(true);
//	add_light(light_ptr1);
//	
//	
//	// point light 
//	
//	PointLight* light_ptr2 = new PointLight;
//	light_ptr2->set_location(-10, 20, 10); 
//	light_ptr2->scale_radiance(4.0);
//	light_ptr2->set_shadows(true);
//	add_light(light_ptr2);
//	
//	
//	// directional light 
//	
//	Directional* light_ptr3 = new Directional;
//	light_ptr3->set_direction(-1, 0, 0); 
//	light_ptr3->scale_radiance(4.0);
//	light_ptr3->set_shadows(true);
//	add_light(light_ptr3);
//	
//	
//	// transparent bunny
//	
//	Transparent* glass_ptr = new Transparent;
//	glass_ptr->set_ks(0.2);
//	glass_ptr->set_exp(2000.0);
//	glass_ptr->set_ior(1.5);		
//	glass_ptr->set_kr(0.1);
//	glass_ptr->set_kt(0.9);
//	
//	//	const char* fileName = "../../PLYFiles/Bunny3K.ply"; 	// 4000 triangles
//	//	const char* fileName = "../../PLYFiles/Bunny10K.ply"; 	// 10000 triangles
//	char* fileName = "../../PLYFiles/Bunny16K.ply"; 	// 16000 triangles
//	//	const char* fileName = "../../PLYFiles/Bunny69K.ply"; 	// 69000 triangles
//	
//	Mesh* mesh_ptr = new Mesh;
//	Grid* bunny_ptr = new Grid(mesh_ptr);
//	//	bunny_ptr->read_flat_triangles(fileName);	
//	bunny_ptr->read_smooth_triangles(fileName);	
//	bunny_ptr->set_material(glass_ptr); 	
//	bunny_ptr->setup_cells();
//	
//	Instance* big_bunny_ptr = new Instance(bunny_ptr);
//	big_bunny_ptr->scale(45.0);
//	big_bunny_ptr->translate(1.7, -1.5, 0.0);
//	add_object(big_bunny_ptr);
//	
//	
//	// red sphere
//	
//	Reflective*	reflective_ptr = new Reflective;
//	reflective_ptr->set_ka(0.3);
//	reflective_ptr->set_kd(0.3); 
//	reflective_ptr->set_cd(red); 
//	reflective_ptr->set_ks(0.2);
//	reflective_ptr->set_exp(2000.0);
//	reflective_ptr->set_kr(0.25);
//	
//	Sphere* sphere_ptr2 = new Sphere(Point3D(4, 4, -6), 3);
//	sphere_ptr2->set_material(reflective_ptr);
//	add_object(sphere_ptr2);
//	
//	
////	Checker3D* checker_ptr = new Checker3D;
////	checker_ptr->set_size(4.0);
////	checker_ptr->set_color1(white);  
////	checker_ptr->set_color2(0.75);	
////	
////	SV_Matte* sv_matte_ptr = new SV_Matte;		
////	sv_matte_ptr->set_ka(0.5);
////	sv_matte_ptr->set_kd(0.35);
////	sv_matte_ptr->set_cd(checker_ptr);	
//	
//	Matte* white_matte_ptr = new Matte;
//	white_matte_ptr->set_ka(0.5);
//	white_matte_ptr->set_kd(0.35);
//	white_matte_ptr->set_cd(white);	
//	
//	// rectangle
//	
//	Point3D p0(-20, 0, -100);
//	Vector3D a(0, 0, 120);
//	Vector3D b(40, 0, 0);
//	
//	Rectangle* rectangle_ptr = new Rectangle(p0, a, b); 
//	rectangle_ptr->set_material(white_matte_ptr);
//	add_object(rectangle_ptr);	
//}
//
//
//
//
//
