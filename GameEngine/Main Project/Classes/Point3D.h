//
//  Point3D.h
//  GameEngine
//
//  Created by Joseph Conley on 5/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_Point3D_h
#define GameEngine_Point3D_h

struct Point3D
{
	Point3D(float xyz_in) : x(xyz_in), y(xyz_in), z(xyz_in) {}
	Point3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in) {}
	Point3D(Point3D& ref) : x(ref.x), y(ref.y), z(ref.z) {}
	
	operator=(const Point3D& rhs)
	{
		if (rhs != this)
		{
			x=rhs.x;
			y=rhs.y;
			z=rhs.z;
		}
		return *this;
	}
	
	float x;
	float y;
	float z;
};

#endif
