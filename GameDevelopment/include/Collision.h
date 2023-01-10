#pragma once

#include "include/CustomMath.h"
#include <algorithm>
#include <vector>

struct Vertex {
	Vector3 Position;
	Vector2 TextureCoords;
	Vector3 Normal;
	Vector3 Tangent;
	float Det;
};

struct LineSegment {
	Vector3 mStart;
	Vector3 mEnd;
	Vector3 PointOnSegment(float t) const;
	float MinDistanceSquared(const Vector3& point) const;
	static float MinDistanceSquared(const LineSegment& s1, const LineSegment& s2);
	float MinDistance(const Vector3& point) const;
};

struct Capsule {
	LineSegment mSegment;
	float mRadius;
	inline bool Contains(const Vector3& point) const {
		float distanceSq = mSegment.MinDistanceSquared(point);
		float radiusSq = mRadius * mRadius;
		return distanceSq <= radiusSq;
	}
};

struct Sphere {
	float mRadius;
	Vector3 mCenter;
	inline bool Contains(const Vector3& point) const {
		float distanceSq = (point - mCenter).LengthSq();
		float radiusSq = mRadius * mRadius;
		return distanceSq <= radiusSq;
	}
};

struct TriangleEdge {
	Vector3 e1;
	Vector3 e2;
	Vector3 e3;
};

struct OBB {
	Vector3 mCenter;
	Quaternion mRotation;
	Vector3 mExtents; // Width, Height and Depth of the oriented-bounding box
	/*
	* The collision computations of an OBB are far more expensive than an AABB
	*/
};

class AABB
{
public:
	Vector3 mMin;
	Vector3 mMax;
	AABB() {
		this->Empty();
	};
	AABB(const std::vector<Vector3>& points) {
		this->Empty();
		for (const Vector3& point : points) {
			this->UpdateMinMax(point);
		}
	}
	~AABB() {};
	inline void Empty() {
		mMin.x = mMin.y = mMin.z = std::numeric_limits<float>::infinity();
		mMax.x = mMax.y = mMax.z = -std::numeric_limits<float>::infinity();
	}
	inline void UpdateMinMax(const Vector3& point) {
		// MIN bound
		mMin.x = std::min(point.x, mMin.x);
		mMin.y = std::min(point.y, mMin.y);
		mMin.z = std::min(point.z, mMin.z);
		// MAX bound
		mMax.x = std::max(point.x, mMax.x);
		mMax.y = std::max(point.y, mMax.y);
		mMax.z = std::max(point.z, mMax.z);
	}
	inline void Rotate(const Quaternion& quaternion) {
		Vector3 points[8];
		points[0] = Vector3(mMin);
		points[1] = Vector3(mMax.x, mMin.y, mMin.z);
		points[2] = Vector3(mMin.x, mMax.y, mMin.z);
		points[3] = Vector3(mMin.x, mMin.y, mMax.z);
		points[4] = Vector3(mMin.x, mMax.y, mMax.z);
		points[5] = Vector3(mMax.x, mMin.y, mMax.z);
		points[6] = Vector3(mMax.x, mMax.y, mMin.z);
		points[0] = Vector3(mMax);
		
		Vector3 p = Vector3::Transform(points[0], quaternion);
		mMin = p;
		mMax = p;

		for (std::uint8_t i = 0; i < sizeof(points) / sizeof(Vector3); i++) {
			p = Vector3::Transform(points[i], quaternion);
			this->UpdateMinMax(p);
		}
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
	inline bool Contains(const Vector3& point) const {
		bool inBoundX = point.x >= mMin.x && point.x <= mMax.x;
		bool inBoundY = point.y >= mMin.y && point.y <= mMax.y;
		bool inBoundZ = point.z >= mMin.z && point.z <= mMax.z;
		return inBoundX && inBoundY && inBoundZ;
	}
	inline float MinDistanceSquared(const Vector3& point) const {
		float dx = Math::Max(mMin.x - point.x, 0.0f);
		dx = Math::Max(dx, point.x - mMax.x);
		float dy = Math::Max(mMin.y - point.y, 0.0f);
		dy = Math::Max(dy, point.y - mMax.y);
		float dz = Math::Max(mMin.z - point.z, 0.0f);
		dz = Math::Max(dz, point.z - mMax.z);
		return dx * dx + dy * dy + dz * dz;
	}
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
		return { v3 - v2, v1 - v3, v2 - v1 };
	}

	inline float GetPerimiter() const {
		const TriangleEdge& edges = this->GetEdges();

		return edges.e1.Length() + edges.e2.Length() + edges.e3.Length();
	}

	inline float GetArea2D() const {
		return ((v1.y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - v1.x)) * 0.5f;
	}

	inline float GetArea3D() const {
		const Vector3& e1 = v3 - v2;
		const Vector3& e2 = v3 - v1;

		return e1.Cross(e2).Length() * 0.5f;
	}

	inline Vector3 BarycentricToCartersian(float b1, float b2, float b3) {
		return v1 * b1 + v2 * b2 + v3 * b3;
	}

	inline Vector3 BarycentricToCartersian(const Vector3& baryCentricCoords) {
		return v1 * baryCentricCoords.x + v2 * baryCentricCoords.y + v3 * baryCentricCoords.z;
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

		float denominator = e1.Cross(e2).Length();
		if (denominator == 0.0f) {
			return outpoint;
		}

		float subTriangle1Area = e1.Cross(subE3).Length();
		float subTriangle2Area = e2.Cross(subE1).Length();

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
	
	// Compute Barycentric point in 3D - better for SIMD instructions
	// v1, v2, v3 are three vertices that form a valid triangle
	inline static Vector3 ComputeBaryCentricPoint(
		const Vector3& v1, const Vector3& v2, const Vector3& v3,
		const Vector3& point)
	{
		return Triangle::ComputeBaryCentricPoint(Triangle(v1, v2, v3), point);
	}

	inline bool Contains(const Vector3& point) const {
		const Vector3& barycentricCoords = Triangle::ComputeBaryCentricPoint(*this, point);
		bool outside = (barycentricCoords.x < 0 || barycentricCoords.x > 1)
			|| (barycentricCoords.y < 0 || barycentricCoords.y > 1)
			|| (barycentricCoords.z < 0 || barycentricCoords.z > 1);
		
		return !outside;
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

		outPointInBaryCentric = Vector3(edges.e1.Length(), edges.e2.Length(),
			edges.e3.Length()) * (1 / this->GetPerimiter());

		outPointInCartersian = (v1 * edges.e1.Length() + v2 * edges.e2.Length() +
			v3 * edges.e3.Length()) * (1 / this->GetPerimiter());

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

		outPointInCartersian = (v1 * (c2 + c3) + v2 * (c3 + c1) + v3 * (c1 + c2)) * (1 / (2 * c));

		outRadius = sqrtf((d1 + d2) * (d2 + d3) * (d1 + d3) / c) / 2;
	}

	uint8_t GetVertexIndex(uint8_t idx) const { return mVertexIndices[idx]; }
	Vector3 GetNormal() const { return mNormal; }
private:
	uint8_t mVertexIndices[3];
	Vector3 mNormal;
};

class Plane
{
public:
	Vector3 mNormal;
	float mDistance;
	Plane(const Vector3& normal, float distance);
	Plane(const Triangle& triangle);
	Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3);
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
	inline bool Contains(const Vector3& point) const {
		return (point.Dot(mNormal) + mDistance) == 0.0f;
	}
	// Return a signed distance from a point to the plane
	inline float DistanceToPoint(const Vector3& point) {
		return point.Dot(mNormal) - mDistance;
	}
};

class TriangleMesh {
public:
	TriangleMesh() = default;
	~TriangleMesh() = default;
	void ComputeVertexNormals();
	// Compute basis vectors of a triangle mesh such as normal, tangent and binormal
	void ComputeBasisVectors();
private:
	std::vector<Vertex> mVertices;
	std::vector<Triangle> mTriangles;
};

class Polygon {
public:
	Polygon(const std::vector<Vector3>& points) {
		memcpy(mVertices.data(), points.data(), points.size() * sizeof(Vector3));
	}
	inline static bool IsConvex(const std::vector<Vector3>& vertices) {
		float angleSum = 0.0f;
		std::uint32_t numOfVertices = vertices.size();

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

		float convexSumAngle = (numOfVertices - 2) * Math::Pi;

		if (angleSum < convexSumAngle - numOfVertices * 0.0001f) {
			return false;
		}

		return true;
	}
	inline bool Contains(const Vector3& point) const {
		float sumAngle = 0.0f;

		Vector3 v1, v2;
		for (std::uint32_t i = 0; i < mVertices.size() - 1; i++) {
			v1 = mVertices[i] - point;
			v1.Normalized();

			v2 = mVertices[i + 1] - point;
			v2.Normalized();

			sumAngle += Math::Acos(v1.Dot(v2));
		}

		v1 = mVertices.front() - point;
		v1.Normalized();
		v2 = mVertices.back() - point;
		v2.Normalized();
		sumAngle += Math::Acos(v1.Dot(v2));

		return Math::NearZero(sumAngle - Math::TwoPi);
	}
private:
	std::vector<Vector3> mVertices;
};

class Collision {
public:
	inline static bool Intersect(const AABB& a, const AABB& b) {
		bool outsideX = a.mMin.x > b.mMax.x || a.mMax.x < b.mMin.x;
		bool outsideY = a.mMin.y > b.mMax.y || a.mMax.y < b.mMin.y;
		bool outsideZ = a.mMin.z > b.mMax.z || a.mMax.z < b.mMin.z;
		return !(outsideX && outsideY && outsideZ);
	}
	inline static bool Intersect(const AABB& box, const Sphere& sphere) {
		float distanceSq = box.MinDistanceSquared(sphere.mCenter);
		float radiusSq = sphere.mRadius * sphere.mRadius;
		return distanceSq <= radiusSq;
	}
	inline static bool Intersect(const Sphere& a, const Sphere& b) {
		float centerDistSq = (a.mCenter- b.mCenter).LengthSq();
		float radiusDistSq = std::pow(a.mRadius + b.mRadius, 2);
		return centerDistSq <= radiusDistSq;
	}
	inline static bool Intersect(const Capsule& a, const Capsule& b) {
		float distanceSq = LineSegment::MinDistanceSquared(a.mSegment, b.mSegment);
		float radiusSq = std::pow(a.mRadius + b.mRadius, 2);
		return distanceSq <= radiusSq;
	}
	inline static bool Intersect(const LineSegment& l, const Plane& p, float& outT) {
		// Check if the line is on the plane
		if (p.Contains(l.mStart) && p.Contains(l.mEnd)) {
			outT = 0.0f;
			return true;
		}
		// Check if the line is parallel to the plane
		else if (Math::NearZero((l.mStart - l.mEnd).Dot(p.mNormal))) {
			outT = -1.0f;
			return false;
		}
		
		float nominator = -l.mStart.Dot(p.mNormal) - p.mDistance;
		float denominator = (l.mStart - l.mEnd).Dot(p.mNormal);
		outT = nominator / denominator;

		return outT >= 0.0f && outT <= 1.0f;
	}
	inline static bool Intersect(const LineSegment& l, const Sphere& s, float& outT) {
		Vector3 x = l.mStart - s.mCenter;
		Vector3 y = l.mEnd - l.mStart;
		float a = y.Dot(y);
		float b = 2 * x.Dot(y);
		float c = x.Dot(x) - s.mRadius * s.mRadius;
		float discriminant = b * b - 4 * a * c;
		// Segment doesnt intersect with the sphere
		if (discriminant < 0) {
			outT = -1.0f;
			return false;
		}
		else {
			discriminant = Math::Sqrt(discriminant);
			float minT = (-b - discriminant) / (2.0f * a);
			float maxT = (-b + discriminant) / (2.0f * a);
			// Segment is outside the sphere and intersect with the sphere
			if (minT >= 0.0f && minT <= 1.0f) {
				outT = minT;
				return true;
			}
			// Segment is inside the sphere and interst with the sphere
			else if (maxT >= 0.0f && maxT <= 1.0f) {
				outT = maxT;
				return true;
			}
			else {
				outT = -1.0f;
				return false;
			}
		}
	}
	inline static bool TestSidePlane(float start, float end, float negd, 
		const Vector3& normal, std::vector<std::pair<float, Vector3>>& tValues) {
		float denom = end - start;
		if (Math::NearZero(denom)) {
			return false;
		}

		float numer = -start + negd;
		float t = numer / denom;
		if (t >= 0.0f && t <= 1.0f) {
			tValues.emplace_back(std::pair<float, Vector3>(t, normal));
			return true;
		}
		else {
			return false;
		}
	}
	inline static bool Intersect(const LineSegment& l, const AABB& box, float& outT, Vector3& outNormal) {
		std::vector<std::pair<float, Vector3>> tValues;
		// Test segment intersect on x planes
		Collision::TestSidePlane(l.mStart.x, l.mEnd.x, box.mMin.x, Vector3::NegUnitX, tValues);
		Collision::TestSidePlane(l.mStart.x, l.mEnd.x, box.mMax.x, Vector3::UnitX, tValues);
		// Test segment intersect on y planes
		Collision::TestSidePlane(l.mStart.y, l.mEnd.y, box.mMin.y, Vector3::NegUnitY, tValues);
		Collision::TestSidePlane(l.mStart.y, l.mEnd.y, box.mMax.y, Vector3::UnitY, tValues);
		// Test segment intersect on z planes
		Collision::TestSidePlane(l.mStart.z, l.mEnd.z, box.mMin.z, Vector3::NegUnitZ, tValues);
		Collision::TestSidePlane(l.mStart.z, l.mEnd.z, box.mMax.z, Vector3::UnitY, tValues);
		// Test for the box that contains any points of intersection
		std::sort(tValues.begin(), tValues.end(), 
			[](std::pair<float, Vector3>& t1, std::pair<float, Vector3>& t2) 
			{
				return t1.first < t2.first;
			}
		);
		for (std::pair<float, Vector3> pair : tValues) {
			Vector3 point = l.PointOnSegment(pair.first);
			if (box.Contains(point)) {
				outT = pair.first;
				outNormal = pair.second;
				return true;
			}
		}

		outT = -1.0f;
		return false;
	}
	inline static bool SweptSphere(const Sphere& p0, const Sphere& p1, const Sphere& q0, const Sphere& q1, float& outT) {
		Vector3 x = p0.mCenter - q0.mCenter;
		Vector3 y = (p1.mCenter - p0.mCenter) - (q1.mCenter - q0.mCenter);
		float a = y.Dot(y);
		float b = 2 * x.Dot(y);
		float c = x.Dot(x) - std::pow(p0.mRadius + q0.mRadius, 2);
		float discriminant = b * b - 4 * a * c;
		if (Math::NearZero(discriminant)) {
			outT = -1.0f;
			return false;
		}

		discriminant = Math::Sqrt(discriminant);
		// Takes the smaller solution to get the first point of intersection
		float minT = (-b - discriminant) / (2.0f * a);
		
		if (minT >= 0.0f && minT <= 1.0f) {
			outT = minT;
			return true;
		}

		outT = -1.0f;
		return false;
	}
};