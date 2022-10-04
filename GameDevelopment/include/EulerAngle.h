#pragma once
class EulerAngle
{
public:
	// Wrap theta in range (-180; 180] degrees
	static float WrapPI(float theta);
	static void ToCanonicalSet(float& head, float& pitch, float& bank);
};
