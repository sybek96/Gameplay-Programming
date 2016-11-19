#pragma once
#include "Vector3.h"
class Quaternion
{
	friend Quaternion operator*(const Quaternion&, const Quaternion&);
	friend Quaternion operator+(const Quaternion&, const Quaternion&);
	friend Quaternion operator-(const Quaternion&, const Quaternion&);
	friend Quaternion operator*(const Quaternion&, const double&);
	friend Quaternion operator*(const Quaternion&, const float&);
	friend Quaternion operator*(const Quaternion&, const int&);
	friend Quaternion operator*(const double&, const Quaternion&);
	friend Quaternion operator*(const float&, const Quaternion&);
	friend Quaternion operator*(const int&, const Quaternion&);

public:
	Quaternion();
	Quaternion(double, double, double, double);
	Quaternion(double, Vector3);
	std::string toString();
	double modulus() const;
	double modulusSquared() const;
	Quaternion normalise() const;
	Quaternion conjugate() const;
	Quaternion inverse() const;
	Quaternion multiply(const Quaternion&) const;
	Vector3 rotate(const Vector3&,const int&) const;
	Quaternion operator- () const;
private:
	double m_w;
	double m_x;
	double m_y;
	double m_z;
};

