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
				min[0] += mMin.y * matrix[1][0];
				max[0] += mMax.y * matrix[1][0];
			}
			else {
				min[0] += mMax.y * matrix[1][0];
				max[0] += mMin.y * matrix[1][0];
			}
			
			if (matrix[2][0] > 0.0f) {
				min[0] += mMin.z * matrix[2][0];
				max[0] += mMax.z * matrix[2][0];
			}
			else {
				min[0] += mMax.z * matrix[2][0];
				max[0] += mMin.z * matrix[2][0];
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
				min[1] += mMin.y * matrix[1][1];
				max[1] += mMax.y * matrix[1][1];
			}
			else {
				min[1] += mMax.y * matrix[1][1];
				max[1] += mMin.y * matrix[1][1];
			}

			if (matrix[2][1] > 0.0f) {
				min[1] += mMin.z * matrix[2][1];
				max[1] += mMax.z * matrix[2][1];
			}
			else {
				min[1] += mMax.z * matrix[2][1];
				max[1] += mMin.z * matrix[2][1];
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
				min[2] += mMin.y * matrix[1][2];
				max[2] += mMax.y * matrix[1][2];
			}
			else {
				min[2] += mMax.y * matrix[1][2];
				max[2] += mMin.y * matrix[1][2];
			}

			if (matrix[2][2] > 0.0f) {
				min[2] += mMin.z * matrix[2][2];
				max[2] += mMax.z * matrix[2][2];
			}
			else {
				min[2] += mMax.z * matrix[2][2];
				max[2] += mMin.z * matrix[2][2];
			}
		}
		inline Vector3 GetGenterPoint() {
			return (mMin + mMax) * 0.5f;
		}
		inline Vector3 GetSizeVector() {
			return mMax - mMin;
		}
		inline Vector3 GetRadiusVector() {
			return this->GetSizeVector() * 0.5f;
		}
	private:
		Vector3 mMin;
		Vector3 mMax;
	};
	
	class Plane 
	{
	public:
		static Vector3 ComputeBestFitNormal(const std::vector<Vector3>& points) 
		{
			Vector3 normal = Vector3::Zero;
			
			auto iter = points.begin();
			while (iter != points.end()) {
				Vector3 currentPoint = *iter;
				
				Vector3 nextPoint;
				if ((iter + 1) == points.end()) {
					nextPoint = *(points.begin());
				}
				else {
					nextPoint = *(iter + 1);
				}

				normal.x += (currentPoint.z + nextPoint.z) * (currentPoint.y - nextPoint.y);
				normal.y += (currentPoint.x + nextPoint.x) * (currentPoint.z - nextPoint.z);
				normal.z += (currentPoint.y + nextPoint.y) * (currentPoint.x - nextPoint.x);

				iter++;
			}

			return normal.Normalize();
		}

		static float ComputeBestFitPlane(const std::vector<Vector3>& points, const Vector3& normal) 
		{
			Vector3 avgPoint = Vector3::Zero;
			
			for (auto iter = points.begin(); iter != points.end(); iter++) {
				avgPoint = avgPoint + (*iter);
			}

			return avgPoint.Dot(normal) / points.size();
		}
	public:
		inline float DistanceToPoint(const Vector3& point) {
			return point.Dot(mNormal) - mDistance;
		}
	private:
		Vector3 mNormal;
		float mDistance;
	};

	struct TriangleEdge {
		Vector3 e1;
		Vector3 e2;
		Vector3 e3;
	};
	class Triangle {
	public:
		Vector3 v1, v2, v3;
	public:
		Triangle() = default;
		Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3) :
			v1(v1), v2(v2), v3(v3), mVertexIndices()
		{
			mNormal = (v2 - v1).Cross(v3 - v2).Normalize();
		}
		~Triangle() = default;
		
		inline TriangleEdge GetEdges() const {
			return {v3 - v2, v1 - v3, v2 - v1};
		}

		inline float GetPerimiter() const {
			const TriangleEdge& edges = this->GetEdges();
			
			return edges.e1.Magnitude() + edges.e2.Magnitude() + edges.e3.Magnitude();
		}

		inline float GetArea2D() const {
			return ((v1.y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - v1.x)) * 0.5f;
		}

		inline float GetArea3D() const {
			const Vector3& e1 = v3 - v2;
			const Vector3& e2 = v3 - v1;
			
			return e1.Cross(e2).Magnitude() * 0.5f;
		}

		inline Vector3 BarycentricToCartersian(float b1, float b2, float b3) {
			return v1 * b1 + v2 * b2 + v3 * b3;
		}
		
		inline Vector3 BarycentricToCartersian(const Vector3& baryCentricCoords) {
			return v1 * baryCentricCoords.x + v2 * baryCentricCoords.y + v3 * baryCentricCoords.z;
		}

		inline Vector3 GetNormal() const {
			const Vector3& e1 = v3 - v2;
			const Vector3& e2 = v1 - v3;

			return e1.Cross(e2);
		}

		inline static Vector3 ComputeBaryCentricPointProjectedOn2D(
			const Triangle& triangle, 
			const Vector3& point)
		{
			Vector3 outpoint;
			const Vector3& normal = triangle.GetNormal();
			float maxFactor = std::max(std::abs(normal.x), 
				std::max(std::abs(normal.y), std::abs(normal.z)));

			// Select plane of projection
			Vector3 e1, e2;
			Vector3 subE3, subE1;

			e1 = triangle.v3 - triangle.v2;
			e2 = triangle.v1 - triangle.v3;
			subE1 = point - triangle.v1;
			subE3 = point - triangle.v3;

			if (maxFactor == std::abs(normal.x)) 
			{
				// Discard X, project on xz plane
				e1.x = 0;
				e2.x = 0;

				subE1.x = 0;
				subE3.x = 0;
			}
			else if (maxFactor == std::abs(normal.y)) {
				// Discard Y, project on xz plane
				e1.y = 0;
				e2.y = 0;
				
				subE1.y = 0;
				subE3.y = 0;
			}
			else {
				// Discard Z, project on xy plane				
				e1.z = 0;
				e2.z = 0;

				subE1.z = 0;
				subE3.z = 0;
			}

			float denominator = e1.Cross(e2).Magnitude();
			if (denominator == 0.0f) {
				return outpoint;
			}

			float subTriangle1Area = e1.Cross(subE3).Magnitude();
			float subTriangle2Area = e2.Cross(subE1).Magnitude();

			outpoint.x = subTriangle1Area / denominator;
			outpoint.y = subTriangle2Area / denominator;
			outpoint.z = 1.0f - outpoint.x - outpoint.y;
			
			return outpoint;
		}

		// Compute Barycentric point in 3D - better for SIMD instructions
		inline static Vector3 ComputeBaryCentricPoint(
			const Triangle& triangle,
			const Vector3& point)
		{
			Vector3 outpoint;

			const Vector3& surfaceNormal = triangle.GetNormal();
			const Vector3& normalizedSurfaceNormal = surfaceNormal.Normalize();
			const TriangleEdge& edges = triangle.GetEdges();
			float denominator = edges.e1.Cross(edges.e2).Dot(normalizedSurfaceNormal);

			outpoint.x = (edges.e1.Cross(point - triangle.v3).Dot(normalizedSurfaceNormal)) / denominator;
			outpoint.y = (edges.e2.Cross(point - triangle.v1).Dot(normalizedSurfaceNormal)) / denominator;
			outpoint.z = (edges.e3.Cross(point - triangle.v2).Dot(normalizedSurfaceNormal)) / denominator;
			
			return outpoint;
		}
		
		inline void GetGravityPoint(
			Vector3& outPointInCartersian,
			Vector3& outPointInBaryCentric) const 
		{
			outPointInBaryCentric = Vector3(1 / 3.0f);

			outPointInCartersian = (v1 + v2 + v3) * (1 / 3.0f);
		}

		inline void GetIncenter(
			Vector3& outPointInCartersian,
			Vector3& outPointInBaryCentric,
			float& outRadius
		) const 
		{
			const TriangleEdge& edges = this->GetEdges();

			outPointInBaryCentric = Vector3(edges.e1.Magnitude(), edges.e2.Magnitude(), 
				edges.e3.Magnitude()) / this->GetPerimiter();

			outPointInCartersian = (v1 * edges.e1.Magnitude() + v2 * edges.e2.Magnitude() + 
				v3 * edges.e3.Magnitude()) / this->GetPerimiter();
			
			outRadius = this->GetArea3D() / this->GetPerimiter();
		}

		inline float GetInscribedCirlceRadius() const {
			return this->GetArea3D() / this->GetPerimiter();
		}

		inline void GetCircumcenterPoint(
			Vector3& outPointInCartersian,
			Vector3& outPointInBaryCentric, 
			float& outRadius)
		{
			const TriangleEdge& edges = this->GetEdges();
			float d1 = -edges.e2.Dot(edges.e3);
			float d2 = -edges.e3.Dot(edges.e1);
			float d3 = -edges.e1.Dot(edges.e2);
			float c1 = d2 * d3;
			float c2 = d1 * d3;
			float c3 = d1 * d2;
			float c = c1 + c2 + c3;

			outPointInBaryCentric.x = (c2 + c3) / (2 * c);
			outPointInBaryCentric.y = (c3 + c1) / (2 * c);
			outPointInBaryCentric.z = (c1 + c2) / (2 * c);
			
			outPointInCartersian = (v1 * (c2 + c3) + v2 * (c3 + c1) + v3 * (c1 + c2)) / (2 * c);
			
			outRadius = sqrtf((d1 + d2) * (d2 + d3) * (d1 + d3) / c) / 2;
		}
	
		uint8_t GetVertexIndex(uint8_t idx) const { return mVertexIndices[idx]; }
		Vector3 GetNormal() const { return mNormal; }
	private:
			uint8_t mVertexIndices[3];
			Vector3 mNormal;
	};
	
	struct Vertex {
		Vector3 Position;
		Vector3 Color;
		Vector3 Normal;
		Vector2 TextureCoords;
	};

	class TriangleMesh {
	public:
		TriangleMesh() = default;
		~TriangleMesh() = default;
		void ComputeVertexNormals();
	private:
		std::vector<Vertex> mVertices;
		std::vector<Triangle> mTriangles;
	};

	class Polygon {
	public:
		inline static bool IsConvex(const Vector3 vertices[], int numOfVertices) {
			float angleSum = 0.0f;

			for (uint8_t i = 0; i < numOfVertices; i++) {
				Vector3 e1, e2;

				if (i == 0) {
					e1 = vertices[numOfVertices - 1] - vertices[0];
				}
				else {
					e1 = vertices[i - 1] - vertices[i];
				}

				if (i == numOfVertices - 1) {
					e2 = vertices[0] - vertices[i];
				}
				else {
					e2 = vertices[i + 1] - vertices[i];
				}

				e1 = e1.Normalize();
				e2 = e2.Normalize();

				// Get smaller angle (exterior or interior)
				float dot = e1.Dot(e2);

				angleSum += std::acosf(dot);
			}

			float convexSumAngle = (numOfVertices - 2) * PI;

			if (angleSum < convexSumAngle - numOfVertices * 0.0001f) {
				return false;
			}

			return true;
		}
	};
}