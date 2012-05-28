//
//  Vector3D.cpp
//  GameEngine
//
//  Created by Joseph Conley on 5/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "Vector3D.h"

Vector3D::Vector3D(float xyz_in) : x(xyz_in), y(xyz_in), z(xyz_in) {}
Vector3D::Vector3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in) {}
Vector3D::Vector3D(Vector3D& ref) : x(ref.x), y(ref.y), z(ref.z) {}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	if (this != &rhs)
	{
		x=rhs.x;
		y=rhs.y;
		z=rhs.z;
	}
	return *this;
}

Vector3D& Vector3D::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	
	return *this;
}

const Vector3D Vector3D::operator*(float scalar)
{
	return Vector3D(*this) *= scalar;
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	
	return *this;
}

const Vector3D Vector3D::operator+(const Vector3D& rhs)
{
	return Vector3D(*this) += rhs;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	
	return *this;
}

const Vector3D Vector3D::operator-(const Vector3D& rhs)
{
	return Vector3D(*this) -= rhs;
}

float Vector3D::Magnitude() const
{
	// a dot a = |a|^2
	return sqrtf(DotProduct(*this));
}

const Vector3D Vector3D::Normalize(const Vector3D& vectorToNormalize)
{
	float magnitude = vectorToNormalize.Magnitude();
	
	Vector3D retVec;
	retVec.x = vectorToNormalize.x / magnitude;
	retVec.y = vectorToNormalize.y / magnitude;
	retVec.z = vectorToNormalize.z / magnitude;
	return retVec;
}

float Vector3D::DotProduct(const Vector3D& otherVector) const
{
	return (x*otherVector.x + y*otherVector.y + z*otherVector.z);
}

const Vector3D Vector3D::CrossProduct(const Vector3D& otherVector) const
{
	Vector3D retVec;
	
	retVec.x = (y * otherVector.z) - (z * otherVector.y);
	retVec.y = (z * otherVector.x) - (x * otherVector.z);
	retVec.z = (x * otherVector.y) - (y * otherVector.x);
	
	return retVec;
}