#include "include/Collision.h"
#include<array>

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

void TriangleMesh::ComputeBasisVectors()
{
	std::uint32_t vertexCount = mVertices.size();
	Vector3* tempTangent = new Vector3[vertexCount];
	Vector3* tempBinormal = new Vector3[vertexCount];

	for (std::uint32_t i = 0; i < vertexCount; i++) {
		tempTangent[i].SetZero();
		tempBinormal[i].SetZero();
	}

	// Avg basis vectors for each face into its neighboring vertices
	for (std::uint32_t i = 0; i < vertexCount; i++) {
		const Triangle& tri = mTriangles[i];
		const Vertex& v0 = mVertices[tri.GetVertexIndex(0)];
		const Vertex& v1 = mVertices[tri.GetVertexIndex(1)];
		const Vertex& v2 = mVertices[tri.GetVertexIndex(2)];

		// Compute intermediate values
		Vector3 q1 = v1.Position - v0.Position;
		Vector3 q2 = v2.Position - v0.Position;
		float s1 = v1.TextureCoords.x - v0.TextureCoords.x;
		float s2 = v2.TextureCoords.x - v0.TextureCoords.x;
		float t1 = v1.TextureCoords.y - v0.TextureCoords.y;
		float t2 = v2.TextureCoords.y - v0.TextureCoords.y;

		// Compute basis vectors for the triangle
		Vector3 tangent = t2 * q1 - t1 * q2;
		tangent.Normalized();
		Vector3 binormal = -s2 * q1 + s1 * q2;
		binormal.Normalized();

		for (std::uint8_t i = 0; i < 3; i++) {
			tempTangent[tri.GetVertexIndex(i)] += tangent;
			tempBinormal[tri.GetVertexIndex(i)] += binormal;
		}
	}

	// Ensure the tangent and binormal are perpendicular to the normal
	for (std::uint32_t i = 0; i < vertexCount; i++) {
		Vertex& v = mVertices[i];
		Vector3 t = tempTangent[i];

		// Use Gram-Schmit solution
		t -= v.Normal * t.Dot(v.Normal);
		t.Normalized();
		v.Tangent = t;

		// Figure if we're mirrored
		if (v.Normal.Cross(t).Dot(tempBinormal[i]) < 0.0f) {
			v.Det = -1.0f; // We're mirrored
		}
		else {
			v.Det = 1.0f; // We're not mirrored
		}
	}

	delete[] tempTangent;
	delete[] tempBinormal;
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

float LineSegment::MinDistanceSquared(const LineSegment& s1, const LineSegment& s2)
{

	Vector3   u = s1.mEnd - s1.mStart;
	Vector3   v = s2.mEnd - s2.mStart;
	Vector3   w = s1.mStart - s2.mStart;
	float    a = u.Dot(u);         // always >= 0
	float    b = u.Dot(v);
	float    c = v.Dot(v);         // always >= 0
	float    d = u.Dot(w);
	float    e = v.Dot(w);
	float    D = a * c - b * b;        // always >= 0
	float    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
	float    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

								   // compute the line parameters of the two closest points
	if (Math::NearZero(D)) { // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else {                 // get the closest points on the infinite lines
		sN = (b * e - c * d);
		tN = (a * e - b * d);
		if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (Math::NearZero(sN) ? 0.0f : sN / sD);
	tc = (Math::NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	Vector3   dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

	return dP.LengthSq();   // return the closest distance squared
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