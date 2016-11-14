#include "Vector3.h"


/// <summary>
/// Default constructor for a vector3
/// </summary>
Vector3::Vector3() :
	m_x(0.0),
	m_y(0.0),
	m_z(0.0)
{
}
/// <summary>
/// constructor for vector3 that takes in 3 doubles as paramaters
/// </summary>
/// <param name="x1">x component of the passed vector</param>
/// <param name="y1">y component of the passed vector</param>
/// <param name="z1">z component of the passed vector</param>
Vector3::Vector3(double x1, double y1, double z1) :
	m_x(x1),
	m_y(y1),
	m_z(z1)
{
}

/// <summary>
/// calculate the length of a vector by multiplying components by itself and adding them
/// x*x + y*y + z*z
/// </summary>
/// <returns>the length of the vector</returns>
double Vector3::length()
{
	return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
}
/// <summary>
/// calcualtes the length squared of the vector
/// x*x + y*y + z*z
/// </summary>
/// <returns>return the length squared</returns>
double Vector3::lengthSquared()
{
	return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}
/// <summary>
/// make the length of the vector equal to 1 keeping its direction
/// </summary>
void Vector3::normalise()
{
	if (length() > 0.0)
	{
		double magnitude = length();
		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
}

/// <summary>
/// An overloaded operator that will add 2 vectors together
/// </summary>
/// <param name="V">The vector to add</param>
/// <returns>The sum of two vectors</returns>
Vector3 Vector3::operator+(const Vector3 &V) const
{
	return Vector3( m_x + V.m_x,
					m_y + V.m_y,
					m_z + V.m_z);
}
/// <summary>
/// Overloaded operator that takes away one vector from another
/// </summary>
/// <param name="V">Vector to take away</param>
/// <returns>subtraction of two vectors</returns>
Vector3 Vector3::operator-(const Vector3 &V) const
{
	return Vector3( m_x - V.m_x,
					m_y - V.m_y,
					m_z - V.m_z);
}
/// <summary>
/// Overloaded operator that allows to negate a vector
/// </summary>
/// <returns>negated vector</returns>
Vector3 Vector3::operator-() const
{
	return Vector3(-m_x, -m_y, -m_z);
}
/// <summary>
/// overloaded operator to multiply 2 vectors
/// </summary>
/// <param name="V">the vector to multiply</param>
/// <returns>the scalar product</returns>
double Vector3::operator*(const Vector3 &V) const
{
	return (m_x * V.m_x + m_y * V.m_y + m_z * V.m_z);
}
/// <summary>
/// overloaded operator to allow multiplication of a vector by a double
/// </summary>
/// <param name="k">the double to multiply vector by</param>
/// <returns>vector that was multiplied by a double</returns>
Vector3 Vector3::operator*(const double &k) const
{
	return Vector3(m_x * k, m_y * k, m_z * k);
}
/// <summary>
/// overloaded operator to allow multiplication of a vector by a float
/// </summary>
/// <param name="k">the float to multiply vector by</param>
/// <returns>vector that was multiplied by a float</returns>
Vector3 Vector3::operator*(const float &k) const
{
	return Vector3(m_x * k, m_y * k, m_z * k);
}
/// <summary>
/// overloaded operator to allow multiplication of a vector by an int
/// </summary>
/// <param name="k">the int to multiply vector by</param>
/// <returns>vector that was multiplied by a int</returns>
Vector3 Vector3::operator*(const int &k) const
{
	return Vector3(m_x * k, m_y * k, m_z * k);
}
/// <summary>
/// The cross product of two vectors
/// </summary>
/// <param name="V">the second vector to use cross product on</param>
/// <returns>the cross product</returns>
Vector3 Vector3::operator^(const Vector3 &V) const
{
	return Vector3((m_y * V.m_z) - (m_z * V.m_y), (m_z * V.m_x) - (m_x * V.m_z), (m_x * V.m_y) - (m_y * V.m_x));
}
/// <summary>
/// A method that returns a string of the vector
/// </summary>
/// <returns>vector as string</returns>
std::string Vector3::toString()
{
	return std::string("( " + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + " )");
}
/// <summary>
/// Returns x component of a vector
/// </summary>
/// <returns>double m_x</returns>
double Vector3::getX() const
{
	return m_x;
}
/// <summary>
/// Returns y component of vector
/// </summary>
/// <returns>double m_y</returns>
double Vector3::getY() const
{
	return m_y;
}
/// <summary>
/// Returns z component of a vector
/// </summary>
/// <returns>double m_z</returns>
double Vector3::getZ() const
{
	return m_z;
}



