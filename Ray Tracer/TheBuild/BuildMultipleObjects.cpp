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

void 												
World::build(void) {
	int num_samples = 5;
	
	vp.set_hres(400);//1680
	vp.set_vres(400);//1050
	//vp.set_sampler(new Jittered(num_samples));
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples);
	
	
	// PinholeCamera
	//Pinhole* camera_ptr = new Pinhole(Point3D(300, 400, 500), Point3D(0, 0, -50), Vector3D(0, 1, 0), 400, 1.0);
	//Pinhole* camera_ptr = new Pinhole(Point3D(-1000, 2000, -500), Point3D(0, -100, 0), Vector3D(0, 1, 0), 250, 1.0);
	//Pinhole* camera_ptr = new Pinhole(Point3D(0, 0, 500), Point3D(0, 0, 0), Vector3D(0, 1, 0), 500, 1.0);
	//Pinhole* camera_ptr = new Pinhole(Point3D(0, 1000, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 500, 1.0);
	//Pinhole* camera_ptr = new Pinhole(Point3D(0, 50, 600), Point3D(0, 6, -50), Vector3D(0, 1, 0), 500, 1.0);
	
	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(Point3D(0, 0, 500)); 
	camera_ptr->set_lookat(Point3D(0.0));
	camera_ptr->set_d(600.0);
	//camera_ptr->compute_uvw();   
	camera_ptr->set_zoom(1.2);//3 or 3.2
	set_camera(camera_ptr);
	camera_ptr->compute_uvw();
	set_camera(camera_ptr);
	
	// ThinLens camera
	//ThinLens(const Point3D e, const Point3D l, const Vector3D u, float lr, float distance, float focal, float z)
	//ThinLens* camera_ptr = new ThinLens(Point3D(0, 6, 50), Point3D(0, 6, 0), Vector3D(0, -1, 0), 1.0, 40.0, 74);
	//ThinLens* camera_ptr = new ThinLens(Point3D(0, 6, 100), Point3D(0, 6, 0), Vector3D(0, 1, 0), 3.0, 40.0, 74);	// GOOD
	//camera_ptr->set_sampler(vp.sampler_ptr);
	
	// FishEye camera
	//FishEye* camera_ptr = new FishEye(Point3D(0, 6, -150), Point3D(0, 0, -50), Vector3D(0, 1, 0), 120.0);
	//FishEye* camera_ptr = new FishEye(Point3D(5, 1000, -1), Point3D(0, 0, 0), Vector3D(0, 1, 0), 120.0);
	//set_camera(camera_ptr);
	
	// Spherical camera
	//Spherical* camera_ptr = new Spherical(Point3D(0, 6, 150), Point3D(0, 0, -50), Vector3D(0, 1, 0), 120.0, 160.0);
	
	// Stereo 
//	float vpd = 50;
//	
//	int pixel_gap = 5;
//	vp.set_image_hres((vp.hres * 2) + pixel_gap);
//	vp.set_image_vres(vp.vres);
//	
//	int x = vp.hres;
//	int y = vp.vres;
//	
//	int z = vp.image_hres;
//	int w = vp.image_vres; 
//	
//	Pinhole* left_camera_ptr = new Pinhole;
//	left_camera_ptr->set_d(vpd);
//	
//	Pinhole* right_camera_ptr = new Pinhole;
//	right_camera_ptr->set_d(vpd);
//	
//	
//
//	
//	//	StereoCamera(const Point3D e, const Point3D l, const Vector3D u, ViewingType view, const int gap, const float beta,
//	//Camera* left, Camera* right);
//		StereoCamera* camera_ptr = new StereoCamera(Point3D(5,0,-100), Point3D(0), Vector3D(0,1,0), pixel_gap, 
//												0.75f, left_camera_ptr, right_camera_ptr);
//	camera_ptr->setup_cameras();
	

	
	tracer_ptr = new AreaLighting(this); 
	
	background_color = MyRGBColor(black);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.0);
	set_ambient_light(ambient_ptr);
	
	
	MultiJittered* emissive_sampler_ptr = new MultiJittered(num_samples);
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(0.1);
	emissive_ptr->set_ce(1.0, 0.5, 0.0);
	
//	p0(-1, 0, -1), 
//	a(0, 0, 2), b(2, 0, 0), 
//	a_len_squared(4.0), 
//	b_len_squared(4.0),
//	normal(0, 1, 0),
	
	Rectangle* rectangle_ptr = new Rectangle(Point3D(100.0,150,150.0), Vector3D(0,0,200),
											Vector3D(200,0,0), Normal(-1.0, -1.0, -1.0));
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(emissive_sampler_ptr);
	rectangle_ptr->set_shadows(false);
	add_object(rectangle_ptr);
	
//	Sphere* light_sphere_ptr = new Sphere(Point3D(150, 0, 150), 100);
//	light_sphere_ptr->set_material(emissive_ptr);
//	light_sphere_ptr->set_sampler(emissive_sampler_ptr);
//	light_sphere_ptr->set_shadows(false);
//	add_object(light_sphere_ptr);
	
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(rectangle_ptr);
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);
	
	
	
	// if I push this to 512, get weird artifacts
	MultiJittered* occluder_sampler_ptr = new MultiJittered(MIN(num_samples, 256));
	
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->scale_radiance(3.0);
	ambient_occluder_ptr->set_color(white);
	ambient_occluder_ptr->set_min_amount(0.25);
	ambient_occluder_ptr->set_sampler(occluder_sampler_ptr);
	set_ambient_light(ambient_occluder_ptr);
	
	
	Emissive* emissive_ptr2 = new Emissive;
	emissive_ptr2->set_ce(1.0, 1.0, 0.5);
	emissive_ptr2->scale_radiance(1.2);
	
	ConcaveSphere* sky_box = new ConcaveSphere;
	sky_box->set_radius(1000000.0);
	sky_box->set_material(emissive_ptr2);
	sky_box->set_shadows(false);
	add_object(sky_box);
	
	EnvironmentLight* env_light = new EnvironmentLight;
	env_light->set_material(emissive_ptr2);
	env_light->set_sampler(new MultiJittered(num_samples));
	env_light->set_shadows(true);
	add_light(env_light);
	
	// Sample ball on plane scene
	
//	Pinhole* camera_ptr = new Pinhole;
//	camera_ptr->set_eye(Point3D(0,5,45));
//	camera_ptr->set_lookat(Point3D(0,1,0));
//	camera_ptr->set_d(5000);
//	camera_ptr->set_zoom(.3);
//	camera_ptr->compute_uvw();
//	set_camera(camera_ptr);
//	
	float ka1 = 0.25;
	float kd1 = 0.75;
	float exp1 = 0.25;
//	
//	MyRGBColor yellow(1, 1, 0);										// yellow
//	
//	Phong* phong_ptr1 = new Phong;   
//	phong_ptr1->set_ka(ka1);	
//	phong_ptr1->set_kd(kd1);
//	phong_ptr1->set_c(yellow);				
//	phong_ptr1->set_exp_s(exp1);
//	
//	Sphere* sphere_ptr001 = new Sphere(Point3D(0,1,0), 1);
//	sphere_ptr001->set_material(phong_ptr1);
//	add_object(sphere_ptr001);
//	
	Phong* phong_ptr002 = new Phong;   
	phong_ptr002->set_ka(ka1);	
	phong_ptr002->set_kd(kd1);
	phong_ptr002->set_c(white);				
	phong_ptr002->set_exp_s(exp1);
	
	Plane* plane_ptr001 = new Plane(Point3D(0,-100,0), Normal(0,1,0));
	plane_ptr001->set_material(phong_ptr002);
	plane_ptr001->set_shadows(true);
	add_object(plane_ptr001);
	
//	Directional* light_ptr1 = new Directional;
//	light_ptr1->set_direction(100, 100, 200);
//	light_ptr1->scale_radiance(.5); 	
//	add_light(light_ptr1);
	
//	PointLight* light_ptr2 = new PointLight;
//	light_ptr2->set_location(100.0, 1.0, 1.0);
//	light_ptr2->scale_radiance(2.0);
//	add_light(light_ptr2);
	
	
	
//	Matte* the_matte1 = new Matte;
//	the_matte1->set_ka(0.25);
//	the_matte1->set_kd(0.75);
//	the_matte1->set_cd(MyRGBColor(1, 0, 0));
	
//	Phong* spec1 = new Phong();
//	spec1->set_ka(0.25);
//	spec1->set_kd(0.75);
//	spec1->set_c(1.0,0, 0);
//	spec1->set_exp_s(5);
//	
//	// use access functions to set centre and radius
//	
//	Sphere* the_sphere = new Sphere;
//	the_sphere->set_center(0, -25, 0);
//	the_sphere->set_radius(80);
//	//the_sphere->set_color(1, 0, 0);  // red
//	the_sphere->set_material(spec1);
//	add_object(the_sphere);

	// use constructor to set centre and radius 
	
//	Matte* the_matte2 = new Matte;
//	the_matte2->set_ka(0.25);
//	the_matte2->set_kd(0.75);
//	the_matte2->set_cd(MyRGBColor(1, 1, 0));
	
//	Phong* spec2 = new Phong();
//	spec2->set_ka(0.25);
//	spec2->set_kd(0.75);
//	spec2->set_c(1.0, 1.0, 0.0);
//	spec2->set_exp_s(5);
//	
//	Sphere* the_other_sphere = new Sphere(Point3D(0, 30, 0), 60);
//	//sphere_ptr->set_color(0, 1, 0);	// yellow
//	the_other_sphere->set_material(spec2);
//	add_object(the_other_sphere);
//	
//	
//	Matte* the_matte3 = new Matte;
//	the_matte3->set_ka(0.25);
//	the_matte3->set_kd(0.75);
//	the_matte3->set_cd(MyRGBColor(0, 0.3, 0));
////	
//	Plane* the_plane = new Plane(Point3D(0), Normal(0, 1, 1));
//	//plane_ptr->set_color(0.0, 0.3, 0.0);	// dark green
//	the_plane->set_material(the_matte3);
//	add_object(the_plane);
	

	
//	Plane* plane_ptr2 = new Plane(Point3D(0), Normal(0, 1, 0));
//	plane_ptr2->set_color(0.0, 0.3, 0.0);	// dark green
//	plane_ptr2->
//	add_object(plane_ptr2);
	
	bool use_grid = true;
	Grid* grid_ptr = NULL;
	
	if (use_grid) {
		grid_ptr = new Grid;
		set_rand_seed(15);
	}
	
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
	
	// Matte material reflection coefficients - common to all materials
	
	float ka = 0.25;
	float kd = 0.75;
	float exp = 0.25;
	
	Phong* phong_ptr1 = new Phong;   
	phong_ptr1->set_ka(ka);	
	phong_ptr1->set_kd(kd);
	phong_ptr1->set_c(yellow);				
	phong_ptr1->set_exp_s(exp);
	Sphere*	sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30); 
	sphere_ptr1->set_material(phong_ptr1);	   							// yellow
	//sphere_ptr1->set_shadows(false);
	if (use_grid)
		grid_ptr->add_object(sphere_ptr1);
	else
		add_object(sphere_ptr1);
	
	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(ka);	
	phong_ptr2->set_kd(kd);
	phong_ptr2->set_c(brown);
	phong_ptr2->set_exp_s(exp);
	Sphere*	sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20); 
	sphere_ptr2->set_material(phong_ptr2);								// brown
	if (use_grid)
		grid_ptr->add_object(sphere_ptr2);
	else
		add_object(sphere_ptr2);
	
	
	Phong* phong_ptr3 = new Phong;
	phong_ptr3->set_ka(ka);	
	phong_ptr3->set_kd(kd);
	phong_ptr3->set_c(darkGreen);
	phong_ptr3->set_exp_s(exp);
	Sphere*	sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17); 
	sphere_ptr3->set_material(phong_ptr3);								// dark green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr3);
	else
		add_object(sphere_ptr3);
	
	Phong* phong_ptr4 = new Phong;
	phong_ptr4->set_ka(ka);	
	phong_ptr4->set_kd(kd);
	phong_ptr4->set_c(orange);
	phong_ptr4->set_exp_s(exp);
	Sphere*	sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20); 
	sphere_ptr4->set_material(phong_ptr4);								// orange
	if (use_grid)
		grid_ptr->add_object(sphere_ptr4);
	else
		add_object(sphere_ptr4);
	
	Phong* phong_ptr5 = new Phong;
	phong_ptr5->set_ka(ka);	
	phong_ptr5->set_kd(kd);
	phong_ptr5->set_c(green);
	phong_ptr5->set_exp_s(exp);
	Sphere*	sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27); 			
	sphere_ptr5->set_material(phong_ptr5);								// green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr5);
	else
		add_object(sphere_ptr5);
	
	Phong* phong_ptr6 = new Phong;
	phong_ptr6->set_ka(ka);	
	phong_ptr6->set_kd(kd);
	phong_ptr6->set_c(lightGreen);
	phong_ptr6->set_exp_s(exp);
	Sphere*	sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25); 
	sphere_ptr6->set_material(phong_ptr6);								// light green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr6);
	else
		add_object(sphere_ptr6);
	
	Phong* phong_ptr7 = new Phong;
	phong_ptr7->set_ka(ka);	
	phong_ptr7->set_kd(kd);
	phong_ptr7->set_c(green);
	phong_ptr7->set_exp_s(exp);
	Sphere*	sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22); 
	sphere_ptr7->set_material(phong_ptr7);   							// green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr7);
	else
		add_object(sphere_ptr7);
	
	Phong* phong_ptr8 = new Phong;
	phong_ptr8->set_ka(ka);	
	phong_ptr8->set_kd(kd);
	phong_ptr8->set_c(brown);
	phong_ptr8->set_exp_s(exp);
	Sphere*	sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);  
	sphere_ptr8->set_material(phong_ptr8);								// brown
	if (use_grid)
		grid_ptr->add_object(sphere_ptr8);
	else
		add_object(sphere_ptr8);
	
	Phong* phong_ptr9 = new Phong;
	phong_ptr9->set_ka(ka);	
	phong_ptr9->set_kd(kd);
	phong_ptr9->set_c(lightGreen);
	phong_ptr9->set_exp_s(exp);
	Sphere*	sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23); 
	sphere_ptr9->set_material(phong_ptr9);								// light green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr9);
	else
		add_object(sphere_ptr9);
	
	Phong* phong_ptr10 = new Phong;
	phong_ptr10->set_ka(ka);	
	phong_ptr10->set_kd(kd);
	phong_ptr10->set_c(darkGreen);	
	phong_ptr10->set_exp_s(exp);
	Sphere*	sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22); 
	sphere_ptr10->set_material(phong_ptr10);     						// dark green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr10);
	else
		add_object(sphere_ptr10);
	
	Phong* phong_ptr11 = new Phong;
	phong_ptr11->set_ka(ka);	
	phong_ptr11->set_kd(kd);
	phong_ptr11->set_c(darkYellow);
	phong_ptr11->set_exp_s(exp);
	Sphere*	sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22); 
	sphere_ptr11->set_material(phong_ptr11);							// dark yellow
	if (use_grid)
		grid_ptr->add_object(sphere_ptr11);
	else
		add_object(sphere_ptr11);
	
	Phong* phong_ptr12 = new Phong;
	phong_ptr12->set_ka(ka);	
	phong_ptr12->set_kd(kd);
	phong_ptr12->set_c(darkYellow);
	phong_ptr12->set_exp_s(exp);
	Sphere*	sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22); 
	sphere_ptr12->set_material(phong_ptr12);							// dark yellow
	if (use_grid)
		grid_ptr->add_object(sphere_ptr12);
	else
		add_object(sphere_ptr12);
	
	Phong* phong_ptr13 = new Phong;
	phong_ptr13->set_ka(ka);	
	phong_ptr13->set_kd(kd);
	phong_ptr13->set_c(darkYellow);		
	phong_ptr13->set_exp_s(exp);
	Sphere*	sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10); 
	sphere_ptr13->set_material(phong_ptr13);
	if (use_grid)
		grid_ptr->add_object(sphere_ptr13);	
	else
		add_object(sphere_ptr13);										// dark yellow (hidden)
	
	Phong* phong_ptr14 = new Phong;
	phong_ptr14->set_ka(ka);	
	phong_ptr14->set_kd(kd);
	phong_ptr14->set_c(darkGreen);	
	phong_ptr14->set_exp_s(exp);
	Sphere*	sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18); 
	sphere_ptr14->set_material(phong_ptr14); 							// dark green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr14);
	else
		add_object(sphere_ptr14);
	
	Phong* phong_ptr15 = new Phong;
	phong_ptr15->set_ka(ka);	
	phong_ptr15->set_kd(kd);
	phong_ptr15->set_c(brown);	
	phong_ptr15->set_exp_s(exp);
	Sphere*	sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18); 
	sphere_ptr15->set_material(phong_ptr15); 							// brown
	if (use_grid)
		grid_ptr->add_object(sphere_ptr15);
	else
		add_object(sphere_ptr15);
	
	Phong* phong_ptr16 = new Phong;
	phong_ptr16->set_ka(ka);	
	phong_ptr16->set_kd(kd);
	phong_ptr16->set_c(lightPurple);
	phong_ptr16->set_exp_s(exp);
	Sphere*	sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10); 
	sphere_ptr16->set_material(phong_ptr16);							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr16);
	else
		add_object(sphere_ptr16);
	
	Phong* phong_ptr17 = new Phong;
	phong_ptr17->set_ka(ka);	
	phong_ptr17->set_kd(kd);
	phong_ptr17->set_c(brown);
	phong_ptr17->set_exp_s(exp);
	Sphere*	sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15); 		
	sphere_ptr17->set_material(phong_ptr17);							// browm
	if (use_grid)
		grid_ptr->add_object(sphere_ptr17);
	else
		add_object(sphere_ptr17);
	
	Phong* phong_ptr18 = new Phong;
	phong_ptr18->set_ka(ka);	
	phong_ptr18->set_kd(kd);
	phong_ptr18->set_c(darkPurple);
	phong_ptr18->set_exp_s(exp);
	Sphere*	sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15); 
	sphere_ptr18->set_material(phong_ptr18);							// dark purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr18);
	else
		add_object(sphere_ptr18);
	
	Phong* phong_ptr19 = new Phong;
	phong_ptr19->set_ka(ka);	
	phong_ptr19->set_kd(kd);
	phong_ptr19->set_c(darkGreen);
	phong_ptr19->set_exp_s(exp);
	Sphere*	sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17); 
	sphere_ptr19->set_material(phong_ptr19);							// dark green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr19);
	else
		add_object(sphere_ptr19);
	
	Phong* phong_ptr20 = new Phong;
	phong_ptr20->set_ka(ka);	
	phong_ptr20->set_kd(kd);
	phong_ptr20->set_c(brown);
	phong_ptr20->set_exp_s(exp);
	Sphere*	sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15); 
	sphere_ptr20->set_material(phong_ptr20);							// browm
	if (use_grid)
		grid_ptr->add_object(sphere_ptr20);
	else
		add_object(sphere_ptr20);
	
	Phong* phong_ptr21 = new Phong;
	phong_ptr21->set_ka(ka);	
	phong_ptr21->set_kd(kd);
	phong_ptr21->set_c(lightPurple); 	
	phong_ptr21->set_exp_s(exp);
	Sphere*	sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10); 
	sphere_ptr21->set_material(phong_ptr21);							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr21);
	else
		add_object(sphere_ptr21);
	
	Phong* phong_ptr22 = new Phong;
	phong_ptr22->set_ka(ka);	
	phong_ptr22->set_kd(kd);
	phong_ptr22->set_c(lightPurple);
	phong_ptr22->set_exp_s(exp);
	Sphere*	sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12); 
	sphere_ptr22->set_material(phong_ptr22);							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr22);
	else
		add_object(sphere_ptr22);
	
	Phong* phong_ptr23 = new Phong;
	phong_ptr23->set_ka(ka);	
	phong_ptr23->set_kd(kd);
	phong_ptr23->set_c(darkPurple);
	phong_ptr23->set_exp_s(exp);
	Sphere*	sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13); 			
	sphere_ptr23->set_material(phong_ptr23);							// dark purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr23);
	else
		add_object(sphere_ptr23);	
	
	Phong* phong_ptr24 = new Phong;
	phong_ptr24->set_ka(ka);	
	phong_ptr24->set_kd(kd);
	phong_ptr24->set_c(lightPurple);  
	phong_ptr24->set_exp_s(exp);
	Sphere*	sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12); 
	sphere_ptr24->set_material(phong_ptr24);							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr24);
	else
		add_object(sphere_ptr24);
	
	Phong* phong_ptr25 = new Phong;
	phong_ptr25->set_ka(ka);	
	phong_ptr25->set_kd(kd);
	phong_ptr25->set_c(green);
	phong_ptr25->set_exp_s(exp);
	Sphere*	sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11); 			
	sphere_ptr25->set_material(phong_ptr25);					 		// green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr25);
	else
		add_object(sphere_ptr24);
	
	Phong* phong_ptr26 = new Phong;
	phong_ptr26->set_ka(ka);	
	phong_ptr26->set_kd(kd);
	phong_ptr26->set_c(lightPurple);
	phong_ptr26->set_exp_s(exp);
	Sphere*	sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12); 		
	sphere_ptr26->set_material(phong_ptr26);							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr26);
	else
		add_object(sphere_ptr25);
	
	Phong* phong_ptr27 = new Phong;
	phong_ptr27->set_ka(ka);	
	phong_ptr27->set_kd(kd);
	phong_ptr27->set_c(lightPurple);
	phong_ptr27->set_exp_s(exp);
	Sphere*	sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12); 		
	sphere_ptr27->set_material(phong_ptr27);							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr27);
	else
		add_object(sphere_ptr26);
	
	Phong* phong_ptr28 = new Phong;
	phong_ptr28->set_ka(ka);	
	phong_ptr28->set_kd(kd);
	phong_ptr28->set_c(darkPurple);
	phong_ptr28->set_exp_s(exp);
	Sphere*	sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15); 
	sphere_ptr28->set_material(phong_ptr28); 							// dark purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr28);
	else
		add_object(sphere_ptr27);
	
	Phong* phong_ptr29 = new Phong;
	phong_ptr29->set_ka(ka);	
	phong_ptr29->set_kd(kd);
	phong_ptr29->set_c(darkPurple);
	phong_ptr29->set_exp_s(exp);
	Sphere*	sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15); 
	sphere_ptr29->set_material(phong_ptr29);							// dark purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr29);
	else
		add_object(sphere_ptr29);
	
	Phong* phong_ptr30 = new Phong;
	phong_ptr30->set_ka(ka);	
	phong_ptr30->set_kd(kd);
	phong_ptr30->set_c(darkPurple);
	phong_ptr30->set_exp_s(exp);
	Sphere*	sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);  
	sphere_ptr30->set_material(phong_ptr30); 							// dark purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr30);
	else
		add_object(sphere_ptr30);
	
	Phong* phong_ptr31 = new Phong;
	phong_ptr31->set_ka(ka);	
	phong_ptr31->set_kd(kd);
	phong_ptr31->set_c(lightPurple);
	phong_ptr31->set_exp_s(exp);
	Sphere*	sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12); 
	sphere_ptr31->set_material(phong_ptr31); 							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr31);
	else
		add_object(sphere_ptr31);
	
	Phong* phong_ptr32 = new Phong;
	phong_ptr32->set_ka(ka);	
	phong_ptr32->set_kd(kd);
	phong_ptr32->set_c(green);
	phong_ptr32->set_exp_s(exp);
	Sphere*	sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);   
	sphere_ptr32->set_material(phong_ptr32);							//  green
	if (use_grid)
		grid_ptr->add_object(sphere_ptr32);
	else
		add_object(sphere_ptr32);
	
	Phong* phong_ptr33 = new Phong;
	phong_ptr33->set_ka(ka);	
	phong_ptr33->set_kd(kd);
	phong_ptr33->set_c(green);
	phong_ptr33->set_exp_s(exp);
	Sphere*	sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11); 
	sphere_ptr33->set_material(phong_ptr33);							// green 
	if (use_grid)
		grid_ptr->add_object(sphere_ptr33);
	else
		add_object(sphere_ptr33);
	
	Phong* phong_ptr34 = new Phong;
	phong_ptr34->set_ka(ka);	
	phong_ptr34->set_kd(kd);
	phong_ptr34->set_c(lightPurple);
	phong_ptr34->set_exp_s(exp);
	Sphere*	sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10); 	
	sphere_ptr34->set_material(phong_ptr34);							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr34);
	else
		add_object(sphere_ptr34);
	
	Phong* phong_ptr35 = new Phong;
	phong_ptr35->set_ka(ka);	
	phong_ptr35->set_kd(kd);
	phong_ptr35->set_c(lightPurple);
	phong_ptr35->set_exp_s(exp);
	Sphere*	sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12); 
	sphere_ptr35->set_material(phong_ptr35);							// light purple
	if (use_grid)
		grid_ptr->add_object(sphere_ptr35);
	else
		add_object(sphere_ptr35);
	
	
	// vertical plane
	
//	Matte* phong_ptr36 = new Matte;
//	phong_ptr36->set_ka(ka);	
//	phong_ptr36->set_kd(kd);
//	phong_ptr36->set_cd(grey);
//	Plane* plane_ptr = new Plane(Point3D(0, 0, -150), Normal(0, 0, 1));
//	plane_ptr->set_material(phong_ptr36);
//	add_object (plane_ptr);
	
	// HAS TO BE LAST
	if (use_grid) {
		grid_ptr->setup_cells();
		add_object(grid_ptr);
	}
}