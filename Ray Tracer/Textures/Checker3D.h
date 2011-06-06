#ifndef __CHECKER_3D__
#define __CHECKER_3D__

/*
 *  Checker3D.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 11/4/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Texture.h"

class Checker3D: public Texture {
public:
	
	Checker3D(void);										
	
	Checker3D(const Checker3D& texture); 					
	
	virtual Checker3D*									
	clone(void) const;	
	
	void
	set_color1(const MyRGBColor& c);
	
	void
	set_color1(const float r, const float g, const float b);
	
	void
	set_color1(const float c);
	
	void
	set_color2(const MyRGBColor& c);
	
	void
	set_color2(const float r, const float g, const float b);
	
	void
	set_color2(const float c);
	
	void
	set_size(const float s);
	
	virtual MyRGBColor																			
	get_color(const ShadeRec& sr) const;
	
	Checker3D& 											
	operator= (const Checker3D& rhs);
	
private:
	
	MyRGBColor color1;
	MyRGBColor color2;
	float size;
};

inline void
Checker3D::set_color1(const MyRGBColor& c) {
	color1 = c;
}

inline void
Checker3D::set_color1(const float r, const float g, const float b) {
	color1 = MyRGBColor(r, g, b);
}

inline void
Checker3D::set_color1(const float c) {
	color1 = MyRGBColor(c,c,c);
}

inline void
Checker3D::set_color2(const MyRGBColor& c) {
	color2 = c;
}

inline void
Checker3D::set_color2(const float r, const float g, const float b) {
	color2 = MyRGBColor(r, g, b);
}

inline void
Checker3D::set_color2(const float c) {
	color2 = MyRGBColor(c,c,c);
}

inline void
Checker3D::set_size(const float s) {
	size = s;
}

#endif