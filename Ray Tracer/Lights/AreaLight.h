#ifndef __AREA_LIGHT__
#define __AREA_LIGHT__

/*
 *  AreaLight.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Light.h"
#include "GeometricObject.h"
#include "Material.h"

class AreaLight: public Light {
public:
	
	AreaLight(void);
	
	AreaLight(const AreaLight& al);
	
	AreaLight&
	operator= (const AreaLight& al);
	
	~AreaLight(void);
	
	AreaLight*
	clone(void) const;
	
	virtual Vector3D
	get_direction(ShadeRec& sr);
	
	virtual bool
	in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
	virtual float
	G(const ShadeRec& sr) const;
	
	virtual float
	pdf(const ShadeRec& sr) const;
	
	void 									
	set_object(GeometricObject* obj_ptr);
	
private:
	
	GeometricObject* object_ptr;
	Material* material_ptr;			// emissive material
	Point3D sample_point;			// sample point on surface
	Normal light_normal;			// normal at sample point
	Vector3D wi;					// unit vector from hit point to sample point

};

inline void 									
AreaLight::set_object(GeometricObject* obj_ptr) {
	object_ptr = obj_ptr;
	material_ptr = object_ptr->get_material();	
}

#endif