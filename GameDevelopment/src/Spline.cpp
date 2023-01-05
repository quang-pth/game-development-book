#include "include/Spline.h"

Vector3 Spline::ComputePosition(size_t startIdx, float t)
{
	if (startIdx >= mControlPoints.size()) {
		return mControlPoints.back();
	}
	else if (startIdx == 0 || startIdx + 2 >= mControlPoints.size()) {
		return mControlPoints[startIdx];
	}

	// Define four control points
	Vector3 p0 = mControlPoints[startIdx - 1];
	Vector3 p1 = mControlPoints[startIdx];
	Vector3 p2 = mControlPoints[startIdx + 1];
	Vector3 p3 = mControlPoints[startIdx + 2];

	Vector3 position = 0.5f * (2 * p1 + (-p0 + p2) * t + (2 * p0 - 5 * p1 + 4 * p2 - p3) * std::pow(t, 2)
		+ (-p0 + 3 * p1 - 3 * p2 + p3) * std::pow(t, 3));
	
	return position;
}

void Spline::ReversePath()
{
	std::reverse(mControlPoints.begin(), mControlPoints.end());
}
