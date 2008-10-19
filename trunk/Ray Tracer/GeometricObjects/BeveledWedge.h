#ifndef __BEVELED_WEDGE__
#define __BEVELED_WEDGE__

/*
 *  BeveledWedge.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */	

#include "Compound.h"

//-------------------------------------------------------------------------------- class BeveledWedge

class BeveledWedge: public Compound {
public:
	
	BeveledWedge(	const double y0,		// minimum y value
				 const double y1,		// minimum y value
				 const double r0,		// inner radius
				 const double r1,		// outer radius
				 const double rb,		// bevel radius
				 const double phi0,		// minimum azimuth angle in degrees
				 const double phi1,
				 bool wireframe);		// maximum azimuth angle
	
	
	BeveledWedge(const BeveledWedge& bw); 				
	
	virtual BeveledWedge* 								
	clone(void) const;
	
	virtual BeveledWedge& 								
	operator= (const BeveledWedge& rhs);		
	
	virtual 											
	~BeveledWedge(void); 
	
	virtual BBox 
	get_bounding_box(void) const;
	
	virtual bool 																						 
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	
private:
	
	BBox	bbox;	// bounding box
};

#endif
