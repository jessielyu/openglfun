//#include "World.h"
#include "MultipleObjects.h"
//#include "Plane.h"
//
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
#include "Plane.h"
#include "PlaneChecker.h"
#include "SV_Matte.h"
#include "Checker3D.h"
#include "Transparent.h"
#include "Dielectric.h"
//
//void 												
//World::build(void) {
//	int num_samples = 25;
//	
//	vp.set_hres(400);//1680
//	vp.set_vres(400);//1050
//	//vp.set_sampler(new Jittered(num_samples));
//	vp.set_pixel_size(0.5);
//	vp.set_samples(num_samples);
//	vp.set_max_depth(4);
//	
//	
//	// PinholeCamera
//	//Pinhole* camera_ptr = new Pinhole(Point3D(300, 400, 500), Point3D(0, 0, -50), Vector3D(0, 1, 0), 400, 1.0);
//	//Pinhole* camera_ptr = new Pinhole(Point3D(-1000, 2000, -500), Point3D(0, -100, 0), Vector3D(0, 1, 0), 250, 1.0);
//	//Pinhole* camera_ptr = new Pinhole(Point3D(0, 0, 500), Point3D(0, 0, 0), Vector3D(0, 1, 0), 500, 1.0);
//	//Pinhole* camera_ptr = new Pinhole(Point3D(0, 1000, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 500, 1.0);
//	//Pinhole* camera_ptr = new Pinhole(Point3D(0, 50, 600), Point3D(0, 6, -50), Vector3D(0, 1, 0), 500, 1.0);
//	
//	// spheres camera?
//	Pinhole* camera_ptr = new Pinhole;
//	camera_ptr->set_eye(Point3D(0, 0, 500)); 
//	camera_ptr->set_lookat(Point3D(1.0,0.0, 0));
//	camera_ptr->set_d(600.0);
//	//camera_ptr->compute_uvw();   
//	camera_ptr->set_zoom(1.2);//3 or 3.2
//	camera_ptr->compute_uvw();
//	set_camera(camera_ptr);
//	
////	Pinhole* camera_ptr = new Pinhole;
////	camera_ptr->set_eye(Point3D(25, 0, 200)); 
////	camera_ptr->set_lookat(Point3D(-0.75,3.0, 0));
////	camera_ptr->set_d(3000.0);
////	//camera_ptr->compute_uvw();   
////	camera_ptr->set_zoom(1.25);//3 or 3.2
////	camera_ptr->compute_uvw();
////	set_camera(camera_ptr);
//	
//	// triangle camera
////	Pinhole* pinhole_ptr = new Pinhole;
////	pinhole_ptr->set_eye(Point3D(25, 200, 100));  
////	pinhole_ptr->set_lookat(Point3D(-0.5, 0, 0));  
////	pinhole_ptr->set_d(4500);	
////	pinhole_ptr->compute_uvw();	
////	set_camera(pinhole_ptr);
//	
//	// light for triangles
////	PointLight* light_ptr1 = new PointLight;
////	light_ptr1->set_location(1, 5, 0);
////	light_ptr1->scale_radiance(3.0);
////	light_ptr1->set_shadows(true);
////	add_light(light_ptr1);
//	
//
//	
//	
//	// ThinLens camera
//	//ThinLens(const Point3D e, const Point3D l, const Vector3D u, float lr, float distance, float focal, float z)
//	//ThinLens* camera_ptr = new ThinLens(Point3D(0, 6, 50), Point3D(0, 6, 0), Vector3D(0, -1, 0), 1.0, 40.0, 74);
//	//ThinLens* camera_ptr = new ThinLens(Point3D(0, 6, 100), Point3D(0, 6, 0), Vector3D(0, 1, 0), 3.0, 40.0, 74);	// GOOD
//	//camera_ptr->set_sampler(vp.sampler_ptr);
//	
//	// FishEye camera
//	//FishEye* camera_ptr = new FishEye(Point3D(0, 6, -150), Point3D(0, 0, -50), Vector3D(0, 1, 0), 120.0);
//	//FishEye* camera_ptr = new FishEye(Point3D(5, 1000, -1), Point3D(0, 0, 0), Vector3D(0, 1, 0), 120.0);
//	//set_camera(camera_ptr);
//	
//	// Spherical camera
//	//Spherical* camera_ptr = new Spherical(Point3D(0, 6, 150), Point3D(0, 0, -50), Vector3D(0, 1, 0), 120.0, 160.0);
//	
//	// Stereo 
////	float vpd = 50;
////	
////	int pixel_gap = 5;
////	vp.set_image_hres((vp.hres * 2) + pixel_gap);
////	vp.set_image_vres(vp.vres);
////	
////	int x = vp.hres;
////	int y = vp.vres;
////	
////	int z = vp.image_hres;
////	int w = vp.image_vres; 
////	
////	Pinhole* left_camera_ptr = new Pinhole;
////	left_camera_ptr->set_d(vpd);
////	
////	Pinhole* right_camera_ptr = new Pinhole;
////	right_camera_ptr->set_d(vpd);
////	
////	
////
////	
////	//	StereoCamera(const Point3D e, const Point3D l, const Vector3D u, ViewingType view, const int gap, const float beta,
////	//Camera* left, Camera* right);
////		StereoCamera* camera_ptr = new StereoCamera(Point3D(5,0,-100), Point3D(0), Vector3D(0,1,0), pixel_gap, 
////												0.75f, left_camera_ptr, right_camera_ptr);
////	camera_ptr->setup_cameras();
//	
//
//	
//	tracer_ptr = new Whitted(this);//new AreaLighting(this); 
//	
//	background_color = MyRGBColor(black);
//	//background_color = MyRGBColor(0.4,0.4,0.8);
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(1.0);
//	set_ambient_light(ambient_ptr);
//	
//
//	// Area Light
////	MultiJittered* emissive_sampler_ptr = new MultiJittered(num_samples);
////	
////	Emissive* emissive_ptr = new Emissive;
////	emissive_ptr->scale_radiance(1.0);
////	emissive_ptr->set_ce(1.0, 1.0, 1.0);
////	
//////	p0(-1, 0, -1), 
//////	a(0, 0, 2), b(2, 0, 0), 
//////	a_len_squared(4.0), 
//////	b_len_squared(4.0),
//////	normal(0, 1, 0),
////	
////	Rectangle* rectangle_ptr = new Rectangle(Point3D(100.0,150,150.0), Vector3D(0,0,200),
////											Vector3D(200,0,0), Normal(-1.0, -1.0, -1.0));
////	rectangle_ptr->set_material(emissive_ptr);
////	rectangle_ptr->set_sampler(emissive_sampler_ptr);
////	rectangle_ptr->set_shadows(false);
////	add_object(rectangle_ptr);
//	
////	Sphere* light_sphere_ptr = new Sphere(Point3D(1000, 1000, 2000), 1000);
////	light_sphere_ptr->set_material(emissive_ptr);
////	light_sphere_ptr->set_sampler(emissive_sampler_ptr);
////	light_sphere_ptr->set_shadows(false);
////	add_object(light_sphere_ptr);
////	
////	AreaLight* area_light_ptr = new AreaLight;
////	area_light_ptr->set_object(light_sphere_ptr);
////	area_light_ptr->set_shadows(true);
////	add_light(area_light_ptr);
//
//	
//	// FakeSphericalLight
//	FakeSphericalLight* light_ptr2 = new FakeSphericalLight;
//	light_ptr2->set_location(100.0, 100.0, 200.0);
//	light_ptr2->scale_radiance(1.0);
//	light_ptr2->set_radius(500.0);
//	add_light(light_ptr2);
//	
//	
//	
//	// if I push this to 512, get weird artifacts
//	MultiJittered* occluder_sampler_ptr = new MultiJittered(MIN(num_samples, 256));
//	
//	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
//	ambient_occluder_ptr->scale_radiance(1.0);
//	ambient_occluder_ptr->set_color(white);
//	ambient_occluder_ptr->set_min_amount(0.25);
//	ambient_occluder_ptr->set_sampler(occluder_sampler_ptr);
//	set_ambient_light(ambient_occluder_ptr);
//	
//	
////	Emissive* emissive_ptr2 = new Emissive;
////	emissive_ptr2->set_ce(1.0, 1.0, 0.5);
////	emissive_ptr2->scale_radiance(1.2);
////	
////	ConcaveSphere* sky_box = new ConcaveSphere;
////	sky_box->set_radius(1000000.0);
////	sky_box->set_material(emissive_ptr2);
////	sky_box->set_shadows(false);
////	add_object(sky_box);
////	
////	EnvironmentLight* env_light = new EnvironmentLight;
////	env_light->set_material(emissive_ptr2);
////	env_light->set_sampler(new MultiJittered(num_samples));
////	env_light->set_shadows(true);
////	add_light(env_light);
//	
//	// Sample ball on plane scene
//	
////	Pinhole* camera_ptr = new Pinhole;
////	camera_ptr->set_eye(Point3D(0,5,45));
////	camera_ptr->set_lookat(Point3D(0,1,0));
////	camera_ptr->set_d(5000);
////	camera_ptr->set_zoom(.3);
////	camera_ptr->compute_uvw();
////	set_camera(camera_ptr);
////	
//	float ka1 = 0.25;
//	float kd1 = 0.75;
//	float exp1 = 0.25;
////	
////	MyRGBColor yellow(1, 1, 0);										// yellow
////	
////	Phong* phong_ptr1 = new Phong;   
////	phong_ptr1->set_ka(ka1);	
////	phong_ptr1->set_kd(kd1);
////	phong_ptr1->set_c(yellow);				
////	phong_ptr1->set_exp_s(exp1);
////	
////	Sphere* sphere_ptr001 = new Sphere(Point3D(0,1,0), 1);
////	sphere_ptr001->set_material(phong_ptr1);
////	add_object(sphere_ptr001);
////	
////	Phong* phong_ptr002 = new Phong;   
////	phong_ptr002->set_ka(ka1);	
////	phong_ptr002->set_kd(kd1);
////	phong_ptr002->set_c(white);				
////	phong_ptr002->set_exp_s(exp1);
////	
////	Plane* plane_ptr001 = new Plane(Point3D(0,-100,0), Normal(0,1,0));
////	plane_ptr001->set_material(phong_ptr002);
////	plane_ptr001->set_shadows(true);
////	add_object(plane_ptr001);
//	
//	Directional* light_ptr1 = new Directional;
//	light_ptr1->set_direction(15, 25, 50);
//	light_ptr1->scale_radiance(3.0); 	
//	add_light(light_ptr1);
//	
////	PointLight* light_ptr2 = new PointLight;
////	light_ptr2->set_location(2, 2, 10.0);
////	light_ptr2->scale_radiance(2.0);
////	add_light(light_ptr2);
//	
//	
//	
////	Matte* the_matte1 = new Matte;
////	the_matte1->set_ka(0.25);
////	the_matte1->set_kd(0.75);
////	the_matte1->set_cd(MyRGBColor(1, 0, 0));
//	
////	Phong* spec1 = new Phong();
////	spec1->set_ka(0.25);
////	spec1->set_kd(0.75);
////	spec1->set_c(1.0,0, 0);
////	spec1->set_exp_s(5);
////	
////	// use access functions to set centre and radius
////	
////	Sphere* the_sphere = new Sphere;
////	the_sphere->set_center(0, -25, 0);
////	the_sphere->set_radius(80);
////	//the_sphere->set_color(1, 0, 0);  // red
////	the_sphere->set_material(spec1);
////	add_object(the_sphere);
//
//	// use constructor to set centre and radius 
//	
////	Matte* the_matte2 = new Matte;
////	the_matte2->set_ka(0.25);
////	the_matte2->set_kd(0.75);
////	the_matte2->set_cd(MyRGBColor(1, 1, 0));
//	
////	Phong* spec2 = new Phong();
////	spec2->set_ka(0.25);
////	spec2->set_kd(0.75);
////	spec2->set_c(1.0, 1.0, 0.0);
////	spec2->set_exp_s(5);
////	
////	Sphere* the_other_sphere = new Sphere(Point3D(0, 30, 0), 60);
////	//sphere_ptr->set_color(0, 1, 0);	// yellow
////	the_other_sphere->set_material(spec2);
////	add_object(the_other_sphere);
////	
////	
////	Matte* the_matte3 = new Matte;
////	the_matte3->set_ka(0.25);
////	the_matte3->set_kd(0.75);
////	the_matte3->set_cd(MyRGBColor(0, 0.3, 0));
//////	
////	Plane* the_plane = new Plane(Point3D(0), Normal(0, 1, 1));
////	//plane_ptr->set_color(0.0, 0.3, 0.0);	// dark green
////	the_plane->set_material(the_matte3);
////	add_object(the_plane);
//	
//
//	
////	Plane* plane_ptr2 = new Plane(Point3D(0), Normal(0, 1, 0));
////	plane_ptr2->set_color(0.0, 0.3, 0.0);	// dark green
////	plane_ptr2->
////	add_object(plane_ptr2);
//	
//	bool use_grid = true;
//	Grid* grid_ptr = NULL;
//	
//	if (use_grid) {
//		grid_ptr = new Grid;
//		set_rand_seed(15);
//	}
//	
//	// yellow triangle
//	
//	Phong* phong1 = new Phong();
//	phong1->set_ka(0.25);
//	phong1->set_kd(0.75);
//	phong1->set_c(1.0,1.00, 0);
//	phong1->set_exp_s(5);
//	
//	Matte* matte_ptr1 = new Matte;			
//	matte_ptr1->set_ka(0.25); 
//	matte_ptr1->set_kd(0.75);
//	matte_ptr1->set_cd(MyRGBColor(1, 1, 0));
////	
////	Triangle* triangle_ptr1 = new Triangle(Point3D(2, 0.5, 5), Point3D(2, 1.5, -5), Point3D(-1, 0, -4)); 
////	
////	triangle_ptr1->set_material(matte_ptr1);
////	if (use_grid)
////		grid_ptr->add_object(triangle_ptr1);
////	else
////		add_object(triangle_ptr1);
////	
////	
////	// dark green triangle (transformed)
//	
//	Phong* phong2 = new Phong();
//	phong2->set_ka(0.25);
//	phong2->set_kd(0.75);
//	phong2->set_c(0.0,0.5, 0.41);
//	phong2->set_exp_s(5);
//	
//	Matte* matte_ptr2 = new Matte;			
//	matte_ptr2->set_ka(0.25); 
//	matte_ptr2->set_kd(0.75);
//	matte_ptr2->set_cd(MyRGBColor(0.0, 0.5, 0.41));
////	
////	Instance* triangle_ptr2 = new Instance(new Triangle(Point3D(2, 1, 5), Point3D(2, 0.5, -5), Point3D(-1, -1, -4))); 
////	//triangle_ptr2->translate(-1,0,0);
////	triangle_ptr2->rotate_y(120);
////	
////	triangle_ptr2->set_material(matte_ptr2);
////	triangle_ptr2->compute_bounding_box();
////	if (use_grid)
////		grid_ptr->add_object(triangle_ptr2);
////	else
////		add_object(triangle_ptr2);
////	
////	
////	// brown triangle (transformed)
//	
//	Phong* phong3 = new Phong();
//	phong3->set_ka(0.25);
//	phong3->set_kd(0.75);
//	phong3->set_c(0.71,0.40, 0.16);
//	phong3->set_exp_s(5);
//	
//	Matte* matte_ptr3 = new Matte;			
//	matte_ptr3->set_ka(0.25); 
//	matte_ptr3->set_kd(0.75);
//	matte_ptr3->set_cd(MyRGBColor(0.71, 0.40, 0.16));
////	
////	Instance* triangle_ptr3 = new Instance(new Triangle(Point3D(2, 0, 5), Point3D(2, 1, -5), Point3D(-1, 0, -4))); 
////	triangle_ptr3->rotate_y(240);
////	//triangle_ptr3->translate(1, 0, 0);
////	triangle_ptr3->set_material(matte_ptr3);
////	triangle_ptr3->compute_bounding_box();
////	if (use_grid)
////		grid_ptr->add_object(triangle_ptr3);
////	else
////		add_object(triangle_ptr3);
//	
//	//Disk* blank_disk_ptr = new Disk(Point3D(1,1,1), 2, Normal(0,0,1));
//	
//	//Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n)
//	//Rectangle* blank_disk_ptr = new Rectangle(Point3D(-1,3,0), Vector3D(4,0,0), Vector3D(0,-4,0), Normal(0,0,1));
//	
//	//	OpenCylinder(const double bottom, const double top, const double radius);
//	//OpenCylinder* blank_disk_ptr = new OpenCylinder(-1.5, 1.5, 1.5);
//	
//	//SolidCylinder* blank_disk_ptr = new SolidCylinder(-1.5, 1.5, 1.5);
//	
//	//Torus(const double a, const double b);
//	//Torus* blank_disk_ptr = new Torus(2, 1);
//	
//	//ConvexPartSphere* blank_disk_ptr = new ConvexPartSphere(Point3D(0,0,0), 2.0, 40.0, 320, 40.0, 140);
//	
//	//ConvexPartCylinder* blank_disk_ptr = new ConvexPartCylinder(-1.5, 1.5, 1.5, 40.0, 320.0);
//	
//	//Box* blank_disk_ptr = new Box(Point3D(-1.5,-1.5,-1.5), Point3D(1.5,1.5,1.5));
//	
//	//ConvexPartTorus* blank_disk_ptr = new ConvexPartTorus(2, 1, 40.0, 320, 40, 320);
//	
//	//BeveledCylinder* blank_disk_ptr = new BeveledCylinder(-1.5,1.5,1.5,.375);
//	
//	//BeveledBox* blank_disk_ptr = new BeveledBox(Point3D(-1.5,-1.5,-1.5), Point3D(1.5,1.5,1.5), .375, true);
//	
////	PartAnnulus* blank_disk_ptr = new PartAnnulus(Point3D(0,0,0), Normal(0,1,0), 1, 3, 40, 320);
////	
////	Instance* disk_ptr = new Instance(blank_disk_ptr);
////	disk_ptr->set_material(phong3);
////	disk_ptr->translate(0, -.75, 0);
////	disk_ptr->compute_bounding_box();
////	if (use_grid)
////		grid_ptr->add_object(disk_ptr);
////	else
////		add_object(disk_ptr);
////	
////	Instance* disk_ptr2 = new Instance(blank_disk_ptr);
////	disk_ptr2->set_material(phong2);
////	disk_ptr2->translate(-3,-3.75,-1);
////	//disk_ptr2->shear(0.0,0.0,-0.25,0.0,0.0,0.0);
////	disk_ptr2->compute_bounding_box();
////	if (use_grid)
////		grid_ptr->add_object(disk_ptr2);
////	else
////		add_object(disk_ptr2);	
////	
////	Instance* disk_ptr3 = new Instance(blank_disk_ptr);
////	disk_ptr3->set_material(phong1);
////	disk_ptr3->translate(3,2.25,1);
////	//disk_ptr3->shear(0.25,0.0,0.0,0.0,0.0,0.0);
////	disk_ptr3->compute_bounding_box();
////	if (use_grid)
////		grid_ptr->add_object(disk_ptr3);
////	else
////		add_object(disk_ptr3);	
//	
//	
//	// Archway(width, height, depth, column_width, double num_blocks, double num_wedges, double rb) {
//	//Instance* archway_ptr = new Instance(new Archway(2.0, 2.5, 2.5, .4, 6, 10, .05, matte_ptr3));
//	
//	//Rosette(num_rings, hole_radius, ring_width, rb, y0,y1,mat_ptr);
////	Instance* archway_ptr = new Instance(new Rosette(3, .375, .75, .075, 0, .75, matte_ptr3));
////	archway_ptr->rotate_z(90);
////	archway_ptr->rotate_y(60);
////	archway_ptr->translate(0.75, -.375, 0);
//////	archway_ptr->scale(2, 2, 2);
////	archway_ptr->compute_bounding_box();
////	//archway_ptr->set_material(phong3);
////	add_object(archway_ptr);
////	
////	Plane* ground = new Plane(Point3D(0,-3.0,0),Normal(0,1,0));
////	ground->set_material(matte_ptr2);
////	add_object(ground);
//	
////	//char* file_name = "../../PLYFiles/Isis.ply";
////	char* file_name = "../../PLYFiles/Bunny10k.ply";
////	Grid* mesh_grid_ptr = new Grid(new Mesh);
////	mesh_grid_ptr->read_flat_triangles(file_name);
////	mesh_grid_ptr->set_material(matte_ptr2);
////	mesh_grid_ptr->setup_cells();
////	Instance* instance = new Instance(mesh_grid_ptr);
////	instance->scale(30, 30, 30);
////	instance->compute_bounding_box();
////	add_object(instance);
//	
//	
////	// wedge1 parameters
////	
////	float y0 = -1.0;		// minimum y value
////	float y1 = 2;			// maximum y value
////	float r0 = 1.5;			// inner radius
////	float r1 = 3;			// outer radius
////	float rb = 0.25;		// bevel radius
////	float phi0 = 140;		// minimum azimuth angle in degrees
////	float phi1 = 350;		// maximum azimuth angle in degrees
////	
////	BeveledWedge* wedge_ptr1 = new BeveledWedge(y0, y1, r0, r1, rb, phi0, phi1, true);
////	wedge_ptr1->set_material(phong1);
////	if (use_grid)
////		grid_ptr->add_object(wedge_ptr1);
////	else
////		add_object(wedge_ptr1);
////	
////	
////	// wedge2 parameters
////	
////	y0 = -1.5;		// minimum y value
////	y1 = 1.25;		// minimum y value
////	r0 = 0.5;		// inner radius
////	r1 = 4.0;		// outer radius
////	rb = 0.075;		// bevel radius
////	phi0 = 110;		// minimum azimuth angle in degrees
////	phi1 = 130;		// maximum azimuth angle in degrees
////	
////	BeveledWedge* wedge_ptr2 = new BeveledWedge(y0, y1, r0, r1, rb, phi0, phi1, true);
////	wedge_ptr2->set_material(phong2);
////	if (use_grid)
////		grid_ptr->add_object(wedge_ptr2);
////	else
////		add_object(wedge_ptr2);	
////	
////	
////	// wedge3 parameters
////	
////	y0 = -0.75;		// minimum y value
////	y1 = 0.5;		// minimum y value
////	r0 = 1.25;		// inner radius
////	r1 = 3.75;		// outer radius
////	rb = 0.1;		// bevel radius
////	phi0 = 0;		// minimum azimuth angle in degrees
////	phi1 = 90;		// maximum azimuth angle in degrees
////	
////	BeveledWedge* wedge_ptr3 = new BeveledWedge(y0, y1, r0, r1, rb, phi0, phi1, true);
////	wedge_ptr3->set_material(phong3);
////	if (use_grid)
////		grid_ptr->add_object(wedge_ptr3);		
////	else
////		add_object(wedge_ptr3);		
////	
////	
////	Instance* box_ptr = new Instance(new Box());
////	box_ptr->set_material(matte_ptr3);
////	// shear(<#const float xy#>, <#const float xz#>, <#const float yx#>, <#const float yz#>, <#const float zx#>, <#const float zy#>)
////	box_ptr->shear(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
////	box_ptr->reflect_across_x_axis();
////	box_ptr->scale(1, 2, 1);
////	//box_ptr->reflect_across_y_axis();
////	box_ptr->reflect_across_z_axis();
////	box_ptr->compute_bounding_box();
////	if (use_grid)
////		grid_ptr->add_object(box_ptr);
////	else
////		add_object(box_ptr);
//	
//	
////	OpenCylinder* cylinder_ptr = new OpenCylinder();
////	cylinder_ptr->set_material(matte_ptr3);
////	if (use_grid)
////		grid_ptr->add_object(cylinder_ptr);
////	else
////		add_object(cylinder_ptr);
//	
////	Torus* torus_ptr = new Torus();
////	torus_ptr->set_material(matte_ptr3);
////	if (use_grid)
////		grid_ptr->add_object(torus_ptr);
////	else
////		add_object(torus_ptr);
//	
////	ConvexPartSphere* part_sphere_ptr = new ConvexPartSphere(Point3D(0,0,0), 1.0, 0.0, 240, 40.0, 140);
////	part_sphere_ptr->set_material(matte_ptr3);
////	if (use_grid)
////		grid_ptr->add_object(part_sphere_ptr);
////	else
////		add_object(part_sphere_ptr);
//	
////	// Material pointer null error
////	SolidCylinder* solid_cylinder_ptr = new SolidCylinder();
////	solid_cylinder_ptr->set_material(matte_ptr3);
////	if (use_grid)
////		grid_ptr->add_object(solid_cylinder_ptr);
////	else
////		add_object(solid_cylinder_ptr);
////	
////	Instance* solid_cylinder_instance_ptr = new Instance(solid_cylinder_ptr);
////	solid_cylinder_instance_ptr->translate(-2, 2, 10);
////	add_object(solid_cylinder_instance_ptr);
//	
//
//	MyRGBColor yellow(1, 1, 0);										// yellow
//	MyRGBColor brown(0.71, 0.40, 0.16);								// brown
//	MyRGBColor darkGreen(0.0, 0.41, 0.41);							// dark_green
//	MyRGBColor orange(1, 0.75, 0);									// orange
//	MyRGBColor green(0, 0.6, 0.3);									// green
//	MyRGBColor lightGreen(0.65, 1, 0.30);							// light green
//	MyRGBColor darkYellow(0.61, 0.61, 0);							// dark yellow
//	MyRGBColor lightPurple(0.65, 0.3, 1);							// light purple
//	MyRGBColor darkPurple(0.5, 0, 1);								// dark purple
//	MyRGBColor grey(0.25);											// grey
//	
//	// Matte material reflection coefficients - common to all materials
//	
//	float ka = 0.25;
//	float kd = 0.75;
//	//float exp = 0.25;
//	float exp = 100;
//	float k = 0.15;
//	float kr = 0.75;
//	MyRGBColor cr = white;
//	
////	Phong* phong_ptr1 = new Phong;   
////	phong_ptr1->set_ka(ka);	
////	phong_ptr1->set_kd(kd);
////	phong_ptr1->set_c(yellow);				
////	phong_ptr1->set_exp_s(exp);
//	
//	Reflective* phong_ptr1 = new Reflective;   
//	phong_ptr1->set_ka(ka);	
//	phong_ptr1->set_kd(kd);
//	phong_ptr1->set_c(yellow);				
//	phong_ptr1->set_exp_s(exp);
//	phong_ptr1->set_k(k);
//	phong_ptr1->set_kr(kr);
//	phong_ptr1->set_cr(cr);
//	Sphere*	sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30); 
//	sphere_ptr1->set_material(phong_ptr1);	   							// yellow
//	//sphere_ptr1->set_shadows(false);
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr1);
//	else
//		add_object(sphere_ptr1);
//	
//	Reflective* phong_ptr2 = new Reflective;
//	phong_ptr2->set_ka(ka);	
//	phong_ptr2->set_kd(kd);
//	phong_ptr2->set_c(brown);
//	phong_ptr2->set_exp_s(exp);
//	phong_ptr2->set_k(k);
//	phong_ptr2->set_kr(kr);
//	phong_ptr2->set_cr(cr);
//	Sphere*	sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20); 
//	sphere_ptr2->set_material(phong_ptr2);								// brown
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr2);
//	else
//		add_object(sphere_ptr2);
//	
//	
//	Reflective* phong_ptr3 = new Reflective;
//	phong_ptr3->set_ka(ka);	
//	phong_ptr3->set_kd(kd);
//	phong_ptr3->set_c(darkGreen);
//	phong_ptr3->set_exp_s(exp);
//	phong_ptr3->set_k(k);
//	phong_ptr3->set_kr(kr);
//	phong_ptr3->set_cr(cr);
//	Sphere*	sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17); 
//	sphere_ptr3->set_material(phong_ptr3);								// dark green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr3);
//	else
//		add_object(sphere_ptr3);
//	
//	Reflective* phong_ptr4 = new Reflective;
//	phong_ptr4->set_ka(ka);	
//	phong_ptr4->set_kd(kd);
//	phong_ptr4->set_c(orange);
//	phong_ptr4->set_exp_s(exp);
//	phong_ptr4->set_k(k);
//	phong_ptr4->set_kr(kr);
//	phong_ptr4->set_cr(cr);
//	Sphere*	sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20); 
//	sphere_ptr4->set_material(phong_ptr4);								// orange
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr4);
//	else
//		add_object(sphere_ptr4);
//	
//	Reflective* phong_ptr5 = new Reflective;
//	phong_ptr5->set_ka(ka);	
//	phong_ptr5->set_kd(kd);
//	phong_ptr5->set_c(green);
//	phong_ptr5->set_exp_s(exp);
//	phong_ptr5->set_k(k);
//	phong_ptr5->set_kr(kr);
//	phong_ptr5->set_cr(cr);
//	Sphere*	sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27); 			
//	sphere_ptr5->set_material(phong_ptr5);								// green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr5);
//	else
//		add_object(sphere_ptr5);
//	
//	Reflective* phong_ptr6 = new Reflective;
//	phong_ptr6->set_ka(ka);	
//	phong_ptr6->set_kd(kd);
//	phong_ptr6->set_c(lightGreen);
//	phong_ptr6->set_exp_s(exp);
//	phong_ptr6->set_k(k);
//	phong_ptr6->set_kr(kr);
//	phong_ptr6->set_cr(cr);
//	Sphere*	sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25); 
//	sphere_ptr6->set_material(phong_ptr6);								// light green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr6);
//	else
//		add_object(sphere_ptr6);
//	
//	Reflective* phong_ptr7 = new Reflective;
//	phong_ptr7->set_ka(ka);	
//	phong_ptr7->set_kd(kd);
//	phong_ptr7->set_c(green);
//	phong_ptr7->set_exp_s(exp);
//	phong_ptr7->set_k(k);
//	phong_ptr7->set_kr(kr);
//	phong_ptr7->set_cr(cr);
//	Sphere*	sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22); 
//	sphere_ptr7->set_material(phong_ptr7);   							// green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr7);
//	else
//		add_object(sphere_ptr7);
//	
//	Reflective* phong_ptr8 = new Reflective;
//	phong_ptr8->set_ka(ka);	
//	phong_ptr8->set_kd(kd);
//	phong_ptr8->set_c(brown);
//	phong_ptr8->set_exp_s(exp);
//	phong_ptr8->set_k(k);
//	phong_ptr8->set_kr(kr);
//	phong_ptr8->set_cr(cr);
//	Sphere*	sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);  
//	sphere_ptr8->set_material(phong_ptr8);								// brown
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr8);
//	else
//		add_object(sphere_ptr8);
//	
//	Reflective* phong_ptr9 = new Reflective;
//	phong_ptr9->set_ka(ka);	
//	phong_ptr9->set_kd(kd);
//	phong_ptr9->set_c(lightGreen);
//	phong_ptr9->set_exp_s(exp);
//	phong_ptr9->set_k(k);
//	phong_ptr9->set_kr(kr);
//	phong_ptr9->set_cr(cr);
//	Sphere*	sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23); 
//	sphere_ptr9->set_material(phong_ptr9);								// light green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr9);
//	else
//		add_object(sphere_ptr9);
//	
//	Reflective* phong_ptr10 = new Reflective;
//	phong_ptr10->set_ka(ka);	
//	phong_ptr10->set_kd(kd);
//	phong_ptr10->set_c(darkGreen);	
//	phong_ptr10->set_exp_s(exp);
//	phong_ptr10->set_k(k);
//	phong_ptr10->set_kr(kr);
//	phong_ptr10->set_cr(cr);
//	Sphere*	sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22); 
//	sphere_ptr10->set_material(phong_ptr10);     						// dark green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr10);
//	else
//		add_object(sphere_ptr10);
//	
//	Reflective* phong_ptr11 = new Reflective;
//	phong_ptr11->set_ka(ka);	
//	phong_ptr11->set_kd(kd);
//	phong_ptr11->set_c(darkYellow);
//	phong_ptr11->set_exp_s(exp);
//	phong_ptr11->set_k(k);
//	phong_ptr11->set_kr(kr);
//	phong_ptr11->set_cr(cr);
//	Sphere*	sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22); 
//	sphere_ptr11->set_material(phong_ptr11);							// dark yellow
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr11);
//	else
//		add_object(sphere_ptr11);
//	
//	Reflective* phong_ptr12 = new Reflective;
//	phong_ptr12->set_ka(ka);	
//	phong_ptr12->set_kd(kd);
//	phong_ptr12->set_c(darkYellow);
//	phong_ptr12->set_exp_s(exp);
//	phong_ptr12->set_k(k);
//	phong_ptr12->set_kr(kr);
//	phong_ptr12->set_cr(cr);
//	Sphere*	sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22); 
//	sphere_ptr12->set_material(phong_ptr12);							// dark yellow
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr12);
//	else
//		add_object(sphere_ptr12);
//	
//	Reflective* phong_ptr13 = new Reflective;
//	phong_ptr13->set_ka(ka);	
//	phong_ptr13->set_kd(kd);
//	phong_ptr13->set_c(darkYellow);		
//	phong_ptr13->set_exp_s(exp);
//	phong_ptr13->set_k(k);
//	phong_ptr13->set_kr(kr);
//	phong_ptr13->set_cr(cr);
//	Sphere*	sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10); 
//	sphere_ptr13->set_material(phong_ptr13);
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr13);	
//	else
//		add_object(sphere_ptr13);										// dark yellow (hidden)
//	
//	Reflective* phong_ptr14 = new Reflective;
//	phong_ptr14->set_ka(ka);	
//	phong_ptr14->set_kd(kd);
//	phong_ptr14->set_c(darkGreen);	
//	phong_ptr14->set_exp_s(exp);
//	phong_ptr14->set_k(k);
//	phong_ptr14->set_kr(kr);
//	phong_ptr14->set_cr(cr);
//	Sphere*	sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18); 
//	sphere_ptr14->set_material(phong_ptr14); 							// dark green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr14);
//	else
//		add_object(sphere_ptr14);
//	
//	Reflective* phong_ptr15 = new Reflective;
//	phong_ptr15->set_ka(ka);	
//	phong_ptr15->set_kd(kd);
//	phong_ptr15->set_c(brown);	
//	phong_ptr15->set_exp_s(exp);
//	phong_ptr15->set_k(k);
//	phong_ptr15->set_kr(kr);
//	phong_ptr15->set_cr(cr);
//	Sphere*	sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18); 
//	sphere_ptr15->set_material(phong_ptr15); 							// brown
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr15);
//	else
//		add_object(sphere_ptr15);
//	
//	Reflective* phong_ptr16 = new Reflective;
//	phong_ptr16->set_ka(ka);	
//	phong_ptr16->set_kd(kd);
//	phong_ptr16->set_c(lightPurple);
//	phong_ptr16->set_exp_s(exp);
//	phong_ptr16->set_k(k);
//	phong_ptr16->set_kr(kr);
//	phong_ptr16->set_cr(cr);
//	Sphere*	sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10); 
//	sphere_ptr16->set_material(phong_ptr16);							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr16);
//	else
//		add_object(sphere_ptr16);
//	
//	Reflective* phong_ptr17 = new Reflective;
//	phong_ptr17->set_ka(ka);	
//	phong_ptr17->set_kd(kd);
//	phong_ptr17->set_c(brown);
//	phong_ptr17->set_exp_s(exp);
//	phong_ptr17->set_k(k);
//	phong_ptr17->set_kr(kr);
//	phong_ptr17->set_cr(cr);
//	Sphere*	sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15); 		
//	sphere_ptr17->set_material(phong_ptr17);							// browm
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr17);
//	else
//		add_object(sphere_ptr17);
//	
//	Reflective* phong_ptr18 = new Reflective;
//	phong_ptr18->set_ka(ka);	
//	phong_ptr18->set_kd(kd);
//	phong_ptr18->set_c(darkPurple);
//	phong_ptr18->set_exp_s(exp);
//	phong_ptr18->set_k(k);
//	phong_ptr18->set_kr(kr);
//	phong_ptr18->set_cr(cr);
//	Sphere*	sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15); 
//	sphere_ptr18->set_material(phong_ptr18);							// dark purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr18);
//	else
//		add_object(sphere_ptr18);
//	
//	Reflective* phong_ptr19 = new Reflective;
//	phong_ptr19->set_ka(ka);	
//	phong_ptr19->set_kd(kd);
//	phong_ptr19->set_c(darkGreen);
//	phong_ptr19->set_exp_s(exp);
//	phong_ptr19->set_k(k);
//	phong_ptr19->set_kr(kr);
//	phong_ptr19->set_cr(cr);
//	Sphere*	sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17); 
//	sphere_ptr19->set_material(phong_ptr19);							// dark green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr19);
//	else
//		add_object(sphere_ptr19);
//	
//	Reflective* phong_ptr20 = new Reflective;
//	phong_ptr20->set_ka(ka);	
//	phong_ptr20->set_kd(kd);
//	phong_ptr20->set_c(brown);
//	phong_ptr20->set_exp_s(exp);
//	phong_ptr20->set_k(k);
//	phong_ptr20->set_kr(kr);
//	phong_ptr20->set_cr(cr);
//	Sphere*	sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15); 
//	sphere_ptr20->set_material(phong_ptr20);							// browm
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr20);
//	else
//		add_object(sphere_ptr20);
//	
//	Reflective* phong_ptr21 = new Reflective;
//	phong_ptr21->set_ka(ka);	
//	phong_ptr21->set_kd(kd);
//	phong_ptr21->set_c(lightPurple); 	
//	phong_ptr21->set_exp_s(exp);
//	phong_ptr21->set_k(k);
//	phong_ptr21->set_kr(kr);
//	phong_ptr21->set_cr(cr);
//	Sphere*	sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10); 
//	sphere_ptr21->set_material(phong_ptr21);							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr21);
//	else
//		add_object(sphere_ptr21);
//	
//	Reflective* phong_ptr22 = new Reflective;
//	phong_ptr22->set_ka(ka);	
//	phong_ptr22->set_kd(kd);
//	phong_ptr22->set_c(lightPurple);
//	phong_ptr22->set_exp_s(exp);
//	phong_ptr22->set_k(k);
//	phong_ptr22->set_kr(kr);
//	phong_ptr22->set_cr(cr);
//	Sphere*	sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12); 
//	sphere_ptr22->set_material(phong_ptr22);							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr22);
//	else
//		add_object(sphere_ptr22);
//	
//	Reflective* phong_ptr23 = new Reflective;
//	phong_ptr23->set_ka(ka);	
//	phong_ptr23->set_kd(kd);
//	phong_ptr23->set_c(darkPurple);
//	phong_ptr23->set_exp_s(exp);
//	phong_ptr23->set_k(k);
//	phong_ptr23->set_kr(kr);
//	phong_ptr23->set_cr(cr);
//	Sphere*	sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13); 			
//	sphere_ptr23->set_material(phong_ptr23);							// dark purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr23);
//	else
//		add_object(sphere_ptr23);	
//	
//	Reflective* phong_ptr24 = new Reflective;
//	phong_ptr24->set_ka(ka);	
//	phong_ptr24->set_kd(kd);
//	phong_ptr24->set_c(lightPurple);  
//	phong_ptr24->set_exp_s(exp);
//	phong_ptr24->set_k(k);
//	phong_ptr24->set_kr(kr);
//	phong_ptr24->set_cr(cr);
//	Sphere*	sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12); 
//	sphere_ptr24->set_material(phong_ptr24);							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr24);
//	else
//		add_object(sphere_ptr24);
//	
//	Reflective* phong_ptr25 = new Reflective;
//	phong_ptr25->set_ka(ka);	
//	phong_ptr25->set_kd(kd);
//	phong_ptr25->set_c(green);
//	phong_ptr25->set_exp_s(exp);
//	phong_ptr25->set_k(k);
//	phong_ptr25->set_kr(kr);
//	phong_ptr25->set_cr(cr);
//	Sphere*	sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11); 			
//	sphere_ptr25->set_material(phong_ptr25);					 		// green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr25);
//	else
//		add_object(sphere_ptr25);
//	
//	Reflective* phong_ptr26 = new Reflective;
//	phong_ptr26->set_ka(ka);	
//	phong_ptr26->set_kd(kd);
//	phong_ptr26->set_c(lightPurple);
//	phong_ptr26->set_exp_s(exp);
//	phong_ptr26->set_k(k);
//	phong_ptr26->set_kr(kr);
//	phong_ptr26->set_cr(cr);
//	Sphere*	sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12); 		
//	sphere_ptr26->set_material(phong_ptr26);							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr26);
//	else
//		add_object(sphere_ptr26);
//	
//	Reflective* phong_ptr27 = new Reflective;
//	phong_ptr27->set_ka(ka);	
//	phong_ptr27->set_kd(kd);
//	phong_ptr27->set_c(lightPurple);
//	phong_ptr27->set_exp_s(exp);
//	phong_ptr27->set_k(k);
//	phong_ptr27->set_kr(kr);
//	phong_ptr27->set_cr(cr);
//	Sphere*	sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12); 		
//	sphere_ptr27->set_material(phong_ptr27);							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr27);
//	else
//		add_object(sphere_ptr27);
//	
//	Reflective* phong_ptr28 = new Reflective;
//	phong_ptr28->set_ka(ka);	
//	phong_ptr28->set_kd(kd);
//	phong_ptr28->set_c(darkPurple);
//	phong_ptr28->set_exp_s(exp);
//	phong_ptr28->set_k(k);
//	phong_ptr28->set_kr(kr);
//	phong_ptr28->set_cr(cr);
//	Sphere*	sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15); 
//	sphere_ptr28->set_material(phong_ptr28); 							// dark purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr28);
//	else
//		add_object(sphere_ptr28);
//	
//	Reflective* phong_ptr29 = new Reflective;
//	phong_ptr29->set_ka(ka);	
//	phong_ptr29->set_kd(kd);
//	phong_ptr29->set_c(darkPurple);
//	phong_ptr29->set_exp_s(exp);
//	phong_ptr29->set_k(k);
//	phong_ptr29->set_kr(kr);
//	phong_ptr29->set_cr(cr);
//	Sphere*	sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15); 
//	sphere_ptr29->set_material(phong_ptr29);							// dark purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr29);
//	else
//		add_object(sphere_ptr29);
//	
//	Reflective* phong_ptr30 = new Reflective;
//	phong_ptr30->set_ka(ka);	
//	phong_ptr30->set_kd(kd);
//	phong_ptr30->set_c(darkPurple);
//	phong_ptr30->set_exp_s(exp);
//	phong_ptr30->set_k(k);
//	phong_ptr30->set_kr(kr);
//	phong_ptr30->set_cr(cr);
//	Sphere*	sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);  
//	sphere_ptr30->set_material(phong_ptr30); 							// dark purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr30);
//	else
//		add_object(sphere_ptr30);
//	
//	Reflective* phong_ptr31 = new Reflective;
//	phong_ptr31->set_ka(ka);	
//	phong_ptr31->set_kd(kd);
//	phong_ptr31->set_c(lightPurple);
//	phong_ptr31->set_exp_s(exp);
//	phong_ptr31->set_k(k);
//	phong_ptr31->set_kr(kr);
//	phong_ptr31->set_cr(cr);
//	Sphere*	sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12); 
//	sphere_ptr31->set_material(phong_ptr31); 							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr31);
//	else
//		add_object(sphere_ptr31);
//	
//	Reflective* phong_ptr32 = new Reflective;
//	phong_ptr32->set_ka(ka);	
//	phong_ptr32->set_kd(kd);
//	phong_ptr32->set_c(green);
//	phong_ptr32->set_exp_s(exp);
//	phong_ptr32->set_k(k);
//	phong_ptr32->set_kr(kr);
//	phong_ptr32->set_cr(cr);
//	Sphere*	sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);   
//	sphere_ptr32->set_material(phong_ptr32);							//  green
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr32);
//	else
//		add_object(sphere_ptr32);
//	
//	Reflective* phong_ptr33 = new Reflective;
//	phong_ptr33->set_ka(ka);	
//	phong_ptr33->set_kd(kd);
//	phong_ptr33->set_c(green);
//	phong_ptr33->set_exp_s(exp);
//	phong_ptr33->set_k(k);
//	phong_ptr33->set_kr(kr);
//	phong_ptr33->set_cr(cr);
//	Sphere*	sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11); 
//	sphere_ptr33->set_material(phong_ptr33);							// green 
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr33);
//	else
//		add_object(sphere_ptr33);
//	
//	Reflective* phong_ptr34 = new Reflective;
//	phong_ptr34->set_ka(ka);	
//	phong_ptr34->set_kd(kd);
//	phong_ptr34->set_c(lightPurple);
//	phong_ptr34->set_exp_s(exp);
//	phong_ptr34->set_k(k);
//	phong_ptr34->set_kr(kr);
//	phong_ptr34->set_cr(cr);
//	Sphere*	sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10); 	
//	sphere_ptr34->set_material(phong_ptr34);							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr34);
//	else
//		add_object(sphere_ptr34);
//	
//	Reflective* phong_ptr35 = new Reflective;
//	phong_ptr35->set_ka(ka);	
//	phong_ptr35->set_kd(kd);
//	phong_ptr35->set_c(lightPurple);
//	phong_ptr35->set_exp_s(exp);
//	phong_ptr35->set_k(k);
//	phong_ptr35->set_kr(kr);
//	phong_ptr35->set_cr(cr);
//	Sphere*	sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12); 
//	sphere_ptr35->set_material(phong_ptr35);							// light purple
//	if (use_grid)
//		grid_ptr->add_object(sphere_ptr35);
//	else
//		add_object(sphere_ptr35);
//	
//	
//	// vertical plane
//	
//	Matte* phong_ptr36 = new Matte;
//	phong_ptr36->set_ka(ka);	
//	phong_ptr36->set_kd(kd);
//	phong_ptr36->set_cd(grey);
//
//	Plane* plane_ptr = new Plane(Point3D(0, 0, -150), Normal(0, 0, 1));
//	plane_ptr->set_material(phong_ptr36);
//	add_object (plane_ptr);
//	
//	// vertical reflection plane
////	
////	Reflective* phong_ptr37 = new Reflective;
////	phong_ptr37->set_ka(ka);	
////	phong_ptr37->set_kd(kd);
////	phong_ptr37->set_c(white);
////	phong_ptr37->set_k(k);
////	phong_ptr37->set_kr(kr);
////	phong_ptr37->set_cr(cr);
////	
////	Plane* plane_ptr2 = new Plane(Point3D(0, 0, 501), Normal(0, 0, -1));
////	plane_ptr2->set_material(phong_ptr37);
////	add_object (plane_ptr2);
//	
//	// HAS TO BE LAST
//	if (use_grid) {
//		grid_ptr->setup_cells();
//		add_object(grid_ptr);
//	}
//}








// This builds the scene for Figure 9.9

//void 												
//World::build(void) {
//	int num_samples = 1;
//	
//	vp.set_hres(600);			
//	vp.set_vres(600);
//	vp.set_samples(num_samples);
//	vp.set_max_depth(3);
//	
//	tracer_ptr = new Whitted(this);//RayCast(this);
//	
//	Pinhole* camera_ptr = new Pinhole;
//	
//	// for Figure 9.9(a)	
//	
//	camera_ptr->set_eye(0, 0, 500);
//	camera_ptr->set_lookat(0);    
//	camera_ptr->set_zoom(2);
//	camera_ptr->set_view_distance(500); 
//	
//	/*	
//	 // for Figure 9.9(b)
//	 
//	 camera_ptr->set_eye(300, 400, 500);
//	 camera_ptr->set_lookat(0, 0, -50);
//	 camera_ptr->set_view_distance(400);
//	 */
//	
//	/*	
//	 // for Figure 9.9(c)
//	 
//	 camera_ptr->set_eye(-1000, 2000, -500);
//	 camera_ptr->set_lookat(0, -100, 0);
//	 camera_ptr->set_view_distance(250);
//	 */
//	
//	camera_ptr->compute_uvw();		  
//	set_camera(camera_ptr);
//	
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(50, 150, 200); 
//	light_ptr1->scale_radiance(6.0);
//	light_ptr1->set_shadows(true);
//	add_light(light_ptr1);
//	
//	
//	// sphere
//	
//	Phong* phong_ptr1 = new Phong;			
//	phong_ptr1->set_ka(0.5); 
//	phong_ptr1->set_kd(0.4);
//	phong_ptr1->set_cd(0.5, 0.6, 0);  	// green
//	phong_ptr1->set_ks(0.05); 
//	phong_ptr1->set_exp(25); 	
//	
////	Matte* matte_ptr1 = new Matte;				
////	matte_ptr1->set_ka(0.4); 
////	matte_ptr1->set_kd(0.3);
////	matte_ptr1->set_cd(0.5, 0.6, 0);  	// orange
////	matte_ptr1->set_shadows(false);
//	
//	Sphere*	sphere_ptr1 = new Sphere(Point3D(-45, 45, 40), 50); 
//	sphere_ptr1->set_material(phong_ptr1);
//	sphere_ptr1->set_shadows(false);
//	add_object(sphere_ptr1);
//	
//	
//	
//	// box
//	
////	Reflective* reflective_ptrc = new Reflective;			
////	reflective_ptrc->set_ka(0.0); 
////	reflective_ptrc->set_kd(0.0);
////	reflective_ptrc->set_ks(0.0);
////	reflective_ptrc->set_cd(0.8, 0.5, 0);
////	reflective_ptrc->set_kr(0.9);
////	reflective_ptrc->set_cr(0.65, 0.75, 1.0);   // pale blue
//	
//	Reflective* reflective_ptr3 = new Reflective;			
//	reflective_ptr3->set_ka(0.35); 
//	reflective_ptr3->set_kd(0.5);
//	reflective_ptr3->set_cd(0.8, 0.5, 0.0);   // cyan
//	reflective_ptr3->set_ks(0.2);
//	reflective_ptr3->set_exp(100.0);
//	reflective_ptr3->set_kr(0.75);
//	reflective_ptr3->set_cr(0.8, 0.5, 0.0);
//	
//	Matte* matte_ptr = new Matte;				
//	matte_ptr->set_ka(0.4); 
//	matte_ptr->set_kd(0.3);
//	matte_ptr->set_cd(0.8, 0.5, 0);  	// orange
//	matte_ptr->set_shadows(false);
//	
//	Box* box_ptr1 = new Box(Point3D(20, -101, -100), Point3D(90, 100, 20));
//	box_ptr1->set_material(reflective_ptr3);
//	box_ptr1->set_shadows(false);
//	add_object(box_ptr1);
//	
//	
//	// triangle
//	
////	Reflective* reflective_ptr = new Reflective;			
////	reflective_ptr->set_ka(0.0); 
////	reflective_ptr->set_kd(0.0);
////	reflective_ptr->set_ks(0.0);
////	reflective_ptr->set_cd(0.0);
////	reflective_ptr->set_kr(0.9);
////	reflective_ptr->set_cr(0.0, 0.5, 0.5);  // light green
//	
//	Transparent* glass_ptr = new Transparent;
//	glass_ptr->set_ks(0.2);
//	glass_ptr->set_exp(2000.0);
//	glass_ptr->set_ior(1.5);		
//	glass_ptr->set_kr(0.1);
//	glass_ptr->set_kt(0.9);
//	
//	Dielectric* dielectric_ptr = new Dielectric;
//	dielectric_ptr->set_ka(0.0);
//	dielectric_ptr->set_kd(0.0); 
//	dielectric_ptr->set_ks(0.2);    
//	dielectric_ptr->set_exp(2000.0);
//	dielectric_ptr->set_eta_in(1.5);   
//	dielectric_ptr->set_eta_out(1.5);
//	dielectric_ptr->set_cf_in(0.35, 0.65, 0.45);   // green
//	dielectric_ptr->set_cf_out(white);
//	
//	Phong*	phong_ptr2 = new Phong;			
//	phong_ptr2->set_ka(0.25); 
//	phong_ptr2->set_kd(0.5); 
//	phong_ptr2->set_cd(0, 0.5, 0.5);     // cyan
//	phong_ptr2->set_ks(0.05); 
//	phong_ptr2->set_exp(50); 
//	
//	Triangle* triangle_ptr1 = new Triangle(Point3D(-110, -85, 80), Point3D(120, 10, 20), Point3D(-40, 50, -30));
//	triangle_ptr1->set_material(glass_ptr);     
//	triangle_ptr1->set_shadows(false);
//	add_object(triangle_ptr1);
//	
//	
//	// ground plane with checker
//	
//	Checker3D* checker3D_ptr = new Checker3D;
//	checker3D_ptr->set_size(100); 
//	checker3D_ptr->set_color1(0.7);  
//	checker3D_ptr->set_color2(1.0);
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;
//	sv_matte_ptr->set_ka(0.25);
//	sv_matte_ptr->set_kd(0.35);
//	sv_matte_ptr->set_cd(checker3D_ptr);
//	
//	Plane* plane_ptr = new Plane(Point3D(0, -101, 0), Normal(0, 1, 0));
//	plane_ptr->set_material(sv_matte_ptr);
//	plane_ptr->set_shadows(false);
//	add_object(plane_ptr);
//}







// This builds the scene for Figure 18.12

// lights

//void 												
//World::build(void) {
//	int num_samples = 100;   
//	
//	Sampler* sampler_ptr = new MultiJittered(num_samples);
//	
//	vp.set_hres(600);
//	vp.set_vres(600);
//	vp.set_sampler(sampler_ptr);	
//	
//	background_color = MyRGBColor(0.5);
//	
//	tracer_ptr = new RayCast(this);   
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(-20, 10, 20);
//	pinhole_ptr->set_lookat(0, 2, 0); 	
//	pinhole_ptr->set_view_distance(1080);          
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr); 
//	
//	
//	Emissive* emissive_ptr = new Emissive;
//	emissive_ptr->scale_radiance(40.0);   // can be different from the light_ptr
//	emissive_ptr->set_ce(white);
//	
//	float width = 4.0;
//	float radius = 0.56 * width;
//	Point3D center(0.0, 7.0, -7.0);		
//	Sphere* sphere_ptr = new Sphere(center, radius);
//	sphere_ptr->set_material(emissive_ptr);
//	sphere_ptr->set_sampler(sampler_ptr);
//	sphere_ptr->set_shadows(false);
//	add_object(sphere_ptr);
//	
//	
//	FakeSphericalLight* light_ptr = new FakeSphericalLight;
//	light_ptr->set_location(center);
//	light_ptr->scale_radiance(250.0);       // for Figure 18.12(a)
//	//	light_ptr->scale_radiance(3.0);			// for Figure 18.12(b)
//	light_ptr->set_radius(radius);
//	//light_ptr->use_distance_attenuation(true);
//	light_ptr->set_shadows(true);
//	add_light(light_ptr);
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->set_location(50, 150, 200); 
//	light_ptr1->scale_radiance(6.0);
//	light_ptr1->set_shadows(true);
//	add_light(light_ptr1);
//	
//	
//	// Four axis aligned boxes
//	
//	float box_width 	= 1.0; 		// x dimension
//	float box_depth 	= 1.0; 		// z dimension
//	float box_height 	= 4.5; 		// y dimension
//	float gap			= 3.0; 
//	
//	Matte* matte_ptr1 = new Matte;			
//	matte_ptr1->set_ka(0.25); 
//	matte_ptr1->set_kd(0.75);
//	matte_ptr1->set_cd(0.4, 0.7, 0.4);     // green
//	
//	Box* box_ptr0 = new Box(Point3D(- 1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth), 
//							Point3D(-1.5 * gap  - box_width, box_height, 0.5 * box_depth)); 
//	box_ptr0->set_material(matte_ptr1);
//	add_object(box_ptr0);
//	
//	Box* box_ptr1 = new Box(Point3D(- 0.5 * gap - box_width, 0.0, -0.5 * box_depth), 
//							Point3D(-0.5 * gap, box_height, 0.5 * box_depth)); 
//	box_ptr1->set_material(matte_ptr1);
//	add_object(box_ptr1);
//	
//	Box* box_ptr2 = new Box(Point3D(0.5 * gap, 0.0, -0.5 * box_depth), 
//							Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
//	box_ptr2->set_material(matte_ptr1);
//	add_object(box_ptr2);
//	
//	Box* box_ptr3 = new Box(Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth), 
//							Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
//	box_ptr3->set_material(matte_ptr1);
//	add_object(box_ptr3);
//	
//	
//	// ground plane
//	
//	Matte* matte_ptr2 = new Matte;			
//	matte_ptr2->set_ka(0.1); 
//	matte_ptr2->set_kd(0.90);
//	matte_ptr2->set_cd(white);
//	
//	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0)); 
//	plane_ptr->set_material(matte_ptr2);
//	add_object(plane_ptr);	
//}








// This builds the scene for Figure 18.6

//void 												
//World::build(void) {
//	int num_samples = 100;   
//	
//	Sampler* sampler_ptr = new MultiJittered(num_samples);
//	
//	vp.set_hres(600);
//	vp.set_vres(600);
//	//	vp.set_gamut_display(true);    // for Figure 18.6(b)
//	vp.set_sampler(sampler_ptr);	
//	
//	background_color = MyRGBColor(0.5);
//	
//	tracer_ptr = new AreaLighting(this);
//	
//	Pinhole* camera = new Pinhole;
//	camera->set_eye(-20, 10, 20);
//	camera->set_lookat(0, 2, 0); 	
//	camera->set_view_distance(1080);          
//	camera->compute_uvw();     
//	set_camera(camera); 
//	
//	
//	Emissive* emissive_ptr = new Emissive;
//	emissive_ptr->scale_radiance(40.0);
//	emissive_ptr->set_ce(white);
//	
//	
//	// define a rectangle for the rectangular light
//	
//	float width = 4.0;	
//	float height = 4.0;
//	Point3D center(0.0, 2.0, -7.0);  // rectangle just touches the plane   
//	Point3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
//	Vector3D a(width, 0.0, 0.0);
//	Vector3D b(0.0, height, 0.0);
//	Normal normal(0, 0, 1);
//	
//	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
//	rectangle_ptr->set_material(emissive_ptr);
//	rectangle_ptr->set_sampler(sampler_ptr);
//	rectangle_ptr->set_shadows(false);
//	add_object(rectangle_ptr);
//	
//	
//	AreaLight* area_light_ptr = new AreaLight;
//	area_light_ptr->set_object(rectangle_ptr);
//	area_light_ptr->set_shadows(true);
//	add_light(area_light_ptr);
//	
//	
//	// Four axis aligned boxes
//	
//	float box_width 	= 1.0; 		// x dimension
//	float box_depth 	= 1.0; 		// z dimension
//	float box_height 	= 4.5; 		// y dimension
//	float gap			= 3.0; 
//	
//	Matte* matte_ptr1 = new Matte;			
//	matte_ptr1->set_ka(0.25); 
//	matte_ptr1->set_kd(0.75);
//	matte_ptr1->set_cd(0.4, 0.7, 0.4);     // green
//	
//	Box* box_ptr0 = new Box(Point3D(- 1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth), 
//							Point3D(-1.5 * gap  - box_width, box_height, 0.5 * box_depth)); 
//	box_ptr0->set_material(matte_ptr1);
//	add_object(box_ptr0);
//	
//	Box* box_ptr1 = new Box(Point3D(- 0.5 * gap - box_width, 0.0, -0.5 * box_depth), 
//							Point3D(-0.5 * gap, box_height, 0.5 * box_depth)); 
//	box_ptr1->set_material(matte_ptr1);
//	add_object(box_ptr1);
//	
//	Box* box_ptr2 = new Box(Point3D(0.5 * gap, 0.0, -0.5 * box_depth), 
//							Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
//	box_ptr2->set_material(matte_ptr1);
//	add_object(box_ptr2);
//	
//	Box* box_ptr3 = new Box(Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth), 
//							Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
//	box_ptr3->set_material(matte_ptr1);
//	add_object(box_ptr3);
//	
//	
//	// ground plane
//	
//	Matte* matte_ptr2 = new Matte;			
//	matte_ptr2->set_ka(0.1); 
//	matte_ptr2->set_kd(0.90);
//	matte_ptr2->set_cd(white);
//	
//	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0)); 
//	plane_ptr->set_material(matte_ptr2);
//	add_object(plane_ptr);	
//}





// DRAGON

//void 												
//World::build(void) {
//	int num_samples = 1;
//	
//	vp.set_hres(600);      
//	vp.set_vres(600);    
//	vp.set_samples(num_samples);
//	vp.set_max_depth(1);	
//	
//	tracer_ptr = new Whitted(this);
//	background_color = black;
//	
//	MultiJittered* sampler_ptr = new MultiJittered(num_samples);
//	
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->scale_radiance(1.0);
//	//	set_ambient_light(ambient_ptr);
//	
//	AmbientOccluder* occluder_ptr = new AmbientOccluder;
//	occluder_ptr->set_min_amount(0.25);		
//	occluder_ptr->set_sampler(sampler_ptr);
//	set_ambient_light(occluder_ptr);
//	
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(-6, 5, 11);    	
//	pinhole_ptr->set_lookat(-0.009 , 0.11, 0);
//	pinhole_ptr->set_view_distance(37500);  
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr); 
//	
//	Directional* light_ptr = new Directional;
//	light_ptr->set_direction(0.5, 1, 0.75);
//	light_ptr->scale_radiance(1.0);
//	light_ptr->set_shadows(true);
//	add_light(light_ptr);
//	
//	
//	Phong* phong_ptr = new Phong;			
//	phong_ptr->set_ka(0.2); 
//	phong_ptr->set_kd(0.95); 
//	phong_ptr->set_cd(1, 0.6, 0);   // orange
//	phong_ptr->set_ks(0.5);  
//	phong_ptr->set_exp(20); 
//	phong_ptr->set_cs(1, 0.6, 0);   // orange   
//	
////	char* file_name = "../../PLYFiles/dragon_vrip_352k.ply";
////	char* file_name = "../../PLYFiles/dragon_vrip_1600k.ply";
////	char* file_name = "../../PLYFiles/dragon_vrip_7m.ply";
//	char* file_name = "../../PLYFiles/dragon_vrip_32m.ply";
//	Grid* dragon_ptr = new Grid(new Mesh);
//	//dragon_ptr->read_flat_triangles(file_name);		
//	dragon_ptr->read_smooth_triangles(file_name);
//	dragon_ptr->set_material(phong_ptr); 
//	dragon_ptr->setup_cells();
//	add_object(dragon_ptr);
//	
//	
//	Reflective*	reflective_ptr = new Reflective;			
//	reflective_ptr->set_ka(0.2); 
//	reflective_ptr->set_kd(0.75);
//	reflective_ptr->set_cd(0.5);
//	reflective_ptr->set_ks(0.0);
//	reflective_ptr->set_exp(20);
//	reflective_ptr->set_kr(0.5);  
//	reflective_ptr->set_cr(0.8, 1.0, 0.8);    
//	
//	Plane* plane_ptr = new Plane(Point3D(0, 0.055, 0), Normal(0, 1, 0)); 	
//	plane_ptr->set_material(reflective_ptr);
//	add_object(plane_ptr);	
//}
//
//
//
//
//








//void 												
//World::build(void) {
//	vp.set_hres(400);
//	vp.set_vres(400);
//	vp.set_pixel_size(0.5);
//	
//	background_color = black;
//	tracer_ptr = new MultipleObjects(this);  
//	
//	// colours
//	
//	MyRGBColor yellow(1, 1, 0);										// yellow
//	MyRGBColor brown(0.71, 0.40, 0.16);								// brown
//	MyRGBColor dark_green(0.0, 0.41, 0.41);							// dark_green
//	MyRGBColor orange(1.0, 0.75, 0.0);								// orange
//	MyRGBColor green(0.0, 0.6, 0.3);									// green
//	MyRGBColor light_green(0.65, 1.0, 0.30);							// light green
//	MyRGBColor dark_yellow(0.61, 0.61, 0.0);							// dark yellow
//	MyRGBColor light_purple(0.65, 0.3, 1.0);							// light purple
//	MyRGBColor dark_purple(0.5, 0.0, 1.0);							// dark purple
//	
//	// spheres
//	
//	Sphere*	sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30); 
//	sphere_ptr1->set_color(yellow);	   								// yellow
//	add_object(sphere_ptr1);
//	
//	Sphere*	sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20); 
//	sphere_ptr2->set_color(brown);									// brown
//	add_object(sphere_ptr2);
//	
//	Sphere*	sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17); 
//	sphere_ptr3->set_color(dark_green);								// dark green
//	add_object(sphere_ptr3);
//	
//	Sphere*	sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20); 
//	sphere_ptr4->set_color(orange);									// orange
//	add_object(sphere_ptr4);
//	
//	Sphere*	sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27); 			
//	sphere_ptr5->set_color(green);									// green
//	add_object(sphere_ptr5);
//	
//	Sphere*	sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25); 
//	sphere_ptr6->set_color(light_green);							// light green
//	add_object(sphere_ptr6);
//	
//	Sphere*	sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22); 
//	sphere_ptr7->set_color(green);   								// green
//	add_object(sphere_ptr7);
//	
//	Sphere*	sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);  
//	sphere_ptr8->set_color(brown);									// brown
//	add_object(sphere_ptr8);
//	
//	Sphere*	sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23); 
//	sphere_ptr9->set_color(light_green);							// light green
//	add_object(sphere_ptr9);
//	
//	Sphere*	sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22); 
//	sphere_ptr10->set_color(dark_green);     						// dark green
//	add_object(sphere_ptr10);
//	
//	Sphere*	sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22); 
//	sphere_ptr11->set_color(dark_yellow);							// dark yellow
//	add_object(sphere_ptr11);
//	
//	Sphere*	sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22); 
//	sphere_ptr12->set_color(dark_yellow);							// dark yellow
//	add_object(sphere_ptr12);
//	
//	Sphere*	sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10); 
//	sphere_ptr13->set_color(dark_yellow);
//	add_object(sphere_ptr13);										// dark yellow (hidden)
//	
//	Sphere*	sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18); 
//	sphere_ptr14->set_color(dark_green); 							// dark green
//	add_object(sphere_ptr14);
//	
//	Sphere*	sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18); 
//	sphere_ptr15->set_color(brown); 								// brown
//	add_object(sphere_ptr15);
//	
//	Sphere*	sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10); 
//	sphere_ptr16->set_color(light_purple);							// light purple
//	add_object(sphere_ptr16);
//	
//	Sphere*	sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15); 		
//	sphere_ptr17->set_color(brown);									// browm
//	add_object(sphere_ptr17);
//	
//	Sphere*	sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15); 
//	sphere_ptr18->set_color(dark_purple);							// dark purple
//	add_object(sphere_ptr18);
//	
//	Sphere*	sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17); 
//	sphere_ptr19->set_color(dark_green);							// dark green
//	add_object(sphere_ptr19);
//	
//	Sphere*	sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15); 
//	sphere_ptr20->set_color(brown);									// browm
//	add_object(sphere_ptr20);
//	
//	Sphere*	sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10); 
//	sphere_ptr21->set_color(light_purple);							// light purple
//	add_object(sphere_ptr21);
//	
//	Sphere*	sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12); 
//	sphere_ptr22->set_color(light_purple);							// light purple
//	add_object(sphere_ptr22);
//	
//	Sphere*	sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13); 			
//	sphere_ptr23->set_color(dark_purple);							// dark purple
//	add_object(sphere_ptr23);	
//	
//	Sphere*	sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12); 
//	sphere_ptr24->set_color(light_purple);							// light purple
//	add_object(sphere_ptr24);
//	
//	Sphere*	sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11); 			
//	sphere_ptr25->set_color(green);					 				// green
//	add_object(sphere_ptr25);
//	
//	Sphere*	sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12); 		
//	sphere_ptr26->set_color(light_purple);							// light purple
//	add_object(sphere_ptr26);
//	
//	Sphere*	sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12); 		
//	sphere_ptr27->set_color(light_purple);							// light purple
//	add_object(sphere_ptr27);
//	
//	Sphere*	sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15); 
//	sphere_ptr28->set_color(dark_purple); 							// dark purple
//	add_object(sphere_ptr28);
//	
//	Sphere*	sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15); 
//	sphere_ptr29->set_color(dark_purple);							// dark purple
//	add_object(sphere_ptr29);
//	
//	Sphere*	sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);  
//	sphere_ptr30->set_color(dark_purple); 							// dark purple
//	add_object(sphere_ptr30);
//	
//	Sphere*	sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12); 
//	sphere_ptr31->set_color(light_purple); 							// light purple
//	add_object(sphere_ptr31);
//	
//	Sphere*	sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);   
//	sphere_ptr32->set_color(green);									//  green
//	add_object(sphere_ptr32);
//	
//	Sphere*	sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11); 
//	sphere_ptr33->set_color(green);									// green 
//	add_object(sphere_ptr33);
//	
//	Sphere*	sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10); 	
//	sphere_ptr34->set_color(light_purple);							// light purple
//	add_object(sphere_ptr34);
//	
//	Sphere*	sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12); 
//	sphere_ptr35->set_color(light_purple);							// light purple
//	add_object(sphere_ptr35);
//}
