#pragma once
#include "Vector3.h"
class Quaternion
{
public:
	Quaternion();
	Quaternion(double, double, double, double);
	Quaternion(double, Vector3);
	std::string toString();
	double modulus() const;
	double modulusSquared() const;
	Quaternion normalise() const;
	Quaternion conjugate() const;
	void fromAxisAngle(Vector3, double);
	Quaternion multiply(const Quaternion&) const;
	Vector3 rotate(const Vector3&,const int&) const;
	Quaternion operator* (const Quaternion&) const;
	Quaternion operator+ (const Quaternion&) const;
	Quaternion operator- (const Quaternion&) const;
	Quaternion operator- () const;
private:
	double m_w;
	double m_x;
	double m_y;
	double m_z;
};

