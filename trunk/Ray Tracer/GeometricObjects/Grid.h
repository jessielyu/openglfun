#ifndef __GRID__
#define __GRID__

/*
 *  Grid.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Compound.h"
#include <vector>

class Grid: public Compound {
public:
	
	Grid(void);
	
	Grid(const Grid& grid);
	
	Grid&
	operator=(const Grid& grid);
	
	~Grid(void);
	
	virtual Grid*								// virtual copy constructor
	clone(void) const;
	
	virtual BBox
	get_bounding_box(void) const;
	
	void
	setup_cells(void);
	
	virtual bool 												 
	hit(const Ray& ray, double& t, ShadeRec& s) const;
	
	virtual bool
	shadow_hit(const Ray& ray, float& tmin) const;
	
//	virtual void
//	set_material(Material* mat_ptr);
	
private:
	
	std::vector<GeometricObject*> cells;		// 1D array
	BBox bbox;
	int nx, ny, nz;			// number of cells in the x, y, and z directions
	
	Point3D 
	min_coordinates(void);
	
	Point3D
	max_coordinates(void);
	
	void
	delete_cells(void);
	
	void
	copy_cells(const std::vector<GeometricObject*>& rhs_cells);
};

#endif