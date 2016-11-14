#include <iostream>
#include "Vector3.h"
int main()
{
	Vector3 forward(4, 2, 5);
	Vector3 back(2, 5, 2);
	Vector3 answer;
	answer = forward ^ back;
	std::cout << answer.toString();
	system("PAUSE");
}