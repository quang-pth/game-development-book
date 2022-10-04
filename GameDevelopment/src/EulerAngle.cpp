#include "include/EulerAngle.h"
#include<cmath>
#include <iostream>

#define PI 180.0f

float EulerAngle::WrapPI(float theta)
{
	if (fabs(theta) > PI) {
		float resolution = floor((theta + PI) / (2 * PI));
		theta -= 2 * PI * resolution;
	}
	return theta;
}

void EulerAngle::ToCanonicalSet(float& head, float& pitch, float& bank)
{
	// Head [-180, 180)
	// Pitch [-90, 90]
	// Bank [-180, 180)

	if (fabs(pitch) == PI) {
		bank = 0.0f;
	}
}
