#ifndef __COMPOUND__
#define __COMPOUND__

/*
 *  Compound.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "GeometricObject.h"
#include <vector>

class Compound: public GeometricObject {
public:
	
	Compound(void);
	
	virtual Compound*
	clone(void) const;
	
	Compound(const Compound& c);
	
	~Compound(void);
	
	Compound&
	operator= (const Compound& c);
	
	virtual void
	set_material(Material* mat_ptr);
	
	virtual void
	add_object(GeometricObject* obj_ptr);
	
	int
	get_num_objects(void);
	
	virtual bool
	hit(const Ray& ray, double& tmin, ShadeRec& s) const;
	
	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const;
	
protected:
	
	std::vector<GeometricObject*> objects;
	
private:
	
	void
	delete_objects(void);
	
	void
	copy_objects(const std::vector<GeometricObject*>& rhs_objects);
	
};

inline int
Compound::get_num_objects(void) {
	return objects.size();
}

#endif