//
//  Vector3D.h
//  GameEngine
//
//  Created by Joseph Conley on 5/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_Vector3D_h
#define GameEngine_Vector3D_h

struct Vector3D
{
	Vector3D() {}
	explicit Vector3D(float xyz_in);
	Vector3D(float x_in, float y_in, float z_in);
	Vector3D(Vector3D& ref);
	
	Vector3D& operator=(const Vector3D& rhs);
	Vector3D& operator*=(float scalar);
	const Vector3D operator*(float scalar);	
	Vector3D& operator+=(const Vector3D& rhs);
	const Vector3D operator+(const Vector3D& rhs);
	Vector3D& operator-=(const Vector3D& rhs);
	const Vector3D operator-(const Vector3D& rhs);
	
	float Magnitude() const;
	static const Vector3D Normalize(const Vector3D& vectorToNormalize);
	float DotProduct(const Vector3D& otherVector) const;
	const Vector3D CrossProduct(const Vector3D& otherVector) const;
	
	float x;
	float y;
	float z;
};

#endif
