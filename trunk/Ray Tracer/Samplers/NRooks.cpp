/*
 *  NRooks.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "NRooks.h"

NRooks::NRooks(void) 
: Sampler()
{}

NRooks::NRooks(const int num_samples) 
: Sampler(num_samples) {
	generate_samples();
}

NRooks::~NRooks()
{
}

void
NRooks::generate_samples(void) {
	// generate samples along the main diagonal
	for (int p = 0; p < num_sets; p++)
		for (int j; j < num_samples; j++) {
			Point2D pv;
			pv.x = (j + rand_float()) / num_samples;
			pv.y = (j + rand_float()) / num_samples;
			samples.push_back(pv);
		}
	shuffle_x_coordinates();
	shuffle_y_coordinates();
}

void
NRooks::shuffle_x_coordinates(void) {
	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i < num_samples - 1; i++) {
			int target = rand_int() % num_samples + p * num_samples;
			float temp = samples[i + p * num_samples + 1].x;
			samples[i + p * num_samples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
}

void
NRooks::shuffle_y_coordinates(void) {
	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i < num_samples - 1; i++) {
			int target = rand_int() % num_samples + p * num_samples;
			float temp = samples[i + p * num_samples + 1].y;
			samples[i + p * num_samples + 1].y = samples[target].y;
			samples[target].y = temp;
		}
}
