#ifndef __NROOKS__
#define __NROOKS__

/*
 *  NRooks.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Sampler.h"

class NRooks: public Sampler {
public:
	
	NRooks(void);
	
	NRooks(const int num_samples);
	
	~NRooks(void);
	
	virtual void		// Gen the samples
	generate_samples(void);
	
	void				// Shuffle the x
	shuffle_x_coordinates(void);
	
	void				// Shuffle the y
	shuffle_y_coordinates(void);
};
#endif