/*
 *  BeveledBox.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "BeveledBox.h"
#include "Rectangle.h"
#include "OpenCylinder.h"
#include "Instance.h"
#include "Sphere.h"

BeveledBox::BeveledBox(void)
:	Compound() {
	
	Point3D p0 = (-1,-1,-1);	// min corner
	Point3D p1 = (1,1,1);		// max corner
	float rb = (0.25);		// bevel radius
	
	// Edges
	
	// Top Front Edge
	Instance* top_front_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));
	top_front_edge->rotate_z(90);
	top_front_edge->translate((p0.x + p1.x) / 2, p1.y - rb, p1.z - rb);
	top_front_edge->transform_texture(false);
	top_front_edge->compute_bounding_box();
	objects.push_back(top_front_edge);
	
	// Top Front Edge
	Instance* top_back_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));
	top_back_edge->rotate_z(90);
	top_back_edge->translate((p0.x + p1.x) / 2, p1.y - rb, p0.z + rb);
	top_back_edge->transform_texture(false);
	top_back_edge->compute_bounding_box();
	objects.push_back(top_back_edge);
	
	// Top Right Edge
	Instance* top_right_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb));
	top_right_edge->rotate_x(90);
	top_right_edge->translate(p1.x - rb, p1.y - rb, (p0.z + p1.z) / rb);
	top_right_edge->transform_texture(false);
	top_right_edge->compute_bounding_box();
	objects.push_back(top_right_edge);
	
	// Top Right Edge
	Instance* top_left_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb));
	top_left_edge->rotate_x(90);
	top_left_edge->translate(p0.x + rb, p1.y - rb, (p0.z + p1.z) / rb);
	top_left_edge->transform_texture(false);
	top_left_edge->compute_bounding_box();
	objects.push_back(top_left_edge);
	
	// Bottom Front Edge
	Instance* bottom_front_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));
	bottom_front_edge->rotate_z(90);
	bottom_front_edge->translate((p0.x + p1.x) / 2, p0.y + rb, p1.z - rb);
	bottom_front_edge->transform_texture(false);
	bottom_front_edge->compute_bounding_box();
	objects.push_back(bottom_front_edge);
	
	// Bottom Front Edge
	Instance* bottom_back_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));
	bottom_back_edge->rotate_z(90);
	bottom_back_edge->translate((p0.x + p1.x) / 2, p0.y + rb, p0.z + rb);
	bottom_back_edge->transform_texture(false);
	bottom_back_edge->compute_bounding_box();
	objects.push_back(bottom_back_edge);
	
	// Bottom Right Edge
	Instance* bottom_right_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb));
	bottom_right_edge->rotate_x(90);
	bottom_right_edge->translate(p1.x - rb, p0.y + rb, (p0.z + p1.z) / rb);
	bottom_right_edge->transform_texture(false);
	bottom_right_edge->compute_bounding_box();
	objects.push_back(bottom_right_edge);
	
	// Bottom Right Edge
	Instance* bottom_left_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb));
	bottom_left_edge->rotate_x(90);
	bottom_left_edge->translate(p0.x + rb, p0.y + rb, (p0.z + p1.z) / rb);
	bottom_left_edge->transform_texture(false);
	bottom_left_edge->compute_bounding_box();
	objects.push_back(bottom_left_edge);
	
	// Vertical Edges
	
	// Vertical right front
	Instance* vertical_right_front_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_right_front_edge->translate(p1.x - rb, 0, p1.z - rb);
	vertical_right_front_edge->transform_texture(false);
	objects.push_back(vertical_right_front_edge);
	
	// Vertical left front
	Instance* vertical_left_front_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_left_front_edge->translate(p0.x + rb, 0, p1.z - rb);
	vertical_left_front_edge->transform_texture(false);
	objects.push_back(vertical_left_front_edge);
	
	// Vertical right rear
	Instance* vertical_right_rear_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_right_rear_edge->translate(p1.x - rb, 0, p0.z + rb);
	vertical_right_rear_edge->transform_texture(false);
	objects.push_back(vertical_right_rear_edge);
	
	// Vertical left rear
	Instance* vertical_left_rear_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_left_rear_edge->translate(p0.x + rb, 0, p0.z + rb);
	vertical_left_rear_edge->transform_texture(false);
	objects.push_back(vertical_left_rear_edge);
	
	// Corner Spheres
	
	// Top Right Front corner
	Sphere* top_right_front_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p1.z - rb), rb);
	objects.push_back(top_right_front_corner);
	
	// Top left Front corner
	Sphere* top_left_front_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p1.z - rb), rb);
	objects.push_back(top_left_front_corner);
	
	// Bottom Right Front corner
	Sphere* bottom_right_front_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p1.z - rb), rb);
	objects.push_back(bottom_right_front_corner);
	
	// Bottom left Front corner
	Sphere* bottom_left_front_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p1.z - rb), rb);
	objects.push_back(bottom_left_front_corner);		
	
	// Top Right Rear corner
	Sphere* top_right_rear_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p0.z + rb), rb);
	objects.push_back(top_right_rear_corner);
	
	// Top left Rear corner
	Sphere* top_left_rear_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p0.z + rb), rb);
	objects.push_back(top_left_rear_corner);
	
	// Bottom Right Rear corner
	Sphere* bottom_right_rear_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p0.z + rb), rb);
	objects.push_back(bottom_right_rear_corner);
	
	// Bottom left Rear corner
	Sphere* bottom_left_rear_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p0.z + rb), rb);
	objects.push_back(bottom_left_rear_corner);		
	
	// Faces
	
	// Bottom Face
	Rectangle* bottom_face = new Rectangle(Point3D(p0.x + rb, p0.y, p0.z + rb), 
										   Vector3D(0,0, (p1.z - rb) - (p0.z + rb)),
										   Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
										   Normal(0, -1, 0));
	objects.push_back(bottom_face);
	
	// Top Face
	Rectangle* top_face = new Rectangle(Point3D(p0.x + rb, p1.y, p0.z + rb), 
										Vector3D(0,0, (p1.z - rb) - (p0.z + rb)),
										Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
										Normal(0, 1, 0));
	objects.push_back(top_face);
	
	// Back Face
	Rectangle* back_face = new Rectangle(Point3D(p0.x + rb, p0.y + rb, p0.z),
										 Vector3D((p1.x - rb) - (p0.x +rb), 0, 0),
										 Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
										 Normal(0, 0, -1));
	objects.push_back(back_face);
	
	// Front Face
	Rectangle* front_face = new Rectangle(Point3D(p0.x + rb, p0.y + rb, p1.z),
										  Vector3D((p1.x - rb) - (p0.x +rb), 0, 0),
										  Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
										  Normal(0, 0, 1));
	objects.push_back(front_face);
	
	// Left Face
	Rectangle* left_face = new Rectangle(Point3D(p0.x, p0.y + rb, p0.z + rb),
										 Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
										 Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
										 Normal(1, 0, 0));
	objects.push_back(left_face);
	
	//Right Face
	Rectangle* right_face = new Rectangle(Point3D(p1.x, p0.y + rb, p0.z + rb),
										  Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
										  Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
										  Normal(1, 0, 0));
	objects.push_back(right_face);
}

BeveledBox::BeveledBox(const Point3D p0, const Point3D p1, const float rb, const bool wireframe)
:	Compound(),
	bbox(p0, p1) {
	
	// Edges
	
	// Top Front Edge
	Instance* top_front_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));
	top_front_edge->rotate_z(90);
	top_front_edge->translate((p0.x + p1.x) / 2, p1.y - rb, p1.z - rb);
	top_front_edge->transform_texture(false);
	top_front_edge->compute_bounding_box();
	objects.push_back(top_front_edge);
	
	// Top Front Edge
	Instance* top_back_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));
	top_back_edge->rotate_z(90);
	top_back_edge->translate((p0.x + p1.x) / 2, p1.y - rb, p0.z + rb);
	top_back_edge->transform_texture(false);
	top_back_edge->compute_bounding_box();
	objects.push_back(top_back_edge);
		
	// Top Right Edge
	Instance* top_right_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb));
	top_right_edge->rotate_x(90);
	top_right_edge->translate(p1.x - rb, p1.y - rb, (p0.z + p1.z) / rb);
	top_right_edge->transform_texture(false);
	top_right_edge->compute_bounding_box();
	objects.push_back(top_right_edge);
		
	// Top Right Edge
	Instance* top_left_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb));
	top_left_edge->rotate_x(90);
	top_left_edge->translate(p0.x + rb, p1.y - rb, (p0.z + p1.z) / rb);
	top_left_edge->transform_texture(false);
	top_left_edge->compute_bounding_box();
	objects.push_back(top_left_edge);
		
	// Bottom Front Edge
	Instance* bottom_front_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));
	bottom_front_edge->rotate_z(90);
	bottom_front_edge->translate((p0.x + p1.x) / 2, p0.y + rb, p1.z - rb);
	bottom_front_edge->transform_texture(false);
	bottom_front_edge->compute_bounding_box();
	objects.push_back(bottom_front_edge);
	
	// Bottom Front Edge
	Instance* bottom_back_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));
	bottom_back_edge->rotate_z(90);
	bottom_back_edge->translate((p0.x + p1.x) / 2, p0.y + rb, p0.z + rb);
	bottom_back_edge->transform_texture(false);
	bottom_back_edge->compute_bounding_box();
	objects.push_back(bottom_back_edge);
	
	// Bottom Right Edge
	Instance* bottom_right_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb));
	bottom_right_edge->rotate_x(90);
	bottom_right_edge->translate(p1.x - rb, p0.y + rb, (p0.z + p1.z) / rb);
	bottom_right_edge->transform_texture(false);
	bottom_right_edge->compute_bounding_box();
	objects.push_back(bottom_right_edge);
	
	// Bottom Right Edge
	Instance* bottom_left_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb));
	bottom_left_edge->rotate_x(90);
	bottom_left_edge->translate(p0.x + rb, p0.y + rb, (p0.z + p1.z) / rb);
	bottom_left_edge->transform_texture(false);
	bottom_left_edge->compute_bounding_box();
	objects.push_back(bottom_left_edge);
		
	// Vertical Edges
		
	// Vertical right front
	Instance* vertical_right_front_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_right_front_edge->translate(p1.x - rb, 0, p1.z - rb);
	vertical_right_front_edge->transform_texture(false);
	objects.push_back(vertical_right_front_edge);
	
	// Vertical left front
	Instance* vertical_left_front_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_left_front_edge->translate(p0.x + rb, 0, p1.z - rb);
	vertical_left_front_edge->transform_texture(false);
	objects.push_back(vertical_left_front_edge);
		
	// Vertical right rear
	Instance* vertical_right_rear_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_right_rear_edge->translate(p1.x - rb, 0, p0.z + rb);
	vertical_right_rear_edge->transform_texture(false);
	objects.push_back(vertical_right_rear_edge);
	
	// Vertical left rear
	Instance* vertical_left_rear_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_left_rear_edge->translate(p0.x + rb, 0, p0.z + rb);
	vertical_left_rear_edge->transform_texture(false);
	objects.push_back(vertical_left_rear_edge);
		
	// Corner Spheres
		
	// Top Right Front corner
	Sphere* top_right_front_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p1.z - rb), rb);
	objects.push_back(top_right_front_corner);
		
	// Top left Front corner
	Sphere* top_left_front_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p1.z - rb), rb);
	objects.push_back(top_left_front_corner);
		
	// Bottom Right Front corner
	Sphere* bottom_right_front_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p1.z - rb), rb);
	objects.push_back(bottom_right_front_corner);
	
	// Bottom left Front corner
	Sphere* bottom_left_front_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p1.z - rb), rb);
	objects.push_back(bottom_left_front_corner);		
		
	// Top Right Rear corner
	Sphere* top_right_rear_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p0.z + rb), rb);
	objects.push_back(top_right_rear_corner);
	
	// Top left Rear corner
	Sphere* top_left_rear_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p0.z + rb), rb);
	objects.push_back(top_left_rear_corner);
	
	// Bottom Right Rear corner
	Sphere* bottom_right_rear_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p0.z + rb), rb);
	objects.push_back(bottom_right_rear_corner);
	
	// Bottom left Rear corner
	Sphere* bottom_left_rear_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p0.z + rb), rb);
	objects.push_back(bottom_left_rear_corner);		
	
	if(!wireframe) {
		// Faces
			
		// Bottom Face
		Rectangle* bottom_face = new Rectangle(Point3D(p0.x + rb, p0.y, p0.z + rb), 
			Vector3D(0,0, (p1.z - rb) - (p0.z + rb)),
			Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
			Normal(0, -1, 0));
		objects.push_back(bottom_face);
			
		// Top Face
		Rectangle* top_face = new Rectangle(Point3D(p0.x + rb, p1.y, p0.z + rb), 
											   Vector3D(0,0, (p1.z - rb) - (p0.z + rb)),
											   Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
											   Normal(0, 1, 0));
		objects.push_back(top_face);
			
		// Back Face
		Rectangle* back_face = new Rectangle(Point3D(p0.x + rb, p0.y + rb, p0.z),
		Vector3D((p1.x - rb) - (p0.x +rb), 0, 0),
		Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
										 Normal(0, 0, -1));
		objects.push_back(back_face);
		
		// Front Face
		Rectangle* front_face = new Rectangle(Point3D(p0.x + rb, p0.y + rb, p1.z),
											 Vector3D((p1.x - rb) - (p0.x +rb), 0, 0),
											 Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
											 Normal(0, 0, 1));
		objects.push_back(front_face);
		
		// Left Face
		Rectangle* left_face = new Rectangle(Point3D(p0.x, p0.y + rb, p0.z + rb),
		Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
		Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
											 Normal(1, 0, 0));
		objects.push_back(left_face);
		
		//Right Face
		Rectangle* right_face = new Rectangle(Point3D(p1.x, p0.y + rb, p0.z + rb),
											 Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
											 Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
											 Normal(1, 0, 0));
		objects.push_back(right_face);
	}
}

BeveledBox::BeveledBox(const BeveledBox& cc)
:	Compound(cc),
bbox(cc.bbox) {}

BeveledBox&
BeveledBox::operator= (const BeveledBox& cc) {
	if (this == &cc)
		return (*this);
	
	Compound::operator= (cc);
	
	bbox = cc.bbox;
	
	return (*this);
}

BeveledBox*
BeveledBox::clone(void) const {
	return (new BeveledBox(*this));
}

bool
BeveledBox::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

bool
BeveledBox::shadow_hit(const Ray& ray, float& tmin) const {
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

BBox
BeveledBox::get_bounding_box(void) const {
	return bbox;
}