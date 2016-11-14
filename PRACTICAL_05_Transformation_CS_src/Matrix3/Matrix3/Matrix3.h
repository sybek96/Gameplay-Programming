#pragma once
#include "Vector3.h"

class Matrix3
{
public:
	Matrix3();
	Matrix3(Vector3, Vector3, Vector3);
	Matrix3(double, double, double, double, double, double, double, double, double);
	Vector3 operator* (const Vector3&);
	Matrix3 operator+ (const Matrix3&);
	Matrix3 operator- (const Matrix3&);
	Matrix3 operator* (const double&);
	Vector3 Row(int) const;
	Vector3 Column(int) const;
	Matrix3 transpose();
	double determinant();
	Matrix3 inverse();
	double m_a11;
	double m_a12;
	double m_a13;
	double m_a21;
	double m_a22;
	double m_a23;
	double m_a31;
	double m_a32;
	double m_a33;
};

