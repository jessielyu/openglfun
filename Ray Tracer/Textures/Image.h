#ifndef __IMAGE__
#define __IMAGE__

/*
 *  Image.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */


#include <vector>		
#include "MyRGBColor.h"
using namespace std;

//--------------------------------------------------------------------- class Image

class Image {	
	public:
	
		Image(void);								

		Image(const Image& image);					

		Image& 										
		operator= (const Image& image);		

		~Image(void) ;								
		
		void										
		read_ppm_file(const char* file_name);
		
		int
		get_hres(void);	
		
		int
		get_vres(void);	
				
		MyRGBColor									
		get_color(const int row, const int col) const;		
		
	private:
		int 				hres;			// horizontal resolution of image
		int					vres;			// vertical resolution of image
		vector<MyRGBColor> 	pixels;
};


//--------------------------------------------------------------------- get_hres

inline int
Image::get_hres(void) {
	return (hres);
}


//--------------------------------------------------------------------- get_vres

inline int
Image::get_vres(void) {
	return (vres);
}

#endif
		
