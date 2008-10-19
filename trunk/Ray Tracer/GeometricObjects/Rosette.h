#ifndef __ROSETTE__
#define __ROSETTE__

/*
 *  Rosette.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Grid.h"
#include "Material.h"

class Rosette: public Grid {
public:
	Rosette(void);
	
	Rosette(const int num_rings,
			const double hole_radius,
			const double ring_width,
			const double rb,
			const double y0,
			const double y1,
			Material* mat_ptr);
	
	Rosette(const Rosette& bb);
	
	virtual Rosette*
	clone(void) const;
	
	Rosette&
	operator= (const Rosette& rhs);
	
	virtual 
	~Rosette(void);
	
	void construct_rosette(const int num_rings,
						   const double hole_radius,
						   const double ring_width,
						   const double rb,
						   const double y0,
						   const double y1,
						   Material* mat_ptr);

private:
	static const int num_wedges[6];  // number of wedges in each ring
};

#endif