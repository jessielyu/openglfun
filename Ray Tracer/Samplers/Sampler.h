#ifndef __SAMPLER__
#define __SAMPLER__

/*
 *  Sampler.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
#include <vector>

#include "Point2D.h"

#include "Maths.h"

#include "Point3D.h"

class Sampler {

public:

	//constructors, access functions, etc
	
	Sampler(void);
	
	Sampler(const int num);
	
	Sampler(const int samples, const int sets);
	
	Sampler& 
	operator= (const Sampler& rhs);		
	
	virtual
	~Sampler(void);
	
	virtual void	// generate sample patterns in a unit square
	generate_samples(void) = 0;
	
	void			// mapping samples to a disk/circle
	map_samples_to_unit_disk(void);
	
	void			// mapping samples to a hemisphere
	map_samples_to_hemisphere(const float e);
	
	void			// set up the randomly shuffled indices
	setup_shuffled_indices(void);
	
	void			// randomly shuffle the samples in each pattern
	shuffle_samples(void);
	
	Point2D			// get next sample on unit square
	sample_unit_square(void);
	
	Point2D			// get next sample on unit disk
	sample_unit_disk(void);
	
	Point3D			// get next sample on hemisphere
	sample_hemisphere(void);
	
	int				// get the number of samples
	get_num_samples(void);
	
protected:
	
	int num_samples;	// the number of sample points in a pattern
	int num_sets;	// the number of sample sets (patterns) stored
	std::vector <Point2D> samples; //sample points on a unit square
	std::vector <Point2D> disk_samples; //sample points on a unit disk
	std::vector <Point3D> hemisphere_samples; //sample points on a hemisphere disk
	std::vector <int> shuffled_indices;	// shuffled samples array indices
	unsigned long count;	//current number of sample points used
	int jump;	//random index jump
};

inline int
Sampler::get_num_samples(void) {
	return num_samples;
}

#endif