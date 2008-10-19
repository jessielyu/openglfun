/*
 *  Archway.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Archway.h"
#include "BeveledBox.h"
#include "BeveledWedge.h"

Archway::Archway(const double width,
				 const double height,
				 const double depth,
				 const double column_width,
				 const double num_blocks,
				 const double num_wedges,
				 const double rb,
				 Material* mat_ptr) {
	
	construct_archway(width,
					  height,
					  depth,
					  column_width,
					  num_blocks,
					  num_wedges,
					  rb, 
					  mat_ptr);
}

Archway::Archway(const Archway& aw)
:	Grid(aw) {}

Archway*
Archway::clone(void) const {
	return (new Archway(*this));
}

Archway&
Archway::operator= (const Archway& aw) {
	if(this == &aw)
		return (*this);
	
	Grid::operator= (aw);
	
	return (*this);
}

Archway::~Archway(void) {}

void
Archway::construct_archway(const double width,
						   const double height,
						   const double depth,
						   const double column_width,
						   const double num_blocks,
						   const double num_wedges,
						   const double rb,
						   Material* mat_ptr) {
	
	double block_height = (height - width / 2.0) / num_blocks;
	
	// build left column
	
	for (int j = 0; j < num_blocks; j++) {
		Point3D p0(-(height - width / 2.0) + j * block_height, 0.0, - width / 2.0);
		Point3D p1(-(height - width / 2.0) + (j + 1) * block_height, depth, - width / 2.0 + column_width);
		BeveledBox* block_ptr = new BeveledBox(p0, p1, rb, false);
		block_ptr->set_material(mat_ptr);
		add_object(block_ptr);
	}
	
	// build right column
	
	for (int j = 0; j < num_blocks; j++) {
		Point3D p0(-(height - width / 2.0) + j * block_height, 0.0, width / 2.0 - column_width);
		Point3D p1(-(height - width / 2.0) + (j + 1) * block_height, depth, width / 2.0);
		BeveledBox* block_ptr = new BeveledBox(p0, p1, rb, false);
		block_ptr->set_material(mat_ptr);
		add_object(block_ptr);
		
	}
	
	for (int j = 0; j < num_wedges; j++) {
		double angle_width = 180 / num_wedges;	// angle width of each wedge
		double r0 = width / 2.0 - column_width;
		double r1 = width / 2.0;
		double phi0 = j * angle_width;
		double phi1 = (j + 1) * angle_width;
		
		BeveledWedge* wedge_ptr = new BeveledWedge(0.0, depth, r0, r1, rb, phi0, phi1, false);
		wedge_ptr->set_material(mat_ptr);
		add_object(wedge_ptr);
	}
	
	setup_cells();
}


