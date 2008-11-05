#ifndef __RECTANGULAR_MAP__
#define __RECTANGULAR_MAP__

/*
 *  RectangularMap.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Constants.h"
#include "Mapping.h"

class RectangularMap: public Mapping {		
public:
	
	RectangularMap(void);									
	
	RectangularMap(const RectangularMap& sm);					
	
	RectangularMap& 											
	operator= (const RectangularMap& rhs);		
	
	virtual RectangularMap*									
	clone(void) const;				
	
	~RectangularMap(void);									
	
	virtual void
	get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
						  const 	int 		xres, 
						  const 	int 		yres, 
						  int& 		row, 
						  int& 		column) const;
};

#endif
