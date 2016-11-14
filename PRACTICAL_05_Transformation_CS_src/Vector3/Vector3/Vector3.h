#pragma once
#include <math.h>
#include <string>

class Vector3
{
public:
	Vector3();
	Vector3(double, double, double);
	Vector3(Vector3&);
	double length();
	double lengthSquared();
	void normalise();
	Vector3 operator+ (const Vector3&);
	Vector3 operator- (const Vector3&);
	Vector3 operator- ();
	double operator*(const Vector3&);
	Vector3 operator*(const double&);
	Vector3 operator*(const float&);
	Vector3 operator*(const int&);
	Vector3 operator^(const Vector3&);
	std::string toString();
	double m_x;
	double m_y;
	double m_z;
};

