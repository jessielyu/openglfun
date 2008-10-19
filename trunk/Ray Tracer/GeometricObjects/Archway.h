/*
 *  Archway.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Grid.h"
#include "Material.h"

class Archway: public Grid {
public:
	Archway(const double width,
			const double height,
			const double depth,
			const double column_width,
			const double num_blocks,
			const double num_wedges,
			const double rb,
			 Material* mat_ptr);

	Archway(const Archway& aw);

	virtual Archway*
	clone(void) const;
	
	virtual Archway&
	operator= (const Archway& aw);
	
	virtual
	~Archway(void);
	
	void
	construct_archway(const double width,
					  const double height,
					  const double depth,
					  const double column_width,
					  const double num_blocks,
					  const double num_wedges,
					  const double rb,
					   Material* mat_ptr);

};