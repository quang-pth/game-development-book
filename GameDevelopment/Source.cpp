#include <iostream>
#include<EsstenialMath.h>

using namespace EssentialMath;

void PrintMatrix(float matrix[3][3]);
void TestQuaternionAndMatrix();

int main(int argc, char* args[]) 
{
	TestQuaternionAndMatrix();
	return 0;
}

void TestQuaternionAndMatrix() 
{
	Quaternion quaterion = Quaternion(45.0f * DEGREE_TO_RADIAN, Vector3(0.0f, 1.0f, 0.0f));
	std::cout << "Quaternion " << quaterion.w << ", " << quaterion.x << ", " << quaterion.y << ", " << quaterion.z << std::endl;

	float matrix[3][3] = { 0 };
	ConvertHelper::QuaternionToMatrix(quaterion, matrix);
	PrintMatrix(matrix);

	// Matrix to quaternion
}

void TestEulerAngleAndMatrix() 
{
	float matrix[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	};

	EulerAngle angle(-179.0f * DEGREE_TO_RADIAN, 60.0f * DEGREE_TO_RADIAN,
		179.0f * DEGREE_TO_RADIAN);
	std::cout << "Original: (" << angle.head << ", " << angle.pitch << ", " << angle.bank << ")" << std::endl;
	ConvertHelper::ObjectToUprightRotationMatrix(angle, matrix);

	std::cout << "Matrix form: " << std::endl;
	PrintMatrix(matrix);

	EulerAngle originAngle = ConvertHelper::EulerAngleFromObjectToUpRightMatrix(matrix);
	std::cout << "Converted back: (" << originAngle.head << ", " << originAngle.pitch << ", " << originAngle.bank << ")" << std::endl;
}

void PrintMatrix(float matrix[3][3]) {
	std::cout << "Matrix form: " << std::endl;
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			std::cout << matrix[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}