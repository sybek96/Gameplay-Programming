#include "Quaternion.h"


/// <summary>
/// Default contructor
/// </summary>
Quaternion::Quaternion():
	m_w(0),
	m_x(0),
	m_y(0),
	m_z(0)
{
}
/// <summary>
/// constructor that takes in 4 doubles
/// </summary>
/// <param name="w">w component</param>
/// <param name="x">x component</param>
/// <param name="y">y component</param>
/// <param name="z">z component</param>
Quaternion::Quaternion(double w, double x, double y, double z) :
	m_w(w),
	m_x(x),
	m_y(y),
	m_z(z)
{
}
/// <summary>
/// Constructor that takes in the w component and the x,y,z as a vector3
/// </summary>
/// <param name="w">double w component</param>
/// <param name="v">vector3 x,y,z components</param>
Quaternion::Quaternion(double w, Vector3 v) :
	m_w(w),
	m_x(v.getX()),
	m_y(v.getY()),
	m_z(v.getZ())
{
}
/// <summary>
/// Returns a quaternion as string
/// </summary>
/// <returns>string of quaternion</returns>
std::string Quaternion::toString()
{
	return std::string("(" + std::to_string(m_w) + "," + std::to_string(m_x) + "i," + std::to_string(m_y) + "j," + std::to_string(m_z) + "k)");
}
/// <summary>
/// Gets the mod of the quaternion
/// </summary>
/// <returns>modulus</returns>
double Quaternion::modulus() const
{
	return sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}
/// <summary>
/// Mod squared to prevent square rooting for efficiency
/// </summary>
/// <returns>double mod squared</returns>
double Quaternion::modulusSquared() const
{
	return m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;
}
/// <summary>
/// normalises the quaternion
/// </summary>
/// <returns>normalised quaternion</returns>
Quaternion Quaternion::normalise() const
{
	double m = modulusSquared();
	if (m > 0.001)
	{
		m = sqrt(m);
		return Quaternion(m_w / m, m_x / m, m_y / m, m_z / m);
	}
	else
	{
		return Quaternion(1, 0, 0, 0);
	}
}
/// <summary>
/// Gets the conjugate of a quaternion
/// </summary>
/// <returns>quaternions conjugate</returns>
Quaternion Quaternion::conjugate() const
{
	return Quaternion(m_w, -m_x, -m_y, -m_z);
}
Quaternion Quaternion::inverse() const
{
	return Quaternion(conjugate() * (1/ modulusSquared()));
}
/// <summary>
/// Multiply quaternion by another quaternion
/// </summary>
/// <param name="q">the quaternion to multiply by</param>
/// <returns></returns>
Quaternion Quaternion::multiply(const Quaternion& q) const
{
	return Quaternion(  q.m_w *  m_w - q.m_x *  m_x - q.m_y *  m_y - q.m_z *  m_z,
						q.m_w *  m_x + q.m_x *  m_w + q.m_y *  m_z - q.m_z *  m_y,
						q.m_w *  m_y + q.m_y *  m_w + q.m_z *  m_x - q.m_x *  m_z,
						q.m_w *  m_z + q.m_z *  m_w + q.m_x *  m_y - q.m_y *  m_x);
}
/// <summary>
/// Return a rotation vector
/// </summary>
/// <param name="pt">the axis by which to rotate</param>
/// <param name="angle">angle at which to rotate</param>
/// <returns>rotation vector</returns>
Vector3 Quaternion::rotate(const Vector3 &pt, const int &angle) const
{
	Quaternion axis(normalise());
	Quaternion rotateQ;
	double angleRad = (acos(-1) / 180) * angle;
	rotateQ = Quaternion(cos(angleRad / 2), sin(angleRad / 2) * axis.m_x, sin(angleRad / 2) * axis.m_y, sin(angleRad / 2) * axis.m_z);
	Quaternion inverse = rotateQ.inverse();
	Quaternion qNode = Quaternion(0, pt.getX(), pt.getY(), pt.getZ());
	qNode = rotateQ * qNode * inverse;
	return Vector3(qNode.m_x,qNode.m_y,qNode.m_z);
}
/// <summary>
/// Negates the quaternion
/// </summary>
/// <returns>negated quaternion</returns>
Quaternion Quaternion::operator-() const
{
	return Quaternion(-m_w, -m_x, -m_y, -m_z);
}
/// <summary>
/// Multiplying one quaternion by another
/// </summary>
/// <param name="Q1">lhs</param>
/// <param name="Q2">rhs</param>
/// <returns>product of 2 quaternions</returns>
Quaternion operator*(const Quaternion &Q1, const Quaternion &Q2)
{
	return Quaternion(Q1.multiply(Q2));
}
/// <summary>
/// Adding 2 quaternions
/// </summary>
/// <param name="Q1">lhs</param>
/// <param name="Q2">rhs</param>
/// <returns>sum of 2 quaternions</returns>
Quaternion operator+(const Quaternion &Q1, const Quaternion &Q2)
{
	return Quaternion(Q1.m_w + Q2.m_w, Q1.m_x + Q2.m_x, Q1.m_y + Q2.m_y, Q1.m_z + Q2.m_z);
}
/// <summary>
/// Result of subtracting a quaternion
/// </summary>
/// <param name="Q1">lhs</param>
/// <param name="Q2">rhs</param>
/// <returns>subtraction of quaternion</returns>
Quaternion operator-(const Quaternion &Q1, const Quaternion &Q2)
{
	return Quaternion(Q1.m_w - Q2.m_w, Q1.m_x - Q2.m_x, Q1.m_y - Q2.m_y, Q1.m_z - Q2.m_z);
}
/// <summary>
/// multiplying a quaternion by a double
/// </summary>
/// <param name="Q">quaternion</param>
/// <param name="s">double</param>
/// <returns>sum of quaternion by double</returns>
Quaternion operator*(const Quaternion &Q, const double &s)
{
	return Quaternion(Q.m_w * s, Q.m_x * s, Q.m_y * s, Q.m_z * s);
}
/// <summary>
/// multiplying a quaternion by a float
/// </summary>
/// <param name="Q">quaternion</param>
/// <param name="s">float</param>
/// <returns>sum of quaternion by float</returns>
Quaternion operator*(const Quaternion &Q, const float &s)
{
	return Quaternion(Q.m_w * s, Q.m_x * s, Q.m_y * s, Q.m_z * s);
}
/// <summary>
/// multiplying a quaternion by a int
/// </summary>
/// <param name="Q">quaternion</param>
/// <param name="s">int</param>
/// <returns>sum of quaternion by int</returns>
Quaternion operator*(const Quaternion &Q, const int &s)
{
	return Quaternion(Q.m_w * s, Q.m_x * s, Q.m_y * s, Q.m_z * s);
}
/// <summary>
/// multiplying a double by a quaternion
/// </summary>
/// <param name="s">double</param>
/// <param name="Q">quaternion</param>
/// <returns>sum of double by quaternion</returns>
Quaternion operator*(const double &s, const Quaternion &Q)
{
	return Quaternion(Q.m_w * s, Q.m_x * s, Q.m_y * s, Q.m_z * s);
}
/// <summary>
/// multiplying a float by a quaternion
/// </summary>
/// <param name="s">float</param>
/// <param name="Q">quaternion</param>
/// <returns>sum of float by quaternion</returns>
Quaternion operator*(const float &s, const Quaternion &Q)
{
	return Quaternion(Q.m_w * s, Q.m_x * s, Q.m_y * s, Q.m_z * s);
}
/// <summary>
/// multiplying a int by a quaternion
/// </summary>
/// <param name="s">int</param>
/// <param name="Q">quaternion</param>
/// <returns>sum of int by quaternion</returns>
Quaternion operator*(const int &s, const Quaternion &Q)
{
	return Quaternion(Q.m_w * s, Q.m_x * s, Q.m_y * s, Q.m_z * s);
}


