#ifndef __PLANE_CHECKER__
#define __PLANE_CHECKER__

/*
 *  PlaneChecker.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 11/4/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Texture.h"

class PlaneChecker: public Texture {
public:
	
	PlaneChecker(void);										
	
	PlaneChecker(const PlaneChecker& texture); 					
	
	virtual PlaneChecker*									
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
	set_outline_color(const MyRGBColor& c);
	
	void
	set_outline_color(const float r, const float g, const float b);
	
	void
	set_outline_color(const float c);
	
	void
	set_size(const float s);
	
	void
	set_outline_width(const float s);
	
	virtual MyRGBColor																			
	get_color(const ShadeRec& sr) const;
	
	PlaneChecker& 											
	operator= (const PlaneChecker& rhs);
	
private:
	
	MyRGBColor color1;
	MyRGBColor color2;
	MyRGBColor outline_color;
	float size;
	float outline_width;
};

inline void
PlaneChecker::set_color1(const MyRGBColor& c) {
	color1 = c;
}

inline void
PlaneChecker::set_color1(const float r, const float g, const float b) {
	color1 = MyRGBColor(r, g, b);
}

inline void
PlaneChecker::set_color1(const float c) {
	color1 = MyRGBColor(c,c,c);
}

inline void
PlaneChecker::set_color2(const MyRGBColor& c) {
	color2 = c;
}

inline void
PlaneChecker::set_color2(const float r, const float g, const float b) {
	color2 = MyRGBColor(r, g, b);
}

inline void
PlaneChecker::set_color2(const float c) {
	color2 = MyRGBColor(c,c,c);
}

inline void
PlaneChecker::set_outline_color(const MyRGBColor& c) {
	outline_color = c;
}

inline void
PlaneChecker::set_outline_color(const float r, const float g, const float b) {
	outline_color = MyRGBColor(r, g, b);
}

inline void
PlaneChecker::set_outline_color(const float c) {
	outline_color = MyRGBColor(c,c,c);
}

inline void
PlaneChecker::set_size(const float s) {
	size = s;
}
	
inline void
PlaneChecker::set_outline_width(const float s) {
	outline_width = s;
}
	
	

#endif