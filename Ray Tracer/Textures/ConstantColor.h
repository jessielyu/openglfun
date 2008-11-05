#ifndef __CONSTANT_COLOR__
#define __CONSTANT_COLOR__

/*
 *  ConstantColor.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Texture.h"

class ConstantColor: public Texture {
public:
	
	ConstantColor(void);										
	
	ConstantColor(const ConstantColor& texture); 					
	
	virtual ConstantColor*									
	clone(void) const;	
	
	void
	set_color(const MyRGBColor& c);
	
	void
	set_color(const float r, const float g, const float b);
	
	void
	set_color(const float c);
	
	virtual MyRGBColor																			
	get_color(const ShadeRec& sr) const;
		
	ConstantColor& 											
	operator= (const ConstantColor& rhs);
	
private:
	
	MyRGBColor color;
};

inline void
ConstantColor::set_color(const MyRGBColor& c) {
	color = c;
}

inline void
ConstantColor::set_color(const float r, const float g, const float b) {
	color = MyRGBColor(r, g, b);
}

inline void
ConstantColor::set_color(const float c) {
	color = MyRGBColor(c,c,c);
}

#endif