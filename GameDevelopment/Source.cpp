#include <iostream>
#include<EsstenialMath.h>

int main(int argc, char* args[]) 
{
	float matrix[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	};

	EssentialMath::EulerAngle angle(-139.0f * DEGREE_TO_RADIAN, 60.0f * DEGREE_TO_RADIAN, 
		60.0f * DEGREE_TO_RADIAN);
	std::cout << "Original: (" << angle.head << ", " << angle.pitch << ", " << angle.bank << ")" << std::endl;
	EssentialMath::ConvertHelper::ObjectToUprightRotationMatrix(angle, matrix);

	std::cout << "Matrix form: " << std::endl;
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			std::cout << matrix[i][j] << ", ";
		}
		std::cout << std::endl;
	}

	EssentialMath::EulerAngle originAngle = EssentialMath::ConvertHelper::ObjectToUprightEulerAngle(matrix);
	std::cout << "Converted back: (" << originAngle.head << ", " << originAngle.pitch << ", " << originAngle.bank << ")" << std::endl;

	return 0;
}
