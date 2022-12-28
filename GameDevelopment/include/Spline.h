#pragma once

#include"include/CustomMath.h"
#include<vector>

class Spline
{
public:
	Spline() = default;
	~Spline() = default;
	Vector3 ComputePosition(size_t startIdx, float t);
	const std::vector<Vector3>& GetControlPoints() const { return mControlPoints; }
	void AddControlPoint(const Vector3& point) { mControlPoints.emplace_back(point); }
	size_t GetNumPoints() const { return mControlPoints.size(); }
private:
	std::vector<Vector3> mControlPoints;
};