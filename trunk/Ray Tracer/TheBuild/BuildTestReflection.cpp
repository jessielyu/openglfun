///*
// *  TestReflection.cpp
// *  Ray Tracer
// *
// *  Created by NoEvilPeople on 10/22/08.
// *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
// *
// */
//
//
//#include "Jittered.h"
//#include "Pinhole.h"
//#include "ThinLens.h"
//#include "FishEye.h"
//#include "Spherical.h"
//#include "StereoCamera.h"
//#include "Ambient.h"
//#include "PointLight.h"
//#include "Matte.h"
//#include "RayCast.h"
//#include "Directional.h"
////#include "GlossySpecular.h"
//#include "Phong.h"
//#include "AmbientOccluder.h"
//#include "MultiJittered.h"
//#include "Emissive.h"
//#include "Rectangle.h"
//#include "AreaLight.h"
//#include "AreaLighting.h"
//#include "EnvironmentLight.h"
//#include "ConcaveSphere.h"
//#include "Grid.h"
//#include "Triangle.h"
//#include "Disk.h"
//#include "Box.h"
//#include "OpenCylinder.h"
//#include "Torus.h"
//#include "FakeSphericalLight.h"
//#include "ConvexPartSphere.h"
//#include "SolidCylinder.h"
//#include "Instance.h"
//#include "ConvexPartCylinder.h"
//#include "ConvexPartTorus.h"
//#include "BeveledCylinder.h"
//#include "BeveledBox.h"
//#include "PartAnnulus.h"
//#include "BeveledWedge.h"
//#include "Archway.h"
//#include "Rosette.h"
//#include "Mesh.h"
//#include "Reflective.h"
//#include "Whitted.h"
//#include "Plane.h"
//
//// This builds the scene for Figure 24.6
//
//void 												
//World::build(void) {
//	int num_samples = 512;
//	
//	vp.set_hres(400); 
//	vp.set_vres(400);
//	vp.set_samples(num_samples);
//	//	vp.set_max_depth(0);			// for Figure 24.6(a)
//	vp.set_max_depth(10);			// for Figure 24.6(b)
//	
//	tracer_ptr = new Whitted(this);	
//	background_color = MyRGBColor(0.15); 
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(0.0);
//	set_ambient_light(ambient_ptr);
//	
//	// if I push this to 512, get weird artifacts
//	MultiJittered* occluder_sampler_ptr = new MultiJittered(MIN(num_samples, 256));
//	
//	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
//	ambient_occluder_ptr->scale_radiance(1.5);
//	ambient_occluder_ptr->set_color(white);
//	ambient_occluder_ptr->set_min_amount(0.25);
//	ambient_occluder_ptr->set_sampler(occluder_sampler_ptr);
//	set_ambient_light(ambient_occluder_ptr);
//	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(Point3D(75, 40, 100)); 
//	pinhole_ptr->set_lookat(Point3D(-10, 39, 0));  
//	pinhole_ptr->set_d(360);
//	pinhole_ptr->compute_uvw(); 
//	set_camera(pinhole_ptr);
//	
//	
//	PointLight* light_ptr = new PointLight;
//	light_ptr->set_location(150, 150, 0);  
//	light_ptr->scale_radiance(3.0);
//	light_ptr->set_shadows(true);
//	add_light(light_ptr);
//	
//	// yellow-green reflective sphere
//	
//	Reflective* reflective_ptr1 = new Reflective;			
//	reflective_ptr1->set_ka(0.25); 
//	reflective_ptr1->set_kd(0.5);
//	reflective_ptr1->set_cd(0.75, 0.75, 0);    	// yellow
//	reflective_ptr1->set_ks(0.15);
//	reflective_ptr1->set_exp_s(100.0);
//	reflective_ptr1->set_kr(0.75);
//	reflective_ptr1->set_cr(white); 			// default color
//	
//	float radius = 23.0;
//	Sphere* sphere_ptr1 = new Sphere(Point3D(38, radius, -25), radius); 
//	sphere_ptr1->set_material(reflective_ptr1);
//	add_object(sphere_ptr1);
//	
//	
//	// orange non-reflective sphere
//	
//	Matte* matte_ptr1 = new Matte;			
//	matte_ptr1->set_ka(0.45); 
//	matte_ptr1->set_kd(0.75);
//	matte_ptr1->set_cd(MyRGBColor(0.75, 0.25, 0));   // orange
//	
//	Sphere* sphere_ptr2 = new Sphere(Point3D(-7, 10, 42), 20);
//	sphere_ptr2->set_material(matte_ptr1);      
//	add_object(sphere_ptr2);
//	
//	
//	// sphere on top of box
//	
//	Reflective* reflective_ptr2 = new Reflective;			
//	reflective_ptr2->set_ka(0.35); 
//	reflective_ptr2->set_kd(0.75);
//	reflective_ptr2->set_c(black); 
//	reflective_ptr2->set_ks(0.0);		// default value
//	reflective_ptr2->set_exp_s(1.0);		// default value, but irrelevant in this case
//	reflective_ptr2->set_kr(0.75);
//	reflective_ptr2->set_cr(white); 
//	
//	Sphere* sphere_ptr3 = new Sphere(Point3D(-30, 59, 35), 20);
//	sphere_ptr3->set_material(reflective_ptr2);     
//	add_object(sphere_ptr3);
//	
//	
//	// cylinder
//	
//	Reflective* reflective_ptr3 = new Reflective;			
//	reflective_ptr3->set_ka(0.35); 
//	reflective_ptr3->set_kd(0.5);
//	reflective_ptr3->set_cd(0, 0.5, 0.75);   // cyan
//	reflective_ptr3->set_ks(0.2);
//	reflective_ptr3->set_exp_s(100.0);
//	reflective_ptr3->set_kr(0.75);
//	reflective_ptr3->set_cr(white);
//	
//	double bottom 			= 0.0;
//	double top 				= 85;   
//	double cylinder_radius	= 22;
//	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, cylinder_radius);
//	cylinder_ptr->set_material(reflective_ptr3);
//	add_object(cylinder_ptr);
//	
//	
//	// box
//	
//	Matte* matte_ptr2 = new Matte;			
//	matte_ptr2->set_ka(0.15); 
//	matte_ptr2->set_kd(0.5);
//	matte_ptr2->set_cd(MyRGBColor(0.75, 1.0, 0.75));   // light green
//	
//	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
//	box_ptr->set_material(matte_ptr2);
//	add_object(box_ptr);
//	
//	
//	// ground plane
//	
////	PlaneChecker* checker_ptr = new PlaneChecker;
////	checker_ptr->set_size(20.0);		
////	checker_ptr->set_outline_width(2.0);
////	checker_ptr->set_color1(white);
////	checker_ptr->set_color2(white);
////	checker_ptr->set_outline_color(black); 
////	
////	SV_Matte* sv_matte_ptr = new SV_Matte;		
////	sv_matte_ptr->set_ka(0.30);
////	sv_matte_ptr->set_kd(0.9);
////	sv_matte_ptr->set_cd(checker_ptr); 
//	
//	Matte* matte_ptr3 = new Matte;			
//	matte_ptr3->set_ka(0.15); 
//	matte_ptr3->set_kd(0.5);
//	matte_ptr3->set_cd(white);   // light green
//	
//	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
//	plane_ptr->set_material(matte_ptr3);
//	add_object(plane_ptr);
//}
//
//
//
//
