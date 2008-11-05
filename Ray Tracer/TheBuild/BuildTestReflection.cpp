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
#include "SV_Matte.h"
#include "Image.h"
#include "ImageTexture.h"
#include "LightProbe.h"




void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(1680);//400);			
	vp.set_vres(1050);//400);  
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	vp.set_max_depth(10);
	
	tracer_ptr = new Whitted(this);		
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(400, 125, 500);   
	pinhole_ptr->set_lookat(0.0, -50, 0);
	pinhole_ptr->set_view_distance(550);
	pinhole_ptr->set_zoom(1.9);//2.0/3.0);
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	Compound* spheres = new Compound;
	
	float  kr = 0.9;
	double radius = 100.0;
	
	// reflective sphere centered at the origin
	
	Reflective* reflective_ptrc = new Reflective;			
	reflective_ptrc->set_ka(0.0); 
	reflective_ptrc->set_kd(0.0);
	reflective_ptrc->set_ks(0.0);
	reflective_ptrc->set_cd(0.0);
	reflective_ptrc->set_kr(kr);
	reflective_ptrc->set_cr(0.65, 0.75, 1.0);   // pale blue
	
	Sphere* sphere_ptr = new Sphere(Point3D(0.0), radius);
	sphere_ptr->set_shadows(false);
	sphere_ptr->set_material(reflective_ptrc);
	spheres->add_object(sphere_ptr);
	
	// define materials for the surrounding spheres
	
	vector<Reflective*> materials;	
	
	Reflective* reflective_ptr0 = new Reflective;			
	reflective_ptr0->set_ka(0.0); 
	reflective_ptr0->set_kd(0.0);
	reflective_ptr0->set_ks(0.0);
	reflective_ptr0->set_cd(0.0);
	reflective_ptr0->set_kr(kr);
	reflective_ptr0->set_cr(0.5, 1.0, 0.5);  // light green
	materials.push_back(reflective_ptr0);
	
	Reflective* reflective_ptr1 = new Reflective;			
	reflective_ptr1->set_ka(0.0); 
	reflective_ptr1->set_kd(0.0);
	reflective_ptr1->set_ks(0.0);
	reflective_ptr1->set_cd(0.0);
	reflective_ptr1->set_kr(kr);
	reflective_ptr1->set_cr(0.4, 1.0, 1.0);  // cyan
	materials.push_back(reflective_ptr1);
	
	Reflective* reflective_ptr2 = new Reflective;			
	reflective_ptr2->set_ka(0.0); 
	reflective_ptr2->set_kd(0.0);
	reflective_ptr2->set_ks(0.0);
	reflective_ptr2->set_cd(0.0);
	reflective_ptr2->set_kr(kr);
	reflective_ptr2->set_cr(1.0, 1.0, 0.4);  // lemon
	materials.push_back(reflective_ptr2);
	
	Reflective* reflective_ptr3 = new Reflective;			
	reflective_ptr3->set_ka(0.0); 
	reflective_ptr3->set_kd(0.0);
	reflective_ptr3->set_ks(0.0);
	reflective_ptr3->set_cd(0.0);
	reflective_ptr3->set_kr(kr);
	reflective_ptr3->set_cr(1.0, 0.5, 1.0);  // mauve
	materials.push_back(reflective_ptr3);
	
	Reflective* reflective_ptr4 = new Reflective;			
	reflective_ptr4->set_ka(0.0); 
	reflective_ptr4->set_kd(0.0);
	reflective_ptr4->set_ks(0.0);
	reflective_ptr4->set_cd(0.0);
	reflective_ptr4->set_kr(kr);
	reflective_ptr4->set_cr(1.0, 0.75, 0.25);  // orange
	materials.push_back(reflective_ptr4);
	
	Reflective* reflective_ptr5 = new Reflective;			
	reflective_ptr5->set_ka(0.0); 
	reflective_ptr5->set_kd(0.0);
	reflective_ptr5->set_ks(0.0);
	reflective_ptr5->set_cd(0.0);
	reflective_ptr5->set_kr(kr);
	reflective_ptr5->set_cr(0.5, 0.5, 1.0);  // blue
	materials.push_back(reflective_ptr5);
	
	
	// define ring of reflective spheres that just touch the center sphere
	// these are initially in the (x, z) plane
	
	float  num_spheres = 6;
	double theta = 0.0;
	double delta_theta = 2.0 * PI / num_spheres;
	
	for (int j = 0; j < num_spheres; j++) {
		Point3D center((2.0 * radius) * sin(theta), 0.0, (2.0 * radius) * cos(theta));
		Sphere* sphere_ptr = new Sphere(center, radius);
		sphere_ptr->set_material(materials[j]);
		spheres->add_object(sphere_ptr);
		theta += delta_theta;
	}
	
	// now rotate the spheres
	
	Instance* rotated_spheres_ptr = new Instance(spheres);
	rotated_spheres_ptr->rotate_x(40.0);
	rotated_spheres_ptr->rotate_z(-40.0);
	add_object(rotated_spheres_ptr);
	
	
	// large sphere with Uffizi image
	
	Image* image_ptr = new Image;
	//	image_ptr->read_ppm_file("uffizi_probe_small.ppm");   // for testing 
	image_ptr->read_ppm_file("../../TextureFiles/ppm/uffizi_probe_large.ppm");   // for production
	
	LightProbe* light_probe_ptr = new LightProbe;     	
	//light_probe_ptr->set_map_type(panoramic);
	
	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
	texture_ptr->set_mapping(light_probe_ptr);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;
	sv_matte_ptr->set_ka(1.0);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(texture_ptr);
	
	Sphere* unit_sphere_ptr = new Sphere;
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* sphere_ptr1 = new Instance(unit_sphere_ptr); 
	sphere_ptr1->set_material(sv_matte_ptr);
	sphere_ptr1->transform_texture(true);
	sphere_ptr1->scale(1000000.0);
	add_object(sphere_ptr1);
}



//void 												
//World::build(void) {
//	int num_samples = 16;
//	
//	vp.set_hres(600);			
//	vp.set_vres(600); 
//	vp.set_samples(num_samples);
//	vp.set_max_depth(1);
//	
//	tracer_ptr = new Whitted(this);	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(-150, 75, 500); 
//	pinhole_ptr->set_lookat(-6, 50, 0);
//	pinhole_ptr->set_view_distance(3000);	
//	pinhole_ptr->compute_uvw(); 
//	set_camera(pinhole_ptr);
//	
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(250, 500, 250); 
//	light_ptr1->scale_radiance(3.0); 
//	light_ptr1->set_shadows(true); 
//    add_light(light_ptr1);
//    
//    
//    // sphere
//	
//	Reflective* reflective_ptr = new Reflective;			
//	reflective_ptr->set_ka(0.0); 
//	reflective_ptr->set_kd(0.0);
//	reflective_ptr->set_ks(0.0);
//	reflective_ptr->set_cd(black);
//	reflective_ptr->set_kr(0.9);
//	reflective_ptr->set_cr(1.0, 1.0, 0.3);  // lemon
//	
//	Sphere* sphere_ptr = new Sphere(Point3D(-6, 55, 0), 40);
//	sphere_ptr->set_material(reflective_ptr);
//	add_object(sphere_ptr);
//	
//	
//	//cylinder
//	
//	Matte* matte_ptr = new Matte;		
//	matte_ptr->set_ka(0.15);
//	matte_ptr->set_kd(0.75);
//	matte_ptr->set_cd(0.5, 1.0, 0.5);   // green
//	
//	double bottom = -100.0;
//	double top = 15.0;       
//	double radius = 30.0;
//	Instance* cylinder_ptr = new Instance(new SolidCylinder(bottom, top, radius));
//	cylinder_ptr->translate(-6, 0, 0);
//	cylinder_ptr->set_material(matte_ptr);
//	add_object(cylinder_ptr);
//	
//	
//	// large sphere with Uffizi image
//	
//	Image* image_ptr = new Image;
//	//image_ptr->read_ppm_file("../../TextureFiles/ppm/uffizi_probe_small.ppm");   // for testing 
//		image_ptr->read_ppm_file("../../TextureFiles/ppm/uffizi_probe_large.ppm");   // for production
//	
//	LightProbe* light_probe_ptr = new LightProbe;   
//	light_probe_ptr->set_map_type(panoramic);  		
//	
//	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
//	texture_ptr->set_mapping(light_probe_ptr);
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;
//	sv_matte_ptr->set_ka(1.0);
//	sv_matte_ptr->set_kd(0.85);
//	sv_matte_ptr->set_cd(texture_ptr);
//	
//	Sphere* unit_sphere_ptr = new Sphere;
//	unit_sphere_ptr->set_shadows(false);	
//	
//	Instance* large_sphere_ptr = new Instance(unit_sphere_ptr); 
//	large_sphere_ptr->transform_texture(true);
//	large_sphere_ptr->set_material(sv_matte_ptr);
//	large_sphere_ptr->scale(1000000.0);
//	add_object(large_sphere_ptr);
//}






// bunny

//void 												
//World::build(void) {
//	int num_samples = 16;
//	
//	vp.set_hres(1680);//400);			
//	vp.set_vres(1050);//400); 
//	vp.set_samples(num_samples);
//	vp.set_max_depth(3);
//	
//	tracer_ptr = new Whitted(this);	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(-150, 75, 500); 
//	pinhole_ptr->set_lookat(-6, 50, 0);
//	pinhole_ptr->set_view_distance(3000);
//	pinhole_ptr->set_zoom(2.1);//2.0/3.0);
//	pinhole_ptr->compute_uvw(); 
//	set_camera(pinhole_ptr);
//	
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(250, 500, 250); 
//	light_ptr1->scale_radiance(3.0); 
//	light_ptr1->set_shadows(true); 
//    add_light(light_ptr1);
//    
//	
//	// bunny
//	
//	float exp1 = 100000;
//	GlossyReflector* reflective_ptr1 = new GlossyReflector;	
//	reflective_ptr1->set_samples(num_samples, exp1);
//	reflective_ptr1->set_ka(0.0); 
//	reflective_ptr1->set_kd(0.0);
//	reflective_ptr1->set_cd(1.0);  // light green
//	reflective_ptr1->set_ks(0.0);
//	reflective_ptr1->set_exp_s(exp1);
//	reflective_ptr1->set_exponent(exp1);
//	reflective_ptr1->set_kr(0.9);
//	reflective_ptr1->set_cr(white); 			// default color
//	
//	float exp = 1.0;  		// for Figure 25.30(a)
//	//	float exp = 10.0;  		// for Figure 25.30(b)
//	//	float exp = 100.0;  	// for Figure 25.30(c)
//	//	float exp = 1000.0;  	// for Figure 25.30(d)
//	//	float exp = 10000.0;  	// for Figure 25.30(e)
//	//	float exp = 100000.0;  	// for Figure 25.30(f)
//	
//	GlossyReflector* glossy_ptr = new GlossyReflector;
//	glossy_ptr->set_samples(num_samples, exp);			
//	glossy_ptr->set_ka(0.25); 
//	glossy_ptr->set_kd(0.5);
//	glossy_ptr->set_ks(0.0);
//	glossy_ptr->set_exp(exp);
//	glossy_ptr->set_cd(1.0, 1.0, 0.3);
//	glossy_ptr->set_kr(0.9);
//	glossy_ptr->set_exponent(exp);
//	glossy_ptr->set_cr(1.0, 1.0, 0.3);  // lemon
//	
//	Reflective* reflective_ptr = new Reflective;			
//	reflective_ptr->set_ka(0.0); 
//	reflective_ptr->set_kd(0.0);
//	reflective_ptr->set_ks(0.0);
//	reflective_ptr->set_cd(0.0);
//	reflective_ptr->set_kr(0.9);
//	reflective_ptr->set_cr(0.5, 1.0, 0.5);  // light green
//	
//	Mesh* mesh_ptr = new Mesh;
//	//char* file_name = "../../PLYFiles/Bunny4K.ply";   		// Figure 24.31(a) & (b)
////	char* file_name = "../../PLYFiles/Bunny10K.ply";   		// Figure 24.31(a) & (b)
//	char* file_name = "../../PLYFiles/Bunny69K.ply"; 		// Figure 24.31(c) & (d)
//	
//	Grid* grid_ptr = new Grid(mesh_ptr);
//	//	grid_ptr->read_flat_triangles(file_name);		// Figure 24.31(a) & (c)
//	grid_ptr->read_smooth_triangles(file_name);		// Figure 24.31(b) & (d)
//	grid_ptr->setup_cells();
//	
//	Instance* bunny_ptr1 = new Instance(grid_ptr);
//	bunny_ptr1->set_material(reflective_ptr);
//	bunny_ptr1->scale(500.0);
//	add_object(bunny_ptr1);
//	
//	
//	//cylinder
//	
//	Matte* matte_ptr = new Matte;		
//	matte_ptr->set_ka(0.15);
//	matte_ptr->set_kd(0.75);
//	matte_ptr->set_cd(1.0, 0.7, 0);   // orange
//	
//	double bottom = -100.0;
//	double top = 15.0;       
//	double radius = 30.0;
//	Instance* cylinder_ptr = new Instance(new SolidCylinder(bottom, top, radius));
//	cylinder_ptr->translate(-6, 0, 0);
//	cylinder_ptr->set_material(matte_ptr);
//	add_object(cylinder_ptr);
//	
//	
//	// large sphere with Uffizi image
//	
//	Image* image_ptr = new Image;
//	image_ptr->read_ppm_file("../../TextureFiles/ppm/uffizi_probe_small.ppm");   // for testing 
//	//	image_ptr->read_ppm_file("uffizi_probe_large.ppm");   // for production
//	
//	LightProbe* light_probe_ptr = new LightProbe;   
//	light_probe_ptr->set_map_type(panoramic);  		
//	
//	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
//	texture_ptr->set_mapping(light_probe_ptr);
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;
//	sv_matte_ptr->set_ka(1.0);
//	sv_matte_ptr->set_kd(0.85);
//	sv_matte_ptr->set_cd(texture_ptr);
//	
//	Sphere* unit_sphere_ptr = new Sphere;
//	unit_sphere_ptr->set_shadows(false);	
//	
//	Instance* large_sphere_ptr = new Instance(unit_sphere_ptr); 
//	large_sphere_ptr->set_material(sv_matte_ptr);
//	large_sphere_ptr->transform_texture(true);
//	large_sphere_ptr->scale(1000000.0);
//	add_object(large_sphere_ptr);
//}

// Glossy sphere

//void 												
//World::build(void) {
//	int num_samples = 25;
//	
//	vp.set_hres(600);			
//	vp.set_vres(600); 
//	vp.set_samples(num_samples);
//	vp.set_max_depth(3);
//	
//	tracer_ptr = new AreaLighting(this);	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(-150, 75, 500); 
//	pinhole_ptr->set_lookat(-6, 50, 0);
//	pinhole_ptr->set_view_distance(3000);	
//	pinhole_ptr->compute_uvw(); 
//	set_camera(pinhole_ptr);
//	
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(250, 500, 250); 
//	light_ptr1->scale_radiance(3.0);   
//	light_ptr1->set_shadows(true); 
//    add_light(light_ptr1);
//	
//	//float exp = 1.0;  		// for Figure 25.30(a)
//	//	float exp = 10.0;  		// for Figure 25.30(b)
//	//	float exp = 100.0;  	// for Figure 25.30(c)
//	//float exp = 1000.0;  	// for Figure 25.30(d)
//	//	float exp = 10000.0;  	// for Figure 25.30(e)
//		float exp = 100000.0;  	// for Figure 25.30(f)
//	
//	GlossyReflector* glossy_ptr = new GlossyReflector;
//	glossy_ptr->set_samples(num_samples, exp);			
//	glossy_ptr->set_ka(0.0); 
//	glossy_ptr->set_kd(0.0);
//	glossy_ptr->set_ks(0.0);
//	glossy_ptr->set_exp(exp);
//	glossy_ptr->set_cd(0.5, 1.0, 0.5);
//	glossy_ptr->set_kr(0.9);
//	glossy_ptr->set_exponent(exp);
//	glossy_ptr->set_cr(0.5, 1.0, 0.5);  // lemon
//	
////	Sphere* sphere_ptr1 = new Sphere(Point3D(-6, 55, 0), 40);
////	sphere_ptr1->set_material(glossy_ptr);
////	sphere_ptr1->set_shadows(true);
////	add_object(sphere_ptr1);
//	
//	Mesh* mesh_ptr = new Mesh;
//	char* file_name = "../../PLYFiles/Bunny4K.ply";   		// Figure 24.31(a) & (b)
//	//char* file_name = "../../PLYFiles/Bunny10K.ply";   		// Figure 24.31(a) & (b)
////	const char* file_name = "Bunny69K.ply"; 		// Figure 24.31(c) & (d)
//	
//	Grid* grid_ptr = new Grid(mesh_ptr);
//	//	grid_ptr->read_flat_triangles(file_name);		// Figure 24.31(a) & (c)
//	grid_ptr->read_smooth_triangles(file_name);		// Figure 24.31(b) & (d)
//	grid_ptr->setup_cells();
//	
//	Instance* bunny_ptr1 = new Instance(grid_ptr);
//	bunny_ptr1->set_material(glossy_ptr);
//	bunny_ptr1->scale(500.0);
//	add_object(bunny_ptr1);
//	
//	//cylinder
//	
//	Matte* matte_ptr = new Matte;		
//	matte_ptr->set_ka(0.15);
//	matte_ptr->set_kd(0.75);
//	matte_ptr->set_cd(1.0, 0.7, 0);   // orange
//	matte_ptr->set_shadows(true);
//
//	double bottom = -100.0;
//	double top = 15.0;       
//	double radius = 30.0;
//	Instance* cylinder_ptr = new Instance(new SolidCylinder(bottom, top, radius));
//	cylinder_ptr->translate(-6, 0, 0);
//	cylinder_ptr->set_material(matte_ptr);
//	add_object(cylinder_ptr);
//	
////	Matte* matte_ptr = new Matte;		
////	matte_ptr->set_ka(0.15);
////	matte_ptr->set_kd(0.75);
////	matte_ptr->set_cd(0.5, 1.0, 0.5);   // green
//	
////	double bottom = -100;
////	double top = 15;       
////	double radius = 30;
////	Instance* cylinder_ptr = new Instance(new SolidCylinder(bottom, top, radius));
////	cylinder_ptr->translate(-6, 0, 0);
////	cylinder_ptr->set_material(matte_ptr);
////	add_object(cylinder_ptr);
//	
//	
//	Image* image_ptr = new Image;
//	image_ptr->read_ppm_file("../../TextureFiles/ppm/uffizi_probe_small.ppm");  // for testing 
//	//	image_ptr->read_ppm_file("uffizi_probe_large.ppm");  // for production
//	
//	
//	LightProbe* light_probe_ptr = new LightProbe; 
//	light_probe_ptr->set_map_type(panoramic);   		
//	
//	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
//	image_texture_ptr->set_mapping(light_probe_ptr);
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;		
//	sv_matte_ptr->set_ka(1);
//	sv_matte_ptr->set_kd(0.85);  
//	sv_matte_ptr->set_cd(image_texture_ptr);
//	
//	Sphere* unit_sphere_ptr = new Sphere;
//	unit_sphere_ptr->set_shadows(false);	
//	
//	Instance* sphere_ptr2 = new Instance(unit_sphere_ptr); 
//	sphere_ptr2->transform_texture(true);
//	sphere_ptr2->scale(1000000.0);
//	sphere_ptr2->set_material(sv_matte_ptr);
//	add_object(sphere_ptr2);
//}






//
//// This builds the scene for Figure 24.6
//
//void 												
//World::build(void) {
//	int num_samples = 100;
//	
//	vp.set_hres(400); 
//	vp.set_vres(400);
//	vp.set_samples(num_samples);
//	//	vp.set_max_depth(0);			// for Figure 24.6(a)
//	vp.set_max_depth(10);			// for Figure 24.6(b)
//	
//	//tracer_ptr = new AreaLighting(this);
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
//	bool use_grid = true;
//	Grid* grid_ptr = NULL;
//	
//	if (use_grid) {
//		grid_ptr = new Grid;
//		set_rand_seed(15);
//	}
//	
//	// yellow-green reflective sphere
//	
//	Reflective* reflective_ptr1 = new Reflective;			
//	reflective_ptr1->set_ka(0.25); 
//	reflective_ptr1->set_kd(0.5);
//	reflective_ptr1->set_cd(0.75, 0.75, 0);    	// yellow
//	reflective_ptr1->set_ks(0.15);
//	reflective_ptr1->set_exp(100.0);
//	reflective_ptr1->set_kr(0.75);
//	reflective_ptr1->set_cr(white); 			// default color
//	
////	float exp1 = 100;
////	GlossyReflector* reflective_ptr1 = new GlossyReflector;	
////	reflective_ptr1->set_samples(num_samples, exp1);
////	reflective_ptr1->set_ka(0.25); 
////	reflective_ptr1->set_kd(0.5);
////	reflective_ptr1->set_cd(0.75, 0.75, 0);    	// yellow
////	reflective_ptr1->set_ks(0.2);
////	reflective_ptr1->set_exp_s(exp1);
////	reflective_ptr1->set_exponent(exp1);
////	reflective_ptr1->set_kr(0.75);
////	reflective_ptr1->set_cr(white); 			// default color
//	
//	float radius = 23.0;
//	Sphere* sphere_ptr1 = new Sphere(Point3D(38, radius, -25), radius); 
//	sphere_ptr1->set_material(reflective_ptr1);
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr1);
//	else
//		add_object(sphere_ptr1);
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
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr2);
//	else
//		add_object(sphere_ptr2);
//	
//	
//	// sphere on top of box
//	
//	Reflective* reflective_ptr2 = new Reflective;			
//	reflective_ptr2->set_ka(0.35); 
//	reflective_ptr2->set_kd(0.75);
//	reflective_ptr2->set_cd(black); 
//	reflective_ptr2->set_ks(0.0);		// default value
//	reflective_ptr2->set_exp(1.0);		// default value, but irrelevant in this case
//	reflective_ptr2->set_kr(0.75);
//	reflective_ptr2->set_cr(white); 
//	
////	float exp2 = 1.0;
////	GlossyReflector* reflective_ptr2 = new GlossyReflector;		
////	reflective_ptr2->set_samples(num_samples, exp2);
////	reflective_ptr2->set_ka(0.35); 
////	reflective_ptr2->set_kd(0.75);
////	reflective_ptr2->set_c(black); 
////	reflective_ptr2->set_ks(0.0);		// default value
////	reflective_ptr2->set_exp_s(exp2);		// default value, but irrelevant in this case
////	reflective_ptr2->set_exponent(exp2);
////	reflective_ptr2->set_kr(0.75);
////	reflective_ptr2->set_cr(white); 
//	
//	Sphere* sphere_ptr3 = new Sphere(Point3D(-30, 59, 35), 20);
//	sphere_ptr3->set_material(reflective_ptr2);     
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr3);
//	else
//		add_object(sphere_ptr3);
//	
//	
//	// cylinder
//	
//	Reflective* reflective_ptr3 = new Reflective;			
//	reflective_ptr3->set_ka(0.35); 
//	reflective_ptr3->set_kd(0.5);
//	reflective_ptr3->set_cd(0, 0.5, 0.75);   // cyan
//	reflective_ptr3->set_ks(0.2);
//	reflective_ptr3->set_exp(100.0);
//	reflective_ptr3->set_kr(0.75);
//	reflective_ptr3->set_cr(white);
//	
////	float exp3 = 100;
////	GlossyReflector* reflective_ptr3 = new GlossyReflector;
////	reflective_ptr3->set_samples(num_samples, exp3);
////	reflective_ptr3->set_ka(0.35); 
////	reflective_ptr3->set_kd(0.5);
////	reflective_ptr3->set_cd(0, 0.5, 0.75);   // cyan
////	reflective_ptr3->set_ks(0.2);
////	reflective_ptr3->set_exp_s(exp3);
////	reflective_ptr3->set_exponent(exp3);
////	reflective_ptr3->set_kr(0.75);
////	reflective_ptr3->set_cr(white);
//	
//	double bottom 			= 0.0;
//	double top 				= 85;   
//	double cylinder_radius	= 22;
//	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, cylinder_radius);
//	cylinder_ptr->set_material(reflective_ptr3);
//	if (use_grid)
//		grid_ptr->add_object(cylinder_ptr);
//	else
//		add_object(cylinder_ptr);
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
//	if (use_grid)
//		grid_ptr->add_object(box_ptr);
//	else
//		add_object(box_ptr);
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
//	
//	// HAS TO BE LAST
//	if (use_grid) {
//		grid_ptr->setup_cells();
//		add_object(grid_ptr);
//	}
//}