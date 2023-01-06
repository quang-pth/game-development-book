#include "include/Collision.h"

void TriangleMesh::ComputeVertexNormals()
{
	// Clear the triangle mesh vertices normal
	for (Vertex& vertex : mVertices) {
		vertex.Normal = Vector3::Zero;
	}

	for (Triangle& triangle : mTriangles) {
		for (uint8_t idx = 0; idx < 3; idx++) {
			mVertices[triangle.GetVertexIndex(idx)].Normal += triangle.GetNormal();
		}
	}

	// Average vertex normal
	for (Vertex& vertex : mVertices) {
		vertex.Normal = vertex.Normal.Normalize();
	}
}

Vector3 LineSegment::PointOnSegment(float t) const
{
	return mStart + (mEnd - mStart) * t;
}

float LineSegment::MinDistanceSquared(const Vector3& point) const
{
	Vector3 startToPoint = point - mStart;
	if (startToPoint.Dot(mEnd - mStart) < 0) {
		return startToPoint.LengthSq();
	}

	Vector3 endToPoint = -startToPoint;
	if (endToPoint.Dot(mStart - mEnd) < 0) {
		return endToPoint.LengthSq();
	}

	Vector3 startToEnd = mEnd - mStart;
	Vector3 p = startToPoint.Dot(startToEnd.Normalize()) * startToEnd.Normalize();

	return (startToPoint - p).LengthSq();
}

float LineSegment::MinDistance(const Vector3& point) const
{
	return std::sqrtf(this->MinDistanceSquared(point));
}

Plane::Plane(const Vector3& normal, float distance) : 
	mNormal(normal), mDistance(distance)
{

}

Plane::Plane(const Triangle& triangle)
{
	mNormal = triangle.GetNormal();
	mDistance = mNormal.Dot(triangle.v1);
}

Plane::Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	Plane(Triangle(v1, v2, v3));
}