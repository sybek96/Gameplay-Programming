#include "Matrix3.h"
/// <summary>
/// default constructor
/// </summary>
Matrix3::Matrix3() :
	m_a11(0.0),
	m_a12(0.0),
	m_a13(0.0),
	m_a21(0.0),
	m_a22(0.0),
	m_a23(0.0),
	m_a31(0.0),
	m_a32(0.0),
	m_a33(0.0)
{

}
/// <summary>
/// Overloaded constructor that takes in 3 vectors
/// </summary>
/// <param name="row1">first row</param>
/// <param name="row2">second row</param>
/// <param name="row3">third row</param>
Matrix3::Matrix3(Vector3 row1, Vector3 row2, Vector3 row3) :
	m_a11(row1.getX()),
	m_a12(row1.getY()),
	m_a13(row1.getZ()),
	m_a21(row2.getX()),
	m_a22(row2.getY()),
	m_a23(row2.getZ()),
	m_a31(row3.getX()),
	m_a32(row3.getY()),
	m_a33(row3.getZ())
{
}

/// <summary>
/// Overloaded constructor that takes in individual values
/// </summary>
/// <param name="a11">11</param>
/// <param name="a12">12</param>
/// <param name="a13">12</param>
/// <param name="a21">21</param>
/// <param name="a22">22</param>
/// <param name="a23">23</param>
/// <param name="a31">31</param>
/// <param name="a32">32</param>
/// <param name="a33">33</param>
Matrix3::Matrix3(double a11, double a12, double a13, 
				 double a21, double a22, double a23,
				 double a31, double a32, double a33) :
	m_a11(a11),
	m_a12(a12),
	m_a13(a13),
	m_a21(a21),
	m_a22(a22),
	m_a23(a23),
	m_a31(a31),
	m_a32(a32),
	m_a33(a33)
{
}
/// <summary>
/// Overloaded operator that multiplies a matrix by a vector
/// </summary>
/// <param name="V">the vector to multiply by</param>
/// <returns>produckt of vector by matrix</returns>
Vector3 Matrix3::operator*(const Vector3 & V) const
{
	return Vector3(m_a11 * V.getX() + m_a12 * V.getY() + m_a13 * V.getZ(),
				   m_a21 * V.getX() + m_a22 * V.getY() + m_a23 * V.getZ(),
				   m_a31 * V.getX() + m_a32 * V.getY() + m_a33 * V.getZ());
}
/// <summary>
/// Overloaded operator to allow addition of two matrices
/// </summary>
/// <param name="m1">matrix m1</param>
/// <returns>the result of adding two matrices</returns>
Matrix3 Matrix3::operator+(const Matrix3 &m1) const
{
	return Matrix3( Row(0) + m1.Row(0),
					Row(1) + m1.Row(1),
					Row(2) + m1.Row(2));
}
/// <summary>
/// Overload operator to allow the subtraction of one matrix from another
/// </summary>
/// <param name="m1">matrix m1</param>
/// <returns>result of subtracting two matrices</returns>
Matrix3 Matrix3::operator-(const Matrix3 &m1) const
{
	return Matrix3( Row(0) - m1.Row(0),
					Row(1) - m1.Row(1),
					Row(2) - m1.Row(2));
}
/// <summary>
/// Allows to multiply a matrix by a number
/// </summary>
/// <param name="x">number to multiply by</param>
/// <returns>result of matrix multiplied by a number</returns>
Matrix3 Matrix3::operator*(const double& x) const
{
	return Matrix3( Row(0) * x, Row(1) * x, Row(2) * x);
}
/// <summary>
/// Returns a Row of a matrix as a vector3 0 being first row and 2/default the last
/// </summary>
/// <param name="">number of row</param>
/// <returns>row of matrix as vector3</returns>
Vector3 Matrix3::Row(int i) const
{
	switch (i)
	{
		case 0:
			return Vector3(m_a11, m_a12, m_a13);
		case 1:
			return Vector3(m_a21, m_a22, m_a23);
		case 2:
		default:
			return Vector3(m_a31, m_a32, m_a33);
	}
}
/// <summary>
/// Returns a Column of a matrix as a vector3 0 being first col and 2/default the last
/// </summary>
/// <param name="i">the column num</param>
/// <returns>column of matrix as vector3</returns>
Vector3 Matrix3::Column(int i) const
{
	switch (i)
	{
		case 0:
			return Vector3(m_a11, m_a21, m_a31);
		case 1:
			return Vector3(m_a12, m_a22, m_a32);
		case 2:
		default:
			return Vector3(m_a13, m_a23, m_a33);
	}
}
/// <summary>
/// Transposes the matrix turning each row into a column
/// </summary>
/// <returns>Transposed matrix</returns>
Matrix3 Matrix3::transpose(const Matrix3& M)
{
	return Matrix3( M.Column(0),
					M.Column(1),
					M.Column(2));
}
/// <summary>
/// Returns the determinant of a 3x3 matrix
/// (11)(22)(33) - (11)(32)(23) + (21)(32)(13) - (31)(22)(13) + (31)(12)(23) - (21)(12)(33)   
/// </summary>
/// <returns>the determinant</returns>
double Matrix3::determinant() const
{
	return m_a11 * m_a22 * m_a33 - m_a11 * m_a32 * m_a23 + m_a21 * m_a32 * m_a13 - m_a31 * m_a22 * m_a13 + m_a31 * m_a12 * m_a23 - m_a21 * m_a12 * m_a33;
}
/// <summary>
/// Returns an inverse of a matrix if one exists else default matrix
/// </summary>
/// <returns>inverse of matrix</returns>
Matrix3 Matrix3::inverse(const Matrix3& M)
{
	double det = M.determinant();
	if (det == 0)
		return Matrix3();
	else
	{
		double scale = 1 / det;
		return Matrix3(M.m_a22 * M.m_a33 - M.m_a23 * M.m_a32, M.m_a13 * M.m_a32 - M.m_a12 * M.m_a33, M.m_a12 * M.m_a23 - M.m_a13 * M.m_a22,
					   M.m_a23 * M.m_a31 - M.m_a21 * M.m_a33, M.m_a11 * M.m_a33 - M.m_a13 * M.m_a31, M.m_a13 * M.m_a21 - M.m_a11 * M.m_a23,
					   M.m_a21 * M.m_a32 - M.m_a22 * M.m_a31, M.m_a12 * M.m_a31 - M.m_a11 * M.m_a32, M.m_a11 * M.m_a22 - M.m_a12 * M.m_a21) * scale;
	}
}
/// <summary>
/// Rotates the matrix about the input axis
/// </summary>
/// <param name="axis">axis about which we rotate</param>
/// <param name="angle">angle of rotation</param>
/// <returns>rotation matrix</returns>
Matrix3 Matrix3::rotation(const Axis &axis, const int &angle)
{
	double radians = acos(-1) / 180 * angle;
	switch (axis)
	{
	case Axis::X:
		return Matrix3( 1,		0,				0,
						0, cos(radians), -sin(radians),
						0, sin(radians), cos(radians));
	case Axis::Y:
		return Matrix3( cos(radians),0,sin(radians),
						0,			1,		0,
						-sin(radians),0,cos(radians));
	case Axis::Z:
		return Matrix3(	cos(radians),-sin(radians),0,
						sin(radians),cos(radians), 0,
						0,				0,		   1);
	default:
		return Matrix3();
	}
}
/// <summary>
/// The creation of translation matrix
/// </summary>
/// <param name="dx">translation in x</param>
/// <param name="dy">translation in y</param>
/// <returns>the translation matrix</returns>
Matrix3 Matrix3::translate(const int &dx, const int &dy)
{
	return Matrix3( 1,0,dx,
					0,1,dy,
					0,0,1);
}
/// <summary>
/// Returns the scale matrix
/// </summary>
/// <param name="dx">scale in x</param>
/// <param name="dy">scale in y</param>
/// <param name="dz">scale in z</param>
/// <returns>The scale matrix</returns>
Matrix3 Matrix3::scale(const double &dx, const double &dy, const double &dz)
{
	return Matrix3( dx,0,0,
					0,dy,0,
					0,0,dz);
}

