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
	return Quaternion(-m_w, -m_x, -m_y, -m_z);
}
/// <summary>
/// make an axis angle as quaternion
/// </summary>
/// <param name="axis">the axis</param>
/// <param name="angleRad">angle in radians</param>
void Quaternion::fromAxisAngle(Vector3 axis, double angleRad)
{
	double m = axis.length();
	if (m > 0.0001)
	{
		double ca = cos(angleRad / 2);
		double sa = sin(angleRad / 2);
		m_x = axis.getX() / m * sa;
		m_y = axis.getY() / m * sa;
		m_z = axis.getZ() / m * sa;
		m_w = ca;
	}
	else
	{
		m_w = 1;
		m_x = 0;
		m_y = 0;
		m_z = 0;
	}
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
	Quaternion axis;
	Quaternion rotateQ;
	axis = normalise();
	double angleRad = acos(-1) / 180 * angle;
	rotateQ = Quaternion(cos(angleRad / 2), sin(angleRad / 2) * axis.m_x, sin(angleRad / 2) * axis.m_y, sin(angleRad / 2) * axis.m_z);
	Quaternion conjugate = rotateQ.conjugate();
	Quaternion qNode = Quaternion(0, pt.getX(), pt.getY(), pt.getZ());
	qNode = rotateQ * qNode * conjugate;
	return Vector3(qNode.m_x,qNode.m_y,qNode.m_z);
}
/// <summary>
/// Multiplying one quaternion by another
/// </summary>
/// <param name="q">quaternion to multiply</param>
/// <returns>result of the product of 2 quaternions</returns>
Quaternion Quaternion::operator*(const Quaternion& q) const
{
	return Quaternion(q.multiply(*this));
}
/// <summary>
/// Adding 2 quaternions
/// </summary>
/// <param name="q">quaternion to add</param>
/// <returns>result of the sum of two quaternions</returns>
Quaternion Quaternion::operator+(const Quaternion &q) const
{
	return Quaternion(m_w + q.m_w, m_x + q.m_x, m_y + q.m_y, m_z + q.m_z);
}
/// <summary>
/// Result of subtracting a quaternion
/// </summary>
/// <param name="q">the quaternion to subtract</param>
/// <returns>subtracted quaternion</returns>
Quaternion Quaternion::operator-(const Quaternion &q) const
{
	return Quaternion(m_w - q.m_w, m_x - q.m_x, m_y - q.m_y, m_z - q.m_z);
}
/// <summary>
/// Negates the quaternion
/// </summary>
/// <returns>negated quaternion</returns>
Quaternion Quaternion::operator-() const
{
	return Quaternion(-m_w, -m_x, -m_y, -m_z);
}

