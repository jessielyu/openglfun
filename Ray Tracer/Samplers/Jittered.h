#ifndef __JITTERED__
#define __JITTERED__

/*
 *  Jittered.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Sampler.h"

class Jittered: public Sampler {

public:
	
	Jittered(void);
	Jittered(const int num_samples);
	
private:
	
	virtual void
	generate_samples(void);
	
};

#endif