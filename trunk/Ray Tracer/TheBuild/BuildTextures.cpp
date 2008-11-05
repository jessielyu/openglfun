/*
 *  BuildTextures.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/29/08.
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
#include "Image.h"
#include "RectangularMap.h"
#include "CylindricalMap.h"
#include "ImageTexture.h"
#include "SphericalMap.h"

// penguin

//void 												
//World::build(void) {
//	int num_samples = 16;
//	
//	vp.set_hres(400);      
//	vp.set_vres(400);    
//	vp.set_samples(num_samples);	
//	
//	tracer_ptr = new RayCast(this);
//	
//	background_color = black;
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(11, 5, 9);  
//	pinhole_ptr->set_view_distance(1600.0);
//	pinhole_ptr->set_lookat(0, -0.5, 0);
//	//pinhole_ptr->set_zoom(.1);
//	pinhole_ptr->compute_uvw();     
//	set_camera(pinhole_ptr); 
//	
//	
//	Directional* directional_ptr = new Directional;
//	directional_ptr->set_direction(0.75, 1, -0.15);     
//	directional_ptr->scale_radiance(4.5); 
//	directional_ptr->set_shadows(true);
//	add_light(directional_ptr);
//	
//	Image* image_ptr = new Image;						
//	
//	//image_ptr->read_ppm_file("../../TextureFiles/ppm/BlueGlass.ppm");
//	image_ptr->read_ppm_file("../../TextureFiles/ppm/Lightlace.ppm");
//	//image_ptr->read_ppm_file("../../TextureFiles/ppm/penguin_body.ppm");
//	
//	ImageTexture* texture_ptr = new ImageTexture; 
//	texture_ptr->set_image(image_ptr);
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;		
//	sv_matte_ptr->set_ka(0.1);
//	sv_matte_ptr->set_kd(0.75);
//	sv_matte_ptr->set_cd(texture_ptr);
//	
//	char* file_name = "../../PLYFiles/TwoUVTriangles.ply";
//	//char* file_name = "../../PLYFiles/penguin_body.ply";
//	Grid* grid_ptr = new Grid(new Mesh);
//	//grid_ptr->read_flat_uv_triangles(file_name);		// for Figure 29.22(a)
//		grid_ptr->read_smooth_uv_triangles(file_name);		// for Figure 29.22(b)
//	grid_ptr->set_material(sv_matte_ptr);   
//	grid_ptr->setup_cells();
//	add_object(grid_ptr);
//	
//	
//	Matte* matte_ptr = new Matte;			
//	matte_ptr->set_cd(1, 0.9, 0.6);
//	matte_ptr->set_ka(0.25); 
//	matte_ptr->set_kd(0.4);
//	
//	Plane* plane_ptr1 = new Plane(Point3D(0, -2.0, 0), Normal(0, 1, 0));  
//	plane_ptr1->set_material(matte_ptr);
//	add_object(plane_ptr1);	
//}




//square

//void 												
//World::build(void) {
//	int num_samples = 16;
//	
//	vp.set_hres(400);
//	vp.set_vres(400); 
//	vp.set_samples(num_samples);
//	vp.set_max_depth(0);
//	
//	background_color = MyRGBColor(0.0);
//	
//	tracer_ptr = new RayCast(this);
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(5, 1.5, 8);
//	pinhole_ptr->set_lookat(0.25, 0.0, 0.0); 
//	pinhole_ptr->set_view_distance(1000.0);
//	pinhole_ptr->compute_uvw();
//	set_camera(pinhole_ptr);
//	
//	Directional* light_ptr = new Directional;
//	light_ptr->set_direction(-15, 20, 25);  
//	light_ptr->scale_radiance(2.5);  
//	light_ptr->set_shadows(true);
//	add_light(light_ptr);
//	
//	// image:
//	
//	Image* image_ptr = new Image;					
//	image_ptr->read_ppm_file("../../TextureFiles/ppm/Lightlace.ppm");
//	
//	// mapping:
//	
//	RectangularMap* map_ptr = new RectangularMap;   
//	
//	// image texture:
//	
//	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
//	texture_ptr->set_mapping(map_ptr);
//	
//	// spatially varying material:
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;		
//	sv_matte_ptr->set_ka(0.40);
//	sv_matte_ptr->set_kd(0.95);
//	sv_matte_ptr->set_cd(texture_ptr);
//	
//	// generic rectangle:
//	
//	Rectangle* rectangle_ptr = new Rectangle;
//	rectangle_ptr->set_material(sv_matte_ptr);
//	
//	// transformed rectangle:
//	
//	Instance* lightlace_ptr = new Instance(rectangle_ptr);  
//	lightlace_ptr->transform_texture(true);
//	lightlace_ptr->scale(1.0, 1.0, 1.5);
//	lightlace_ptr->rotate_z(90);
//	lightlace_ptr->rotate_y(90);
//	add_object(lightlace_ptr);
//	
//	// ground plane
//	
//	Matte* matte_ptr1 = new Matte;		
//	matte_ptr1->set_ka(0.25);
//	matte_ptr1->set_kd(0.5);
//	matte_ptr1->set_cd(1.0);
//	
//	Plane* plane_ptr = new Plane(Point3D(0.0, -1.0, 0.0), Normal(0.0, 1.0, 0.0));
//	plane_ptr->set_material(matte_ptr1);
//	add_object(plane_ptr);
//}


// This biuilds the scene for Figure 29.6

// cylinder

//void 												
//World::build(void) {
//	int num_samples = 16;
//	
//	vp.set_hres(400);
//	vp.set_vres(400); 
//	vp.set_samples(num_samples);
//	vp.set_max_depth(0);
//	
//	background_color = MyRGBColor(0.5);
//	
//	tracer_ptr = new RayCast(this);
//	
//	Pinhole* pinhole_ptr = new Pinhole;
//	pinhole_ptr->set_eye(2, 3.5, 5);
//	pinhole_ptr->set_lookat(0); 
//	pinhole_ptr->set_view_distance(800.0);
//	pinhole_ptr->compute_uvw();
//	set_camera(pinhole_ptr);
//	
//	Directional* light_ptr = new Directional;
//	light_ptr->set_direction(14, 20, 25);  
//	light_ptr->scale_radiance(1.75);  
//	light_ptr->set_shadows(true);
//	add_light(light_ptr);
//	
//	Image* image_ptr = new Image;					
//	image_ptr->read_ppm_file("../../TextureFiles/ppm/CountryScene.ppm");
//	CylindricalMap* map_ptr = new CylindricalMap;   
//	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
//	texture_ptr->set_mapping(map_ptr);
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;		
//	sv_matte_ptr->set_ka(0.40);
//	sv_matte_ptr->set_kd(0.95);
//	sv_matte_ptr->set_cd(texture_ptr);
//	
//	OpenCylinder* cylinder_ptr = new OpenCylinder;
//	cylinder_ptr->set_material(sv_matte_ptr); 
//	add_object(cylinder_ptr);
//}

// spherical map

//void 												
//World::build(void) {
//	int num_samples = 16;
//	
//	vp.set_hres(400);      
//	vp.set_vres(400);    
//	vp.set_samples(num_samples);
//	
//	background_color = black;
//	
//	tracer_ptr = new RayCast(this);
//	
//	Pinhole* camera_ptr = new Pinhole;
//	camera_ptr->set_eye(0, 0, -65); 				
//	camera_ptr->set_lookat(0.0); 
//	camera_ptr->set_view_distance(21000.0);
//	camera_ptr->compute_uvw();     
//	camera_ptr->set_zoom(4.0/7.0);
//	set_camera(camera_ptr); 
//	
//	
//	Directional* light_ptr = new Directional;
//	light_ptr->set_direction(-0.25, 0.4, -1);		
//	light_ptr->scale_radiance(2.5); 
//	add_light(light_ptr);
//	
//	
//	// image:					
//	
//	Image* image_ptr = new Image;				
//	//	image_ptr->read_ppm_file("EarthLowRes.ppm");
//	image_ptr->read_ppm_file("../../TextureFiles/ppm/EarthHighRes.ppm");
//	
//	
//	// mapping:
//	
//	SphericalMap* map_ptr = new SphericalMap; 
//	
//	
//	// image based texture:  
//	
//	ImageTexture* texture_ptr = new ImageTexture; 
//	texture_ptr->set_image(image_ptr); 
//	texture_ptr->set_mapping(map_ptr);
//	
//	
//	// textured material:
//	
//	SV_Matte* sv_matte_ptr = new SV_Matte;		
//	sv_matte_ptr->set_ka(0.2);
//	sv_matte_ptr->set_kd(0.8);
//	sv_matte_ptr->set_cd(texture_ptr);
//	
//	
//	// generic sphere:
//	
//	Sphere*	sphere_ptr = new Sphere; 
//	sphere_ptr->set_material(sv_matte_ptr);
//	
//	
//	// rotated sphere
//	
//	Instance* earth_ptr = new Instance(sphere_ptr);
//	earth_ptr->rotate_y(60);
//	add_object(earth_ptr);
//}
//
//
