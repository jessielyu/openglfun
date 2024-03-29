///*
// *  BuildCornellBox.cpp
// *  Ray Tracer
// *
// *  Created by NoEvilPeople on 10/24/08.
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
//#include "GlossySpecular.h"
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
//#include "GlossyReflector.h"
//#include "PathTrace.h"
//#include "GlobalTrace.h"
//
//
//// Cornell Box (GlobalTrace)
////void
////World::build(void) { 
////	int num_samples = 100;
////	
////	vp.set_hres(400);	  		
////	vp.set_vres(400);
////	vp.set_samples(num_samples); 
////	vp.set_max_depth(10);
////	
////	background_color = black;
////	
////	tracer_ptr = new GlobalTrace(this);
////	
////	Ambient* ambient_ptr = new Ambient;
////	ambient_ptr->scale_radiance(0.0);
////	set_ambient_light(ambient_ptr);
////	
////	
////	Pinhole* pinhole_ptr = new Pinhole;
////	pinhole_ptr->set_eye(27.6, 27.4, -80.0);
////	pinhole_ptr->set_lookat(27.6, 27.4, 0.0);
////	pinhole_ptr->set_view_distance(400); 
////	pinhole_ptr->set_zoom(1.45);
////	pinhole_ptr->compute_uvw();     
////	set_camera(pinhole_ptr);
////	
////	Point3D p0;
////	Vector3D a, b;
////	Normal normal;
////	
////	// box dimensions
////	
////	double width 	= 55.28;   	// x direction
////	double height 	= 54.88;  	// y direction
////	double depth 	= 55.92;	// z direction
////	
////	
////	Emissive* emissive_ptr = new Emissive;
////	emissive_ptr->set_ce(1.0, 0.73, 0.4);   
////	emissive_ptr->scale_radiance(100.0);
////	
////	p0 = Point3D(21.3, height - 0.001, 22.7);
////	a = Vector3D(0.0, 0.0, 10.5);
////	b = Vector3D(13.0, 0.0, 0.0);
////	normal = Normal(0.0, -1.0, 0.0);
////	
////	Rectangle* light_ptr = new Rectangle(p0, a, b, normal);
////	light_ptr->set_material(emissive_ptr);
////	light_ptr->set_sampler(new MultiJittered(num_samples));
////	light_ptr->set_shadows(false);
////	add_object(light_ptr);
////	
////	AreaLight* ceiling_light_ptr = new AreaLight;   
////	ceiling_light_ptr->set_object(light_ptr);		
////	ceiling_light_ptr->set_shadows(true);
////	add_light(ceiling_light_ptr);
////	
////	
////	// left wall
////	
////	Matte* matte_ptr1 = new Matte;
////	matte_ptr1->set_ka(0.0);
////	matte_ptr1->set_kd(0.6); 
////	matte_ptr1->set_cd(0.57, 0.025, 0.025);	 // red
////	matte_ptr1->set_sampler(new MultiJittered(num_samples));
////	
////	p0 = Point3D(width, 0.0, 0.0);
////	a = Vector3D(0.0, 0.0, depth);
////	b = Vector3D(0.0, height, 0.0);
////	normal = Normal(-1.0, 0.0, 0.0);
////	Rectangle* left_wall_ptr = new Rectangle(p0, a, b, normal);
////	left_wall_ptr->set_material(matte_ptr1);
////	add_object(left_wall_ptr);
////	
////	
////	// right wall
////	
////	Matte* matte_ptr2 = new Matte;
////	matte_ptr2->set_ka(0.0);
////	matte_ptr2->set_kd(0.6); 
////	matte_ptr2->set_cd(0.37, 0.59, 0.2);	 // green  
////	matte_ptr2->set_sampler(new MultiJittered(num_samples));
////	
////	p0 = Point3D(0.0, 0.0, 0.0);
////	a = Vector3D(0.0, 0.0, depth);
////	b = Vector3D(0.0, height, 0.0);
////	normal = Normal(1.0, 0.0, 0.0);
////	Rectangle* right_wall_ptr = new Rectangle(p0, a, b, normal);
////	right_wall_ptr->set_material(matte_ptr2);
////	add_object(right_wall_ptr);
////	
////	
////	// back wall
////	
////	Matte* matte_ptr3 = new Matte;
////	matte_ptr3->set_ka(0.0);
////	matte_ptr3->set_kd(0.6); 
////	matte_ptr3->set_cd(white);
////	matte_ptr3->set_sampler(new MultiJittered(num_samples));
////	
////	p0 = Point3D(0.0, 0.0, depth);
////	a = Vector3D(width, 0.0, 0.0);
////	b = Vector3D(0.0, height, 0.0);
////	normal = Normal(0.0, 0.0, -1.0);
////	Rectangle* back_wall_ptr = new Rectangle(p0, a, b, normal);
////	back_wall_ptr->set_material(matte_ptr3);
////	add_object(back_wall_ptr);
////	
////	
////	// floor
////	
////	p0 = Point3D(0.0, 0.0, 0.0);
////	a = Vector3D(0.0, 0.0, depth);
////	b = Vector3D(width, 0.0, 0.0);
////	normal = Normal(0.0, 1.0, 0.0);
////	Rectangle* floor_ptr = new Rectangle(p0, a, b, normal);
////	floor_ptr->set_material(matte_ptr3);
////	add_object(floor_ptr);
////	
////	
////	// ceiling
////	
////	p0 = Point3D(0.0, height, 0.0);
////	a = Vector3D(0.0, 0.0, depth);
////	b = Vector3D(width, 0.0, 0.0);
////	normal = Normal(0.0, -1.0, 0.0);
////	Rectangle* ceiling_ptr = new Rectangle(p0, a, b, normal);
////	ceiling_ptr->set_material(matte_ptr3);
////	add_object(ceiling_ptr);
////	
////	
////	// the two boxes defined as 5 rectangles each
////	
////	// short box
////	
////	// top
////	
////	p0 = Point3D(13.0, 16.5, 6.5);
////	a = Vector3D(-4.8, 0.0, 16.0);
////	b = Vector3D(16.0, 0.0, 4.9);
////	normal = Normal(0.0, 1.0, 0.0);
////	Rectangle* short_top_ptr = new Rectangle(p0, a, b, normal);
////	short_top_ptr->set_material(matte_ptr3);
////	add_object(short_top_ptr);
////	
////	
////	// side 1
////	
////	p0 = Point3D(13.0, 0.0, 6.5);
////	a = Vector3D(-4.8, 0.0, 16.0);
////	b = Vector3D(0.0, 16.5, 0.0);
////	Rectangle* short_side_ptr1 = new Rectangle(p0, a, b);
////	short_side_ptr1->set_material(matte_ptr3);
////	add_object(short_side_ptr1);
////	
////	
////	// side 2
////	
////	p0 = Point3D(8.2, 0.0, 22.5);
////	a = Vector3D(15.8, 0.0, 4.7);
////	Rectangle* short_side_ptr2 = new Rectangle(p0, a, b);
////	short_side_ptr2->set_material(matte_ptr3);
////	add_object(short_side_ptr2);
////	
////	
////	// side 3
////	
////	p0 = Point3D(24.2, 0.0, 27.4);
////	a = Vector3D(4.8, 0.0, -16.0);
////	Rectangle* short_side_ptr3 = new Rectangle(p0, a, b);
////	short_side_ptr3->set_material(matte_ptr3);
////	add_object(short_side_ptr3);
////	
////	
////	// side 4
////	
////	p0 = Point3D(29.0, 0.0, 11.4);
////	a = Vector3D(-16.0, 0.0, -4.9);
////	Rectangle* short_side_ptr4 = new Rectangle(p0, a, b);
////	short_side_ptr4->set_material(matte_ptr3);
////	add_object(short_side_ptr4);
////	
////	
////	
////	// tall box
////	
////	// top
////	
////	p0 = Point3D(42.3, 33.0, 24.7);
////	a = Vector3D(-15.8, 0.0, 4.9);
////	b = Vector3D(4.9, 0.0, 15.9);
////	normal = Normal(0.0, 1.0, 0.0);
////	Rectangle* tall_top_ptr = new Rectangle(p0, a, b, normal);
////	tall_top_ptr->set_material(matte_ptr3);
////	add_object(tall_top_ptr);
////	
////	
////	// side 1
////	
////	p0 = Point3D(42.3, 0.0, 24.7);
////	a = Vector3D(-15.8, 0.0, 4.9);
////	b = Vector3D(0.0, 33.0, 0.0);
////	Rectangle* tall_side_ptr1 = new Rectangle(p0, a, b);
////	tall_side_ptr1->set_material(matte_ptr3);
////	add_object(tall_side_ptr1);
////	
////	
////	// side 2
////	
////	p0 = Point3D(26.5, 0.0, 29.6);
////	a = Vector3D(4.9, 0.0, 15.9);
////	Rectangle* tall_side_ptr2 = new Rectangle(p0, a, b);
////	tall_side_ptr2->set_material(matte_ptr3);
////	add_object(tall_side_ptr2);
////	
////	
////	// side 3
////	
////	p0 = Point3D(31.4, 0.0, 45.5);
////	a = Vector3D(15.8, 0.0, -4.9);
////	Rectangle* tall_side_ptr3 = new Rectangle(p0, a, b);
////	tall_side_ptr3->set_material(matte_ptr3);
////	add_object(tall_side_ptr3);
////	
////	
////	// side 4
////	
////	p0 = Point3D(47.2, 0.0, 40.6);
////	a = Vector3D(-4.9, 0.0, -15.9);
////	Rectangle* tall_side_ptr4 = new Rectangle(p0, a, b);
////	tall_side_ptr4->set_material(matte_ptr3);
////	add_object(tall_side_ptr4);
////}
//
//
//
// Cornell box (PathTrace)

//void
//World::build(void) { 
//	 int num_samples = 1;		// for Figure 26.7(a)
//	//	int num_samples = 100;		// for Figure 26.7(b)
//	//	int num_samples = 1024;		// for Figure 26.7(c)
//	//	int num_samples = 10000;	// for Figure 26.7(d)
//
//	
//	vp.set_hres(400);	  		
//	vp.set_vres(400);
//	vp.set_samples(num_samples); 
//	vp.set_max_depth(10);
//	
//	background_color = black;
//	
//	tracer_ptr = new PathTrace(this);
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(27.6, 27.4, -80.0);
//	pinhole_ptr->set_lookat(27.6, 27.4, 0.0);
//	pinhole_ptr->set_view_distance(400);
//	pinhole_ptr->set_zoom(1.45);
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr);
//	
//	
//	Point3D p0;
//	Vector3D a, b;
//	Normal normal;
//	
//	// box dimensions
//	
//	double width 	= 55.28;   	// x direction
//	double height 	= 54.88;  	// y direction
//	double depth 	= 55.92;	// z direction
//	
//	
//	// the ceiling light - doesn't need samples
//	
//	Emissive* emissive_ptr = new Emissive;
//	emissive_ptr->set_ce(1.0, 0.73, 0.4);   
//	emissive_ptr->scale_radiance(100);
//	
//	p0 = Point3D(21.3, height - 0.001, 22.7);
//	a = Vector3D(0.0, 0.0, 10.5);
//	b = Vector3D(13.0, 0.0, 0.0);
//	normal = Normal(0.0, -1.0, 0.0);
//	Rectangle* light_ptr = new Rectangle(p0, a, b, normal);
//	light_ptr->set_material(emissive_ptr);
//	add_object(light_ptr);
//	
//	
//	// left wall
//	
//	Matte* matte_ptr1 = new Matte;
//	matte_ptr1->set_ka(0.0);
//	matte_ptr1->set_kd(0.6); 
//	matte_ptr1->set_cd(0.57, 0.025, 0.025);	 // red
//	matte_ptr1->set_sampler(new MultiJittered(num_samples));
//	
//	p0 = Point3D(width, 0.0, 0.0);
//	a = Vector3D(0.0, 0.0, depth);
//	b = Vector3D(0.0, height, 0.0);
//	normal = Normal(-1.0, 0.0, 0.0);
//	Rectangle* left_wall_ptr = new Rectangle(p0, a, b, normal);
//	left_wall_ptr->set_material(matte_ptr1);
//	add_object(left_wall_ptr);
//	
//	
//	// right wall
//	
//	Matte* matte_ptr2 = new Matte;
//	matte_ptr2->set_ka(0.0);
//	matte_ptr2->set_kd(0.6); 
//	matte_ptr2->set_cd(0.37, 0.59, 0.2);	 // green   from Photoshop
//	matte_ptr2->set_sampler(new MultiJittered(num_samples));
//	
//	p0 = Point3D(0.0, 0.0, 0.0);
//	a = Vector3D(0.0, 0.0, depth);
//	b = Vector3D(0.0, height, 0.0);
//	normal = Normal(1.0, 0.0, 0.0);
//	Rectangle* right_wall_ptr = new Rectangle(p0, a, b, normal);
//	right_wall_ptr->set_material(matte_ptr2);
//	add_object(right_wall_ptr);
//	
//	
//	// back wall
//	
//	Matte* matte_ptr3 = new Matte;
//	matte_ptr3->set_ka(0.0);
//	matte_ptr3->set_kd(0.6); 
//	matte_ptr3->set_cd(1.0);	 // white
//	matte_ptr3->set_sampler(new MultiJittered(num_samples));
//	
//	p0 = Point3D(0.0, 0.0, depth);
//	a = Vector3D(width, 0.0, 0.0);
//	b = Vector3D(0.0, height, 0.0);
//	normal = Normal(0.0, 0.0, -1.0);
//	Rectangle* back_wall_ptr = new Rectangle(p0, a, b, normal);
//	back_wall_ptr->set_material(matte_ptr3);
//	add_object(back_wall_ptr);
//	
//	
//	// floor
//	
//	p0 = Point3D(0.0, 0.0, 0.0);
//	a = Vector3D(0.0, 0.0, depth);
//	b = Vector3D(width, 0.0, 0.0);
//	normal = Normal(0.0, 1.0, 0.0);
//	Rectangle* floor_ptr = new Rectangle(p0, a, b, normal);
//	floor_ptr->set_material(matte_ptr3);
//	add_object(floor_ptr);
//	
//	
//	// ceiling
//	
//	p0 = Point3D(0.0, height, 0.0);
//	a = Vector3D(0.0, 0.0, depth);
//	b = Vector3D(width, 0.0, 0.0);
//	normal = Normal(0.0, -1.0, 0.0);
//	Rectangle* ceiling_ptr = new Rectangle(p0, a, b, normal);
//	ceiling_ptr->set_material(matte_ptr3);
//	add_object(ceiling_ptr);
//	
//	
//	// the two boxes defined as 5 rectangles each
//	
//	// short box
//	
//	// top
//	
//	p0 = Point3D(13.0, 16.5, 6.5);
//	a = Vector3D(-4.8, 0.0, 16.0);
//	b = Vector3D(16.0, 0.0, 4.9);
//	normal = Normal(0.0, 1.0, 0.0);
//	Rectangle* short_top_ptr = new Rectangle(p0, a, b, normal);
//	short_top_ptr->set_material(matte_ptr3);
//	add_object(short_top_ptr);
//	
//	
//	// side 1
//	
//	p0 = Point3D(13.0, 0.0, 6.5);
//	a = Vector3D(-4.8, 0.0, 16.0);
//	b = Vector3D(0.0, 16.5, 0.0);
//	Rectangle* short_side_ptr1 = new Rectangle(p0, a, b);
//	short_side_ptr1->set_material(matte_ptr3);
//	add_object(short_side_ptr1);
//	
//	
//	// side 2
//	
//	p0 = Point3D(8.2, 0.0, 22.5);
//	a = Vector3D(15.8, 0.0, 4.7);
//	Rectangle* short_side_ptr2 = new Rectangle(p0, a, b);
//	short_side_ptr2->set_material(matte_ptr3);
//	add_object(short_side_ptr2);
//	
//	
//	// side 3
//	
//	p0 = Point3D(24.2, 0.0, 27.4);
//	a = Vector3D(4.8, 0.0, -16.0);
//	Rectangle* short_side_ptr3 = new Rectangle(p0, a, b);
//	short_side_ptr3->set_material(matte_ptr3);
//	add_object(short_side_ptr3);
//	
//	
//	// side 4
//	
//	p0 = Point3D(29.0, 0.0, 11.4);
//	a = Vector3D(-16.0, 0.0, -4.9);
//	Rectangle* short_side_ptr4 = new Rectangle(p0, a, b);
//	short_side_ptr4->set_material(matte_ptr3);
//	add_object(short_side_ptr4);
//	
//	
//	
//	
//	// tall box
//	
//	// top
//	
//	p0 = Point3D(42.3, 33.0, 24.7);
//	a = Vector3D(-15.8, 0.0, 4.9);
//	b = Vector3D(4.9, 0.0, 15.9);
//	normal = Normal(0.0, 1.0, 0.0);
//	Rectangle* tall_top_ptr = new Rectangle(p0, a, b, normal);
//	tall_top_ptr->set_material(matte_ptr3);
//	add_object(tall_top_ptr);
//	
//	
//	// side 1
//	
//	p0 = Point3D(42.3, 0.0, 24.7);
//	a = Vector3D(-15.8, 0.0, 4.9);
//	b = Vector3D(0.0, 33.0, 0.0);
//	Rectangle* tall_side_ptr1 = new Rectangle(p0, a, b);
//	tall_side_ptr1->set_material(matte_ptr3);
//	add_object(tall_side_ptr1);
//	
//	
//	// side 2
//	
//	p0 = Point3D(26.5, 0.0, 29.6);
//	a = Vector3D(4.9, 0.0, 15.9);
//	Rectangle* tall_side_ptr2 = new Rectangle(p0, a, b);
//	tall_side_ptr2->set_material(matte_ptr3);
//	add_object(tall_side_ptr2);
//	
//	
//	// side 3
//	
//	p0 = Point3D(31.4, 0.0, 45.5);
//	a = Vector3D(15.8, 0.0, -4.9);
//	Rectangle* tall_side_ptr3 = new Rectangle(p0, a, b);
//	tall_side_ptr3->set_material(matte_ptr3);
//	add_object(tall_side_ptr3);
//	
//	
//	// side 4
//	
//	p0 = Point3D(47.2, 0.0, 40.6);
//	a = Vector3D(-4.9, 0.0, -15.9);
//	Rectangle* tall_side_ptr4 = new Rectangle(p0, a, b);
//	tall_side_ptr4->set_material(matte_ptr3);
//	add_object(tall_side_ptr4);
//}
//
//
// Test with big light target
//
//void 												
//World::build(void) {
//	int num_samples = 100;
//	
//	vp.set_hres(400);
//	vp.set_vres(400);
//	vp.set_samples(num_samples);
//	//vp.set_max_depth(0);				// for Figure 26.6(a)
//	//vp.set_max_depth(1);				// for Figure 26.6(b)
//	vp.set_max_depth(5);				// for Figure 26.6(c)
//	
//	tracer_ptr = new PathTrace(this);	
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(0.0);
//	set_ambient_light(ambient_ptr);	
//	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(100, 45, 100);  
//	pinhole_ptr->set_lookat(-10, 40, 0);  
//	pinhole_ptr->set_view_distance(400);   	
//	pinhole_ptr->compute_uvw(); 
//	set_camera(pinhole_ptr);
//	
//	
//	Emissive* emissive_ptr = new Emissive;
//	emissive_ptr->set_ce(white);  
//	emissive_ptr->scale_radiance(1.5);  
//	
//	
//	ConcaveSphere* sphere_ptr = new ConcaveSphere;		// centered on the origin
//	sphere_ptr->set_radius(1000000.0);
//	sphere_ptr->set_shadows(false);
//	sphere_ptr->set_material(emissive_ptr);
//	add_object(sphere_ptr);	
//	
//	
//	float ka = 0.2;  // common ambient reflection coefficient	
//	
//	
//	// large sphere
//	
//	Matte* matte_ptr1 = new Matte;			
//	matte_ptr1->set_ka(ka); 
//	matte_ptr1->set_kd(0.60);
//	matte_ptr1->set_cd(white);
//	matte_ptr1->set_sampler(new MultiJittered(num_samples));
//	
//	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20); 
//	sphere_ptr1->set_material(matte_ptr1);
//	add_object(sphere_ptr1);
//	
//	
//	// small sphere
//	
//	Matte* matte_ptr2 = new Matte;			
//	matte_ptr2->set_ka(ka); 
//	matte_ptr2->set_kd(0.5);
//	matte_ptr2->set_cd(0.85);				// gray
//	matte_ptr2->set_sampler(new MultiJittered(num_samples));
//	
//	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
//	sphere_ptr2->set_material(matte_ptr2);
//	add_object(sphere_ptr2);
//	
//	
//	// medium sphere
//	
//	Matte* matte_ptr3 = new Matte;			
//	matte_ptr3->set_ka(ka); 
//	matte_ptr3->set_kd(0.75);
//	matte_ptr3->set_cd(0.73, 0.22, 0.0);    // orange
//	matte_ptr3->set_sampler(new MultiJittered(num_samples));
//	
//	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
//	sphere_ptr3->set_material(matte_ptr3);
//	add_object(sphere_ptr3);
//	
//	
//	// cylinder
//	
//	Matte* matte_ptr4 = new Matte;			
//	matte_ptr4->set_ka(ka); 
//	matte_ptr4->set_kd(0.75);
//	matte_ptr4->set_cd(0.60);				// gray
//	matte_ptr4->set_sampler(new MultiJittered(num_samples));
//	
//	double bottom 	= 0.0;
//	double top 		= 85.0;
//	double radius	= 22.0;
//	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
//	cylinder_ptr->set_material(matte_ptr4);
//	add_object(cylinder_ptr);
//	
//	
//	// box
//	
//	Matte* matte_ptr5 = new Matte;			
//	matte_ptr5->set_ka(ka); 
//	matte_ptr5->set_kd(0.75);
//	matte_ptr5->set_cd(0.95);				// gray
//	matte_ptr5->set_sampler(new MultiJittered(num_samples));
//	
//	Box* box_ptr = new Box(Point3D(-55, 0, -110), Point3D(-25, 60, 65));  // thicker
//	box_ptr->set_material(matte_ptr5);
//	add_object(box_ptr);
//	
//	
//	// ground plane
//	
//	MultiJittered* sampler_ptr6 = new MultiJittered(num_samples);
//	
//	Matte* matte_ptr6 = new Matte;			
//	matte_ptr6->set_ka(0.15); 
//	matte_ptr6->set_kd(0.95);	
//	matte_ptr6->set_cd(0.37, 0.43, 0.08);     // olive green
//	matte_ptr6->set_sampler(new MultiJittered(num_samples));    
//	
//	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
//	plane_ptr->set_material(matte_ptr6);
//	add_object(plane_ptr);
//}



