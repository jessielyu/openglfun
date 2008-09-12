#ifndef __RGB_COLOR__
#define __RGB_COLOR__

// This file contains the declaration of the class RGBColor

//------------------------------------------------------------ class RGBColor

class MyRGBColor {
	
	public:
	
		float	r, g, b;									
				
	public:
	
		MyRGBColor(void);										// default constructor
		MyRGBColor(float c);									// constructor
		MyRGBColor(float _r, float _g, float _b);				// constructor
		MyRGBColor(const MyRGBColor& c); 						// copy constructor
		
		~MyRGBColor(void);									// destructor
		
		MyRGBColor& 											// assignment operator
		operator= (const MyRGBColor& rhs); 

		MyRGBColor 											// addition
		operator+ (const MyRGBColor& c) const;	

		MyRGBColor& 											// compound addition
		operator+= (const MyRGBColor& c);
		
		MyRGBColor 											// multiplication by a float on the right
		operator* (const float a) const;
		
		MyRGBColor& 											// compound multiplication by a float on the right
		operator*= (const float a);					
				
		MyRGBColor 											// division by a float
		operator/ (const float a) const;
		
		MyRGBColor& 											// compound division by a float
		operator/= (const float a); 
				
		MyRGBColor 											// component-wise multiplication
		operator* (const MyRGBColor& c) const;
		
		bool												// are two RGBColours the same?
		operator== (const MyRGBColor& c) const;				

		MyRGBColor											// raise components to a power
		powc(float p) const;
		
		float												// the average of the components
		average(void) const;
};



// inlined member functions

// ----------------------------------------------------------------------- operator+
// addition of two colors

inline MyRGBColor 
MyRGBColor::operator+ (const MyRGBColor& c) const {
	return (MyRGBColor(r + c.r, g + c.g, b + c.b));
}


// ----------------------------------------------------------------------- operator+=
// compound addition of two colors

inline MyRGBColor& 
MyRGBColor::operator+= (const MyRGBColor& c) {
	r += c.r; g += c.g; b += c.b;
    return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a float on the right

inline MyRGBColor 
MyRGBColor::operator* (const float a) const {
	return (MyRGBColor (r * a, g * a, b * a));	
}


// ----------------------------------------------------------------------- operator*=
// compound multiplication by a float on the right

inline MyRGBColor& 
MyRGBColor::operator*= (const float a) {
	r *= a; g *= a; b *= a;
	return (*this);
}


// ----------------------------------------------------------------------- operator/
// division by float

inline MyRGBColor 
MyRGBColor::operator/ (const float a) const {
	return (MyRGBColor (r / a, g / a, b / a));
}


// ----------------------------------------------------------------------- operator/=
// compound division by float

inline MyRGBColor& 
MyRGBColor::operator/= (const float a) {	
	r /= a; g /= a; b /= a;
	return (*this);
}



// ----------------------------------------------------------------------- operator*
// component-wise multiplication of two colors

inline MyRGBColor 
MyRGBColor::operator* (const MyRGBColor& c) const {
	return (MyRGBColor (r * c.r, g * c.g, b * c.b));
} 


// ----------------------------------------------------------------------- operator==
// are two RGBColors the same?

inline bool
MyRGBColor::operator== (const MyRGBColor& c) const {
	return (r == c.r && g == c.g && b == c.b);
}


// ----------------------------------------------------------------------- average
// the average of the three components

inline float											
MyRGBColor::average(void) const {
	return (0.333333333333 * (r + g + b));
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a float on the left

MyRGBColor 
operator* (const float a, const MyRGBColor& c);

inline MyRGBColor 
operator* (const float a, const MyRGBColor& c) {
	return (MyRGBColor (a * c.r, a * c.g, a * c.b));	
}


#endif
