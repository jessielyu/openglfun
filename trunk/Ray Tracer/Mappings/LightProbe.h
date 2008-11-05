#ifndef __LIGHT_PROBE__
#define __LIGHT_PROBE__

/*
 *  LightProbe.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/29/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Constants.h"
#include "Mapping.h"

enum type {
	regular,
	panoramic
};

class LightProbe: public Mapping {		
public:
	
	LightProbe(void);									
	
	LightProbe(const LightProbe& sm);					
	
	LightProbe& 											
	operator= (const LightProbe& rhs);		
	
	virtual LightProbe*									
	clone(void) const;				
	
	~LightProbe(void);									
	
	virtual void
	get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
						  const 	int 		xres, 
						  const 	int 		yres, 
						  int& 		row, 
						  int& 		column) const;
	
	void
	set_map_type(const type t);
	
private:
	
	type map_type;
};

inline void
LightProbe::set_map_type(const type t) {
	map_type = t;
}

#endif