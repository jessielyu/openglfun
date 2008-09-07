#ifndef __BRDF__
#define __BRDF__

// This file contains the declaration of the base class BRDF

#include <math.h>

#include "MyRGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"

class BRDF {
	public:
	
		BRDF(void);						
		
		BRDF(const BRDF& object);
		
		virtual BRDF*
		clone(void) const = 0;
		
		~BRDF(void);
								
		virtual MyRGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual MyRGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
		
		virtual MyRGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
		virtual MyRGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
		
			
	protected:
	
		BRDF&							
		operator= (const BRDF& rhs);
};

#endif