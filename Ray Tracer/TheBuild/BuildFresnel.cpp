/*
 *  BuildFresnel.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/26/08.
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
#include "Dielectric.h"
#include "GlassOfWater.h"
#include "SV_Matte.h"

// Good bunny

//void 												
//World::build(void) {
//	int num_samples = 100;
//	
//	vp.set_hres(600);	  		
//	vp.set_vres(600);
//	vp.set_samples(num_samples);	
//	vp.set_max_depth(9);		
//	
//	background_color = MyRGBColor(0.5);
//	
//	tracer_ptr = new AreaLighting(this);
//	
//	Ambient* ambient_ptr = new Ambient;
//	set_ambient_light(ambient_ptr);
//	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(-4, 4, 20);  
//	pinhole_ptr->set_lookat(-0.2, -0.5, 0);     
//	pinhole_ptr->set_view_distance(6000.0);	
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr);
//	
//	
//	// rectangular area light
//	
//	Emissive* emissive_ptr = new Emissive;
//	emissive_ptr->scale_radiance(40.0);		
//	emissive_ptr->set_ce(white);
//	
//	Point3D center(5, 6, 10);
//	double width = 4.0;
//	double height = 5.0;
//	
//	Point3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
//	Vector3D a(width, 0.0, 0.0);
//	Vector3D b(0.0, height, 0.0);
//	Normal normal(0, 0, -1);
//	
//	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
//	rectangle_ptr->set_material(emissive_ptr);
//	rectangle_ptr->set_sampler(new MultiJittered(num_samples));
//	rectangle_ptr->set_shadows(false);
//	add_object(rectangle_ptr);	
//	
//	AreaLight* area_light_ptr = new AreaLight;
//	area_light_ptr->set_object(rectangle_ptr);
//	area_light_ptr->set_shadows(true);
//	add_light(area_light_ptr);
//	
//	
//	// transparent bunny
//	
//	Dielectric* dielectric_ptr = new Dielectric;
//	dielectric_ptr->set_ka(0.0);
//	dielectric_ptr->set_kd(0.0); 
//	dielectric_ptr->set_ks(0.2);     
//	dielectric_ptr->set_exp(2000.0);
//	dielectric_ptr->set_eta_in(1.5);   
//	dielectric_ptr->set_eta_out(1.0);
//	dielectric_ptr->set_cf_in(0.75, 0.45, 0);   // orange
//	dielectric_ptr->set_cf_out(white);
//	
//	 char* file_name = "../../PLYFiles/Bunny4K.ply"; 	
//	
//	Mesh* mesh_ptr = new Mesh;
//	Grid* bunny_ptr = new Grid(mesh_ptr);
//	bunny_ptr->read_smooth_triangles(file_name);	
//	bunny_ptr->set_material(dielectric_ptr); 	
//	bunny_ptr->setup_cells();
//	
//	Instance* big_bunny_ptr = new Instance(bunny_ptr);
//	big_bunny_ptr->scale(10.0);
//	big_bunny_ptr->translate(0, -1.5, 0.0);
//	add_object(big_bunny_ptr);
//	
//	
//	PlaneChecker* plane_checker_ptr = new PlaneChecker;
//	plane_checker_ptr->set_size(0.25);		
//	plane_checker_ptr->set_outline_width(0.02);
//	plane_checker_ptr->set_color1(0.75);
//	plane_checker_ptr->set_color2(0.75);  
//	plane_checker_ptr->set_outline_color(black); 
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;		
//	sv_matte_ptr->set_ka(0.15);
//	sv_matte_ptr->set_kd(0.65);
//	sv_matte_ptr->set_cd(plane_checker_ptr);
//	
//	// ground plane	
//	
//	Plane* plane_ptr1 = new Plane(Point3D(0, -1.175, 0), Normal(0, 1, 0));
//	plane_ptr1->set_material(sv_matte_ptr);
//	plane_ptr1->set_shadows(false);
//	add_object(plane_ptr1);
//	
//	// back plane
//	
//	Instance* plane_ptr2 = new Instance(new Plane(Point3D(0), Normal(0, 1, 0)));
//	plane_ptr2->set_material(sv_matte_ptr);
//	plane_ptr2->rotate_x(90);
//	plane_ptr2->translate(0, 0, -2);
//	plane_ptr2->set_shadows(false);
//	add_object(plane_ptr2);
//	
//	
//	
//}





//void 												
//World::build(void){
//	int num_samples = 16;
//	
//	vp.set_hres(600);	  		
//	vp.set_vres(600);
//	vp.set_samples(num_samples);		
//	vp.set_max_depth(7);		
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
//	pinhole_ptr->set_eye(-8, 5.5, 40);   
//	pinhole_ptr->set_lookat(1, 4, 0);    
//	pinhole_ptr->set_view_distance(2400.0);  
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
//	Dielectric* dielectic_ptr = new Dielectric;
//	dielectic_ptr->set_ks(0.2);
//	dielectic_ptr->set_exp(2000.0);
//	dielectic_ptr->set_eta_in(1.5);		// for Figure 28.5(a)
//	//	dielectic_ptr->set_eta_in(0.75);	// for Figure 28.5(b)
//	dielectic_ptr->set_eta_out(1.0);
//	dielectic_ptr->set_cf_in(white);
//	dielectic_ptr->set_cf_out(white);
//	
//	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 4.5, 0.0), 3.0);
//	sphere_ptr1->set_material(dielectic_ptr);
//	add_object(sphere_ptr1);
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
//	Rectangle* rectangle_ptr = new Rectangle(p0, a, b); 
//	rectangle_ptr->set_material(white_matte_ptr);
//	add_object(rectangle_ptr);		
//}

//void 												
//World::build(void) {
//	int num_samples = 25;
//	
//	vp.set_hres(400);	  		
//	vp.set_vres(400);
//	vp.set_samples(num_samples);
//	vp.set_max_depth(7);
//	
//	background_color = MyRGBColor(0.0, 0.3, 0.25);  // blue green
//	
//	tracer_ptr = new Whitted(this);
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(0.25);
//	set_ambient_light(ambient_ptr);
//	
//	Pinhole* pinhole_ptr = new Pinhole;
////	pinhole_ptr->set_eye(0.5, 40.0, 0.5);
////	pinhole_ptr->set_lookat(0.5, 0.0, 0.5);
////	pinhole_ptr->set_view_distance(3000.0);
//	
//	// other angle
//	pinhole_ptr->set_eye(5, 3, 10);
//	pinhole_ptr->set_lookat(0.0);
//	pinhole_ptr->set_view_distance(700);
//	
//	pinhole_ptr->set_zoom(2.0/3.0);
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr);
//
//
//	
//	Directional* light_ptr = new Directional;
//	light_ptr->set_direction(0, 1, 0);      // straight down
//	light_ptr->scale_radiance(7.5);   
//	light_ptr->set_shadows(false);
//	add_light(light_ptr);
//	
//	
//	// nested spheres
//	
//	MyRGBColor glass_color(0.95, 0.95, 1);  	// faint blue
//	MyRGBColor diamond_color(1, 1, 0.8);  	// lemon
//	MyRGBColor water_color(1, 0.5, 1);  		// mauve
//	
//	Point3D center(0.5, 0, 0.5);  			// common centre
//	
//	
//	// outer sphere - glass
//	
//	Dielectric* glass_ptr = new Dielectric;
//	glass_ptr->set_ks(0.1);   
//	glass_ptr->set_exp(2000.0);
//	glass_ptr->set_eta_in(1.5); 			// water
//	glass_ptr->set_eta_out(1.0);			// air
//	glass_ptr->set_cf_in(glass_color);
//	glass_ptr->set_cf_out(white);
//	
//	Sphere* sphere_ptr1 = new Sphere(center, 3.5);
//	sphere_ptr1->set_material(glass_ptr);
//	add_object(sphere_ptr1);
//	
//	
//	// middle sphere - diamond
//	
//	Dielectric* diamond_ptr = new Dielectric;
//	diamond_ptr->set_ks(0.1);    
//	diamond_ptr->set_exp(2000.0);
//	diamond_ptr->set_eta_in(2.42); 			// diamond
//	diamond_ptr->set_eta_out(1.5);			// glass
//	diamond_ptr->set_cf_in(diamond_color);
//	diamond_ptr->set_cf_out(glass_color);
//	
//	Sphere* sphere_ptr2 = new Sphere(center, 2.0);
//	sphere_ptr2->set_material(diamond_ptr);
//	add_object(sphere_ptr2);
//	
//	
//	// inner sphere - water
//	
//	Dielectric* water_ptr = new Dielectric;
//	water_ptr->set_ks(0.1);  
//	water_ptr->set_exp(2000.0);
//	water_ptr->set_eta_in(1.33); 			// water
//	water_ptr->set_eta_out(2.42); 			// diamond
//	water_ptr->set_cf_in(water_color);
//	water_ptr->set_cf_out(diamond_color);
//	
//	Sphere* sphere_ptr3 = new Sphere(center, 0.6);
//	sphere_ptr3->set_material(water_ptr);
//	add_object(sphere_ptr3);
//	
//	
//	// ground plane
//	
////	Checker3D* checker_ptr = new Checker3D;
////	checker_ptr->set_size(2.0);
////	checker_ptr->set_color1(0.25); 
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
//	Plane* plane_ptr = new Plane(Point3D(0, -6.5, 0), Normal(0, 1, 0));  
//	plane_ptr->set_material(white_matte_ptr);
//	add_object(plane_ptr);
//}


// This builds the scene for Figure 28.22

// I used the following technique to get the filter color for the glass blocks.
// I placed a glass shelf next to a window, with an edge facing the window,
// photographed the opposite edge with a digital camera, opened the image in 
// Photoshop, and extracted the color. It's not accurate, but gave a reasonable
// color.

// This image takes a huge amount of time to render because of the high recursion depth.
// Try it initially with max_depth = 3 and one sample per pixel.

//void 												
//World::build(void) {
//	int num_samples = 100; //10
//	
//	vp.set_hres(1680);	  		
//	vp.set_vres(1050);
//	vp.set_samples(num_samples);    
//	vp.set_max_depth(15); //15
//	
//	tracer_ptr = new Whitted(this);
//	//tracer_ptr = new PathTrace(this);
//	
//	background_color = MyRGBColor(0.75);  
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(1.0);
//	set_ambient_light(ambient_ptr);	
//	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(10, 12, 20); 
//	pinhole_ptr->set_lookat(-3.75, 3, 0);     
//	pinhole_ptr->set_view_distance(1500.0);	
//	pinhole_ptr->set_zoom(3.0);
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr);
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(20, 25, -20);  
//	light_ptr1->scale_radiance(3.0);  
//	light_ptr1->set_shadows(true);
//	add_light(light_ptr1);
//	
//	
//	float c = 1.75;  // this allows us to adjust the filter color without changing the hue
//	MyRGBColor glass_color(0.27*c, 0.49*c, 0.42*c);  
//	
//	
//	Dielectric* glass_ptr = new Dielectric;
//	glass_ptr->set_eta_in(1.50);		// glass
//	glass_ptr->set_eta_out(1.0);		// air
//	glass_ptr->set_cf_in(glass_color);
//	glass_ptr->set_cf_out(white); 
//	
//	double 	thickness 	= 0.25;
//	double 	height 		= 4.0;
//	double 	delta 		= 1.0;			// length change of each box
//	
//	int 	num_boxes 	= 10;
//	double 	x_min 		= -10.0;		// where the boxes start in the x direction
//	double 	gap 		= 0.5;   		// gap between the boxes
//	
//	for (int j = 0; j < num_boxes; j++) {
//		double length = thickness + j * delta;
//		Point3D p0(x_min + j * (thickness + gap), 0.0, -length);
//		Point3D p1(x_min + j * (thickness + gap) + thickness, height, 0.0);
//		
//		Box* box_ptr = new Box(p0, p1);     
//		box_ptr->set_material(glass_ptr);
//		add_object(box_ptr);
//	}
//	
//	
//	// plane
//	
//	Matte* matte_ptr = new Matte;		
//	matte_ptr->set_ka(0.5);
//	matte_ptr->set_kd(0.65);
//	matte_ptr->set_cd(0.75);
//	
//	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
//	plane_ptr->set_material(matte_ptr);
//	add_object(plane_ptr);
//}



// This builds the scene for Figure 28.38(c)

// This takes a long time to render

//void 												
//World::build(void) {
//	int num_samples = 9;
//	
//	vp.set_hres(400);	  		
//	vp.set_vres(400);
//	vp.set_samples(num_samples);
//	vp.set_max_depth(10);
//	
//	background_color = MyRGBColor(0.5);
//	
//	tracer_ptr = new Whitted(this);
//	//tracer_ptr = new PathTrace(this);
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(1.0);
//	set_ambient_light(ambient_ptr);
//	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
////	pinhole_ptr->set_eye(2.5, 0, 5); 
////	pinhole_ptr->set_lookat(0, 1, 0); 
////	pinhole_ptr->set_view_distance(1000.0);
//	pinhole_ptr->set_eye(5, 6, 10); 
//	pinhole_ptr->set_lookat(0, 1, 0); 
//	pinhole_ptr->set_view_distance(2000.0);	
//	pinhole_ptr->set_zoom(2.0/3.0);
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr);
//	
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(40, 50, 30); 
//	light_ptr1->scale_radiance(6.0);    
//	light_ptr1->set_shadows(true);
//	add_light(light_ptr1);
//	
//	
//	// materials for the glass of water
//	
//	// glass-air boundary
//	
//	MyRGBColor glass_color(0.65, 1, 0.75);   
//	MyRGBColor water_color(1, 0.25, 1);       
//	
//	Dielectric* glass_ptr = new Dielectric;
//	glass_ptr->set_eta_in(1.50);			// glass  
//	glass_ptr->set_eta_out(1.0);			// air
//	glass_ptr->set_cf_in(glass_color);
//	glass_ptr->set_cf_out(white);  
//	
//	// water-air boundary
//	
//	Dielectric* water_ptr = new Dielectric;
//	water_ptr->set_eta_in(1.33);			// water
//	water_ptr->set_eta_out(1.0);			// air
//	water_ptr->set_cf_in(water_color);
//	water_ptr->set_cf_out(white);
//	
//	// water-glass boundary
//	
//	Dielectric* dielectric_ptr = new Dielectric;
//	dielectric_ptr->set_eta_in(1.33); 		// water
//	dielectric_ptr->set_eta_out(1.50); 		// glass
//	dielectric_ptr->set_cf_in(water_color);
//	dielectric_ptr->set_cf_out(glass_color);
//	
//	
//	// Define the GlassOfWater object
//	// The parameters below are the default values, but using the constructor that
//	// takes these as arguments makes it easier to experiment with different values
//	
//	double height 			= 2.0;
//	double inner_radius 	= 0.9;
//	double wall_thickness 	= 0.1;  
//	double base_thickness 	= 0.3;
//	double water_height 	= 1.5;
//	double meniscus_radius 	= 0.1;
//	
//	GlassOfWater* glass_of_water_ptr = new GlassOfWater(height,
//														inner_radius,
//														wall_thickness,  
//														base_thickness,
//														water_height,
//														meniscus_radius);
//	
//	glass_of_water_ptr->set_glass_air_material(glass_ptr);
//	glass_of_water_ptr->set_water_air_material(water_ptr);
//	glass_of_water_ptr->set_water_glass_material(dielectric_ptr);
//	add_object(glass_of_water_ptr);
//	
//	
//	// define the straw
//	
//	Matte* matte_ptr = new Matte;
//	matte_ptr->set_cd(1, 1, 0);  			
//	matte_ptr->set_ka(0.25);	
//	matte_ptr->set_kd(0.65);
//	matte_ptr->set_shadows(false);  // there are no shadows cast on the straw
//	
//	Instance* straw_ptr = new Instance(new OpenCylinder(-1.2, 1.7, 0.05));
//	//straw_ptr->set_shadows(false);
//	straw_ptr->set_material(matte_ptr);
//	straw_ptr->rotate_z(40);
//	straw_ptr->translate(0, 1.25, 0);
//	add_object(straw_ptr);
//	
//	// ground plane
//	
////	Checker3D* checker_ptr = new Checker3D;
////	checker_ptr->set_size(0.5); 
////	checker_ptr->set_color1(0.75); 
////	checker_ptr->set_color2(white);
////	
////	SV_Matte* sv_matte_ptr = new SV_Matte;		
////	sv_matte_ptr->set_ka(0.5);
////	sv_matte_ptr->set_kd(0.75);
////	sv_matte_ptr->set_cd(checker_ptr);
//	
//	Matte* matte_ptr1 = new Matte;		
//	matte_ptr1->set_ka(0.5);
//	matte_ptr1->set_kd(0.75);
//	matte_ptr1->set_cd(white);
//	
//	Plane* plane_ptr = new Plane(Point3D(0, -0.01, 0), Normal(0, 1, 0));
//	plane_ptr->set_material(matte_ptr1);
//	add_object(plane_ptr);
//}
//
//
//
//
