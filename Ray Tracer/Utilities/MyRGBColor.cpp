// This file contains the definition of the class RGBColor

#include <math.h>

#include "MyRGBColor.h"

// -------------------------------------------------------- default constructor

MyRGBColor::MyRGBColor(void)
	: r(0.0), g(0.0), b(0.0) 							
{}


// -------------------------------------------------------- constructor

MyRGBColor::MyRGBColor(float c)
	: r(c), g(c), b(c) 							
{}
								

// -------------------------------------------------------- constructor

MyRGBColor::MyRGBColor(float _r, float _g, float _b)	
	: r(_r), g(_g), b(_b)
{}


// -------------------------------------------------------- copy constructor

MyRGBColor::MyRGBColor(const MyRGBColor& c)
	: r(c.r), g(c.g), b(c.b)
{} 				 
		

// -------------------------------------------------------- destructor

MyRGBColor::~MyRGBColor(void)		
{}


// --------------------------------------------------------assignment operator

MyRGBColor& 											
MyRGBColor::operator= (const MyRGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r = rhs.r; g = rhs.g; b = rhs.b;

	return (*this);
}
 

// -------------------------------------------------------- powc
// raise each component to the specified power
// used for color filtering in Chapter 28

MyRGBColor
MyRGBColor::powc(float p) const {
	return (MyRGBColor(pow(r, p), pow(g, p), pow(b, p)));
}

