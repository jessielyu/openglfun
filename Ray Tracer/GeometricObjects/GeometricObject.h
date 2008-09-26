#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

// this file contains the declaration of the class GeometricObject

#include "MyRGBColor.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "ShadeRec.h"

#include "Constants.h"
#include "Material.h"
					

class GeometricObject {	
	
public:	

	GeometricObject(void);									// default constructor
	
	GeometricObject(const GeometricObject& object);			// copy constructor

	virtual GeometricObject*								// virtual copy constructor
	clone(void) const = 0;

	virtual 												// destructor
	~GeometricObject (void);	
		
	virtual bool 												 
	hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
	

	// the following three functions are only required for Chapter 3
	
	void
	set_color(const MyRGBColor& c);
			
	void
	set_color(const float r, const float g, const float b);
	
	MyRGBColor
	get_color(void);

	void
	set_material(Material* material);

	Material*
	get_material(void);

	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const = 0;
	
	void
	set_shadows(const bool shadow);
	
	bool
	get_shadows(void);


protected:

	MyRGBColor   color;						// only used for Bare Bones ray tracing

	GeometricObject&						// assignment operator
	operator= (const GeometricObject& rhs);

	Material* material_ptr;
	
	bool shadows;							// whether or not the object casts shadows
};


// --------------------------------------------------------------------  set_colour

inline void
GeometricObject::set_color(const MyRGBColor& c) {
	color = c;
}

// --------------------------------------------------------------------  set_colour

inline void 
GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

// --------------------------------------------------------------------  get_colour

inline void
GeometricObject::set_shadows(const bool shaodow) {
	shadows = shadow;
}

inline bool
GeometricObject::get_shadows(void) {
	return shadows;
}

inline MyRGBColor 
GeometricObject::get_color(void) {
	return (color);
}

inline void
GeometricObject::set_material(Material* material) {
	material_ptr = material;
}

inline Material*
GeometricObject::get_material(void) {
	return material_ptr;
}

#endif
