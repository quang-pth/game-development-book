#include <iostream>
#include<EsstenialMath.h>

using namespace EssentialMath;

void PrintMatrix(float matrix[3][3]);
void TestQuaternionAndMatrix();
void TestEulerAngleAndMatrix();
void TestEulerAngleAndQuaternion();

int main(int argc, char* args[]) 
{
	TestEulerAngleAndQuaternion();
	return 0;
}

void TestEulerAngleAndQuaternion() {
	EulerAngle angle = EulerAngle(23.0f * DEGREE_TO_RADIAN, 56.0f * DEGREE_TO_RADIAN, 36.0f * DEGREE_TO_RADIAN);
	std::cout << "Euler Angle: " << angle.head << ", " << angle.pitch << ", " << angle.bank << "\n";
	std::cout << "====================================\n";
	Quaternion quaternion = RepresentationConverter::EulerAngleToObjectToUpRightQuaternion(angle);
	std::cout << "Quaternion: " << quaternion.w << ", " << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << std::endl;
	std::cout << "====================================\n";
	float matrix[3][3] = { 0 };
	RepresentationConverter::QuaternionToMatrix(quaternion, matrix);
	PrintMatrix(matrix);
	std::cout << "====================================\n";
	angle = RepresentationConverter::MatrixToEulerAngle(matrix);
	std::cout << "Euler Angle: " << angle.head << ", " << angle.pitch << ", " << angle.bank << "\n";
}

void TestQuaternionAndMatrix() 
{
	Quaternion quaternion = Quaternion(-56.0f * DEGREE_TO_RADIAN, Vector3(-2.2f, 3.001f, 56.3005f).Normalize());
	std::cout << "Original quaternion: " << quaternion.w << ", " << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << std::endl;
	std::cout << "====================================\n";
	float matrix[3][3] = { 0 };
	RepresentationConverter::QuaternionToMatrix(quaternion, matrix);
	PrintMatrix(matrix);
	std::cout << "====================================\n";
	// Matrix to quaternion
	quaternion = RepresentationConverter::MatrixToQuaternion(matrix);
	std::cout << "Converted-back quaternion: " << quaternion.w << ", " << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << std::endl;

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
	RepresentationConverter::EulerAngleToObjectToUpRightMatrix(angle, matrix);

	std::cout << "Matrix form: " << std::endl;
	PrintMatrix(matrix);

	EulerAngle originAngle = RepresentationConverter::MatrixToEulerAngle(matrix);
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