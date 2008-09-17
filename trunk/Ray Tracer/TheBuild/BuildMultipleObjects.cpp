#include "World.h"
#include "MultipleObjects.h"
#include "Plane.h"

// samplers
#include "Jittered.h"
#include "Pinhole.h"
#include "ThinLens.h"

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(400);
	vp.set_vres(400);
	//vp.set_sampler(new Jittered(num_samples));
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples);
	
	// PinholeCamera
	//Pinhole* camera_ptr = new Pinhole(Point3D(300, 400, 500), Point3D(0, 0, -50), Vector3D(0, 1, 0), 400, 1.0);
	//Pinhole* camera_ptr = new Pinhole(Point3D(-1000, 2000, -500), Point3D(0, -100, 0), Vector3D(0, 1, 0), 250, 1.0);
	//Pinhole* camera_ptr = new Pinhole(Point3D(0, 0, 500), Point3D(0, 0, 0), Vector3D(0, 1, 0), 500, 1.0);
	//Pinhole* camera_ptr = new Pinhole(Point3D(0, 1000, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 500, 1.0);
	
	// ThinLens camera
	//ThinLens(const Point3D e, const Point3D l, const Vector3D u, float lr, float distance, float focal, float z)
	//ThinLens* camera_ptr = new ThinLens(Point3D(0, 6, 50), Point3D(0, 6, 0), Vector3D(0, -1, 0), 1.0, 40.0, 74);
	ThinLens* camera_ptr = new ThinLens(Point3D(0, 6, 100), Point3D(0, 6, 0), Vector3D(0, 1, 0), 3.0, 40.0, 74);	// GOOD
	camera_ptr->set_sampler(vp.sampler_ptr);
	
	camera_ptr->compute_uvw();
	set_camera(camera_ptr);
	
	tracer_ptr = new MultipleObjects(this); 
	
	background_color = MyRGBColor(black);
	
	// use access functions to set centre and radius
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80);
	sphere_ptr->set_color(1, 0, 0);  // red
	add_object(sphere_ptr);

	// use constructor to set centre and radius 
	
	sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	add_object(sphere_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 1));
	plane_ptr->set_color(0.0, 0.3, 0.0);	// dark green
	add_object(plane_ptr);
	
//	MyRGBColor yellow(1, 1, 0);										// yellow
//	MyRGBColor brown(0.71, 0.40, 0.16);								// brown
//	MyRGBColor dark_green(0.0, 0.41, 0.41);							// dark_green
//	MyRGBColor orange(1, 0.75, 0);									// orange
//	MyRGBColor green(0, 0.6, 0.3);									// green
//	MyRGBColor light_green(0.65, 1, 0.30);							// light green
//	MyRGBColor dark_yellow(0.61, 0.61, 0);							// dark yellow
//	MyRGBColor light_purple(0.65, 0.3, 1);							// light purple
//	MyRGBColor dark_purple(0.5, 0, 1);								// dark purple
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
//	sphere_ptr6->set_color(light_green);								// light green
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
//	sphere_ptr9->set_color(light_green);								// light green
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
//	sphere_ptr19->set_color(dark_green);								// dark green
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
}
