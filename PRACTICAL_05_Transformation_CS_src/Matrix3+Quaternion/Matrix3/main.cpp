#include <iostream>
#include "Vector3.h"
#include "Matrix3.h"

int main()
{
	Vector3 forward(4, 2, 5);
	Vector3 back(2, 5, 2);
	Vector3 answer;
	Matrix3 kek(4,6,8,10,5,14,8,2,9);
	std::cout << kek.determinant();
	system("PAUSE");
}