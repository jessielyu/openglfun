/*
 *  Rosette.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Rosette.h"
#include "BeveledWedge.h"

const int Rosette::num_wedges[6] = {10, 12, 15, 18, 24, 36};  // these numbers exactly divide into 360

Rosette::Rosette(void)
:	Grid() {
	construct_rosette(1, 1.0, 1.0, 0.25, -1.0, 1.0, NULL);
}

Rosette::Rosette(const int num_rings,
				 const double hole_radius,
				 const double ring_width,
				 const double rb,
				 const double y0,
				 const double y1,
				 Material* mat_ptr)
:	Grid() {
	construct_rosette( num_rings,
					   hole_radius,
					   ring_width,
					   rb,
					   y0,
					  y1,
					  mat_ptr);
}

Rosette::Rosette(const Rosette& r)
:	Grid(r) {}

Rosette*
Rosette::clone(void) const {
	return (new Rosette(*this));
}

Rosette&
Rosette::operator= (const Rosette& r) {
	if (this == &r)
		return (*this);
	
	Grid::operator= (r);
	
	return (*this);
}

Rosette::~Rosette(void) {}

void
Rosette::construct_rosette(const int num_rings,
						   const double hole_radius,
						   const double ring_width,
						   const double rb,
						   const double y0,
						   const double y1,
						   Material* mat_ptr) {
	for (int k = 0; k < num_rings; k++) {
		for (int j = 0; j < num_wedges[k]; j++) {
			double angle_width = 360 / num_wedges[k];  // the azimuth angle extent of each wedge
			double r0 = hole_radius + k * ring_width;
			double r1 = hole_radius + (k + 1) * ring_width;
			double phi0 = j * angle_width;
			
			double phi1 = (j + 1) * angle_width;
			
			BeveledWedge* wedge_ptr = new BeveledWedge(y0, y1, r0, r1, rb, phi0, phi1, false);
			wedge_ptr->set_material(mat_ptr);
			add_object(wedge_ptr);
		}
	}
	
	setup_cells();
}