#include<iostream>
#include"include/EsstenialMath.h"
#include"include/Primitive.h"

using namespace EssentialMath;

int main() 
{
	Vector3 v1(6, 10, -2);
	Vector3 v2(3, -1, 17);
	Vector3 v3(-9, 8, 0);
	Triangle triangle(v1, v2, v3);
	Vector3 point(13.6, -0.46, 17.11);
	Vector3 result = Triangle::ComputeBaryCentricPointProjectedOn2D(triangle, point);
	std::cout << result.x << ", " << result.y << ", " << result.z << "\n";

	std::cin.get();
}
