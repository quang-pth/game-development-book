#pragma once

#include"EsstenialMath.h"

namespace EssentialMath 
{
	class AABB3
	{
	public:
		AABB3() {
			this->Empty();
		};
		~AABB3() {};
		inline void Empty() {
			mMin.x = mMin.y = mMin.z = std::numeric_limits<float>::infinity();
			mMax.x = mMax.y = mMax.z = -std::numeric_limits<float>::infinity();
		}
		inline void Add(const Vector3& point) {
			// MIN bound
			mMin.x = std::min(point.x, mMin.x);
			mMin.y = std::min(point.y, mMin.y);
			mMin.z = std::min(point.z, mMin.z);
			// MAX bound
			mMax.x = std::max(point.x, mMax.x);
			mMax.y = std::max(point.y, mMax.y);
			mMax.z = std::max(point.z, mMax.z);
		}
		inline void Transform(float matrix[4][3]) 
		{
			// Get translation part - the location of the origin after transform
			float* min = matrix[3];
			float* max = matrix[3];
			/*
			* Compute new AABB
			*/
			// X 
			if (matrix[0][0] > 0.0f) {
				min[0] += mMin.x * matrix[0][0];
				max[0] += mMax.x * matrix[0][0];
			}
			else {
				min[0] += mMax.x * matrix[0][0];
				max[0] += mMin.x * matrix[0][0];
			}
			
			if (matrix[1][0] > 0.0f) {
				min[0] += mMin.x * matrix[1][0];
				max[0] += mMax.x * matrix[1][0];
			}
			else {
				min[0] += mMax.x * matrix[1][0];
				max[0] += mMin.x * matrix[1][0];
			}
			
			if (matrix[2][0] > 0.0f) {
				min[0] += mMin.x * matrix[2][0];
				max[0] += mMax.x * matrix[2][0];
			}
			else {
				min[0] += mMax.x * matrix[2][0];
				max[0] += mMin.x * matrix[2][0];
			}
			// Y
			if (matrix[0][1] > 0.0f) {
				min[1] += mMin.x * matrix[0][1];
				max[1] += mMax.x * matrix[0][1];
			}
			else {
				min[1] += mMax.x * matrix[0][1];
				max[1] += mMin.x * matrix[0][1];
			}

			if (matrix[1][1] > 0.0f) {
				min[1] += mMin.x * matrix[1][1];
				max[1] += mMax.x * matrix[1][1];
			}
			else {
				min[1] += mMax.x * matrix[1][1];
				max[1] += mMin.x * matrix[1][1];
			}

			if (matrix[2][1] > 0.0f) {
				min[1] += mMin.x * matrix[2][1];
				max[1] += mMax.x * matrix[2][1];
			}
			else {
				min[1] += mMax.x * matrix[2][1];
				max[1] += mMin.x * matrix[2][1];
			}
			// Z
			if (matrix[0][2] > 0.0f) {
				min[2] += mMin.x * matrix[0][2];
				max[2] += mMax.x * matrix[0][2];
			}
			else {
				min[2] += mMax.x * matrix[0][2];
				max[2] += mMin.x * matrix[0][2];
			}

			if (matrix[1][2] > 0.0f) {
				min[2] += mMin.x * matrix[1][2];
				max[2] += mMax.x * matrix[1][2];
			}
			else {
				min[2] += mMax.x * matrix[1][2];
				max[2] += mMin.x * matrix[1][2];
			}

			if (matrix[2][2] > 0.0f) {
				min[2] += mMin.x * matrix[2][2];
				max[2] += mMax.x * matrix[2][2];
			}
			else {
				min[2] += mMax.x * matrix[2][2];
				max[2] += mMin.x * matrix[2][2];
			}
		}
	private:
		Vector3 mMin;
		Vector3 mMax;
	};
	
	class Plane 
	{
	public:
		static Vector3 ComputeBestFitNormal(const std::vector<Vector3*>& points) 
		{
			Vector3 normal = Vector3::Zero;
			
			auto iter = points.begin();
			while ((iter + 1) != points.end()) {
				Vector3* currentPoint = *iter;
				Vector3* nextPoint = *++iter;

				normal.x += (currentPoint->z + nextPoint->z) * (currentPoint->y - nextPoint->y);
				normal.y += (currentPoint->x + nextPoint->x) * (currentPoint->z - nextPoint->z);
				normal.z += (currentPoint->y + nextPoint->y) * (currentPoint->x - nextPoint->x);
			}

			return normal.Normalize();
		}

		static float ComputeBestFitPlane(const std::vector<Vector3*>& points, const Vector3& normal) 
		{
			Vector3 avgPoint = Vector3::Zero;
			
			for (auto iter = points.begin(); iter != points.end(); iter++) {
				avgPoint = avgPoint + (**iter);
			}

			return (1.0f / (points.size())) * (avgPoint.Dot(normal));
		}
	public:
		inline float DistanceToPoint(Vector3* point) {
			return point->Dot(mNormal) - mDistance;
		}
	private:
		Vector3 mNormal;
		float mDistance;
	};
	
	class Triangle {
	public:

	};
}