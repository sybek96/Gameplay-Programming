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
	m_a11(row1.m_x),
	m_a12(row1.m_y),
	m_a13(row1.m_z),
	m_a21(row2.m_x),
	m_a22(row2.m_y),
	m_a23(row2.m_z),
	m_a31(row3.m_x),
	m_a32(row3.m_y),
	m_a33(row3.m_z)
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
Vector3 Matrix3::operator*(const Vector3 & V)
{
	return Vector3(m_a11 * V.m_x + m_a12 * V.m_y + m_a13 * V.m_z,
				   m_a21 * V.m_x + m_a22 * V.m_y + m_a23 * V.m_z,
				   m_a31 * V.m_x + m_a32 * V.m_y + m_a33 * V.m_z);
}
/// <summary>
/// Overloaded operator to allow addition of two matrices
/// </summary>
/// <param name="m1">matrix m1</param>
/// <returns>the result of adding two matrices</returns>
Matrix3 Matrix3::operator+(const Matrix3 &m1)
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
Matrix3 Matrix3::operator-(const Matrix3 &m1)
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
Matrix3 Matrix3::operator*(const double& x)
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
Matrix3 Matrix3::transpose()
{
	return Matrix3( Column(0),
					Column(1),
					Column(2));
}
/// <summary>
/// Returns the determinant of a 3x3 matrix
/// (11)(22)(33) - (11)(32)(23) + (21)(32)(13) - (31)(22)(13) + (31)(12)(23) - (21)(12)(33)   
/// </summary>
/// <returns>the determinant</returns>
double Matrix3::determinant()
{
	return m_a11 * m_a22 * m_a33 - m_a11 * m_a32 * m_a23 + m_a21 * m_a32 * m_a13 - m_a31 * m_a22 * m_a13 + m_a31 * m_a12 * m_a23 - m_a21 * m_a12 * m_a33;
}
/// <summary>
/// Returns an inverse of a matrix if one exists else default matrix
/// </summary>
/// <returns>inverse of matrix</returns>
Matrix3 Matrix3::inverse()
{
	double det = determinant();
	if (det == 0)
		return Matrix3();
	else
	{
		double scale = 1 / det;
		Matrix3 answer;
		answer.m_a11 = scale * (m_a22 * m_a33 - m_a23 * m_a32);
		answer.m_a12 = scale * (m_a13 * m_a32 - m_a12 * m_a33);
		answer.m_a13 = scale * (m_a12 * m_a23 - m_a13 * m_a22);

		answer.m_a21 = scale * (m_a23 * m_a31 - m_a21 * m_a33);
		answer.m_a22 = scale * (m_a11 * m_a33 - m_a13 * m_a31);
		answer.m_a23 = scale * (m_a13 * m_a21 - m_a11 * m_a23);

		answer.m_a31 = scale * (m_a21 * m_a32 - m_a22 * m_a31);
		answer.m_a32 = scale * (m_a12 * m_a31 - m_a11 * m_a32);
		answer.m_a33 = scale * (m_a11 * m_a22 - m_a12 * m_a21);

		return answer;
	}
}

