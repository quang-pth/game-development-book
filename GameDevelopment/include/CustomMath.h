// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
	const float Pi = 3.1415926535f;
	const float TwoPi = Pi * 2.0f;
	const float PiOver2 = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float Fmod(float numer, float denom)
	{
		return fmod(numer, denom);
	}
}

// 2D Vector
class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		, y(0.0f)
	{}

	explicit Vector2(float inX, float inY)
		:x(inX)
		, y(inY)
	{}

	// Set both components in one line
	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	// Vector addition (a + b)
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	// Vector subtraction (a - b)
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	// Component-wise multiplication
	// (a.x * b.x, ...)
	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	// Scalar multiplication
	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	// Scalar multiplication
	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}
	
	friend Vector2 operator/(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x, vec.y) * (1 / scalar);
	}

	friend bool operator==(const Vector2& vec, const Vector2& other) {
		return vec.x == other.x && vec.y == other.y;
	}
	
	friend bool operator!=(const Vector2& vec, const Vector2& other) {
		return !(vec == other);
	}

	// Scalar *=
	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	// Vector +=
	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	// Vector -=
	Vector2& operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	const float* GetAsFloatPtr() const {
		return reinterpret_cast<const float*>(&x);
	}

	// Length squared of vector
	float LengthSquared() const
	{
		return (x * x + y * y);
	}

	// Length of vector
	float Length() const
	{
		return (Math::Sqrt(LengthSquared()));
	}

	// Normalize this vector
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	// Normalize the provided vector
	static Vector2 Normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x + a.y * b.y);
	}

	// Lerp from A to B by f
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
	{
		return Vector2(a + f * (b - a));
	}

	// Reflect V about (normalized) N
	static Vector2 Reflect(const Vector2& v, const Vector2& n)
	{
		return v - 2.0f * Vector2::Dot(v, n) * n;
	}

	// Transform vector by matrix
	static Vector2 Transform(const Vector2& vec, const class Matrix3& mat, float w = 1.0f);

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};

// 3D Vector
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
		:x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}

	explicit Vector3(float inX, float inY, float inZ)
		:x(inX)
		, y(inY)
		, z(inZ)
	{}

	explicit Vector3(float scale) :
		x(scale), y(scale), z(scale) 
	{}

	explicit Vector3(const Vector2& vec) : 
		x(vec.x), y(vec.y), z(0.0f) 
	{}

	explicit Vector3(float x, float y) :
		x(x), y(y), z(0.0f)
	{}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// Set all three components in one line
	void Set(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	// Vector addition (a + b)
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	// Vector subtraction (a - b)
	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	// Negate a vector
	friend Vector3 operator-(const Vector3& a) 
	{
		return Vector3(-a.x, -a.y, -a.z);
	}

	// Component-wise multiplication
	friend Vector3 operator*(const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	// Scalar multiplication
	friend Vector3 operator*(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar multiplication
	friend Vector3 operator*(float scalar, const Vector3& vec)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	friend bool operator==(const Vector3& left, const Vector3& right) {
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	friend bool operator!=(const Vector3& left, const Vector3& right) {
		return !(left.x == right.x && left.y == right.y && left.z == right.z);
	}

	// Scalar *=
	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Vector +=
	Vector3& operator+=(const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	// Vector -=
	Vector3& operator-=(const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x * x + y * y + z * z);
	}

	// Length of vector
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// Normalize this vector
	Vector3 Normalize() const
	{
		float length = Length();
		return Vector3(this->x / length, this->y / length, this->z / length);
	}

	float Dot(const Vector3& other) const
	{
		return (this->x * other.x + this->y * other.y + this->z * other.z);
	}

	Vector3 Cross(const Vector3& other) const
	{
		Vector3 returnVector;
		returnVector.x = this->y * other.z - this->z * other.y;
		returnVector.y = this->z * other.x - this->x * other.z;
		returnVector.z = this->x * other.y - this->y * other.x;
		return returnVector;
	}

	// Lerp from a to b by t
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
	{
		return Vector3(a + t * (b - a));
	}

	// Reflect v about (normalized) n
	static Vector3 Reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2.0f * v.Dot(n) * n;
	}

	static Vector3 Transform(const Vector3& vec, const class Matrix4& mat, float w = 1.0f);
	// This will transform the vector and renormalize the w component
	static Vector3 TransformWithPerspDiv(const Vector3& vec, const class Matrix4& mat, float w = 1.0f);

	// Transform a Vector3 by a quaternion
	static Vector3 Transform(const Vector3& v, const class Quaternion& q);

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 NegUnitX;
	static const Vector3 NegUnitY;
	static const Vector3 NegUnitZ;
	static const Vector3 Infinity;
	static const Vector3 NegInfinity;
};

// 3x3 Matrix
class Matrix3
{
public:
	float mat[3][3];

	Matrix3()
	{
		*this = Matrix3::Identity;
	}

	explicit Matrix3(float inMat[3][3])
	{
		memcpy(mat, inMat, 9 * sizeof(float));
	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// Matrix multiplication
	friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
	{
		Matrix3 returnMatrix;
		// row 0
		returnMatrix.mat[0][0] =
			left.mat[0][0] * right.mat[0][0] +
			left.mat[0][1] * right.mat[1][0] +
			left.mat[0][2] * right.mat[2][0];

		returnMatrix.mat[0][1] =
			left.mat[0][0] * right.mat[0][1] +
			left.mat[0][1] * right.mat[1][1] +
			left.mat[0][2] * right.mat[2][1];

		returnMatrix.mat[0][2] =
			left.mat[0][0] * right.mat[0][2] +
			left.mat[0][1] * right.mat[1][2] +
			left.mat[0][2] * right.mat[2][2];

		// row 1
		returnMatrix.mat[1][0] =
			left.mat[1][0] * right.mat[0][0] +
			left.mat[1][1] * right.mat[1][0] +
			left.mat[1][2] * right.mat[2][0];

		returnMatrix.mat[1][1] =
			left.mat[1][0] * right.mat[0][1] +
			left.mat[1][1] * right.mat[1][1] +
			left.mat[1][2] * right.mat[2][1];

		returnMatrix.mat[1][2] =
			left.mat[1][0] * right.mat[0][2] +
			left.mat[1][1] * right.mat[1][2] +
			left.mat[1][2] * right.mat[2][2];

		// row 2
		returnMatrix.mat[2][0] =
			left.mat[2][0] * right.mat[0][0] +
			left.mat[2][1] * right.mat[1][0] +
			left.mat[2][2] * right.mat[2][0];

		returnMatrix.mat[2][1] =
			left.mat[2][0] * right.mat[0][1] +
			left.mat[2][1] * right.mat[1][1] +
			left.mat[2][2] * right.mat[2][1];

		returnMatrix.mat[2][2] =
			left.mat[2][0] * right.mat[0][2] +
			left.mat[2][1] * right.mat[1][2] +
			left.mat[2][2] * right.mat[2][2];

		return returnMatrix;
	}

	Matrix3& operator*=(const Matrix3& right)
	{
		*this = *this * right;
		return *this;
	}

	// Create a scale matrix with x and y scales
	static Matrix3 CreateScale(float xScale, float yScale)
	{
		float temp[3][3] =
		{
			{xScale, 0.0f, 0.0f},
			{0.0f, yScale, 0.0f},
			{0.0f, 0.0f, 1.0f},
		};
		return Matrix3(temp);
	}

	static Matrix3 CreateScale(const Vector2& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y);
	}

	// Create a scale matrix with a uniform factor
	static Matrix3 CreateScale(float scale)
	{
		return CreateScale(scale, scale);
	}

	// Create a rotation matrix about the Z axis
	// theta is in radians
	static Matrix3 CreateRotation(float theta)
	{
		float temp[3][3] =
		{
			{ Math::Cos(theta), Math::Sin(theta), 0.0f },
			{ -Math::Sin(theta), Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	// Create a translation matrix (on the xy-plane)
	static Matrix3 CreateTranslation(const Vector2& trans)
	{
		float temp[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, 1.0f },
		};
		return Matrix3(temp);
	}

	static const Matrix3 Identity;
};

// 4x4 Matrix
class Matrix4
{
public:
	float matrix[4][4];

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	explicit Matrix4(float inMatrix[4][4])
	{
		memcpy(matrix, inMatrix, 16 * sizeof(float));
	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&matrix[0][0]);
	}

	// Matrix multiplication (a * b)
	friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
	{
		Matrix4 returnMatrix;
		// row 0
		returnMatrix.matrix[0][0] =
			a.matrix[0][0] * b.matrix[0][0] +
			a.matrix[0][1] * b.matrix[1][0] +
			a.matrix[0][2] * b.matrix[2][0] +
			a.matrix[0][3] * b.matrix[3][0];

		returnMatrix.matrix[0][1] =
			a.matrix[0][0] * b.matrix[0][1] +
			a.matrix[0][1] * b.matrix[1][1] +
			a.matrix[0][2] * b.matrix[2][1] +
			a.matrix[0][3] * b.matrix[3][1];

		returnMatrix.matrix[0][2] =
			a.matrix[0][0] * b.matrix[0][2] +
			a.matrix[0][1] * b.matrix[1][2] +
			a.matrix[0][2] * b.matrix[2][2] +
			a.matrix[0][3] * b.matrix[3][2];

		returnMatrix.matrix[0][3] =
			a.matrix[0][0] * b.matrix[0][3] +
			a.matrix[0][1] * b.matrix[1][3] +
			a.matrix[0][2] * b.matrix[2][3] +
			a.matrix[0][3] * b.matrix[3][3];

		// row 1
		returnMatrix.matrix[1][0] =
			a.matrix[1][0] * b.matrix[0][0] +
			a.matrix[1][1] * b.matrix[1][0] +
			a.matrix[1][2] * b.matrix[2][0] +
			a.matrix[1][3] * b.matrix[3][0];

		returnMatrix.matrix[1][1] =
			a.matrix[1][0] * b.matrix[0][1] +
			a.matrix[1][1] * b.matrix[1][1] +
			a.matrix[1][2] * b.matrix[2][1] +
			a.matrix[1][3] * b.matrix[3][1];

		returnMatrix.matrix[1][2] =
			a.matrix[1][0] * b.matrix[0][2] +
			a.matrix[1][1] * b.matrix[1][2] +
			a.matrix[1][2] * b.matrix[2][2] +
			a.matrix[1][3] * b.matrix[3][2];

		returnMatrix.matrix[1][3] =
			a.matrix[1][0] * b.matrix[0][3] +
			a.matrix[1][1] * b.matrix[1][3] +
			a.matrix[1][2] * b.matrix[2][3] +
			a.matrix[1][3] * b.matrix[3][3];

		// row 2
		returnMatrix.matrix[2][0] =
			a.matrix[2][0] * b.matrix[0][0] +
			a.matrix[2][1] * b.matrix[1][0] +
			a.matrix[2][2] * b.matrix[2][0] +
			a.matrix[2][3] * b.matrix[3][0];

		returnMatrix.matrix[2][1] =
			a.matrix[2][0] * b.matrix[0][1] +
			a.matrix[2][1] * b.matrix[1][1] +
			a.matrix[2][2] * b.matrix[2][1] +
			a.matrix[2][3] * b.matrix[3][1];

		returnMatrix.matrix[2][2] =
			a.matrix[2][0] * b.matrix[0][2] +
			a.matrix[2][1] * b.matrix[1][2] +
			a.matrix[2][2] * b.matrix[2][2] +
			a.matrix[2][3] * b.matrix[3][2];

		returnMatrix.matrix[2][3] =
			a.matrix[2][0] * b.matrix[0][3] +
			a.matrix[2][1] * b.matrix[1][3] +
			a.matrix[2][2] * b.matrix[2][3] +
			a.matrix[2][3] * b.matrix[3][3];

		// row 3
		returnMatrix.matrix[3][0] =
			a.matrix[3][0] * b.matrix[0][0] +
			a.matrix[3][1] * b.matrix[1][0] +
			a.matrix[3][2] * b.matrix[2][0] +
			a.matrix[3][3] * b.matrix[3][0];

		returnMatrix.matrix[3][1] =
			a.matrix[3][0] * b.matrix[0][1] +
			a.matrix[3][1] * b.matrix[1][1] +
			a.matrix[3][2] * b.matrix[2][1] +
			a.matrix[3][3] * b.matrix[3][1];

		returnMatrix.matrix[3][2] =
			a.matrix[3][0] * b.matrix[0][2] +
			a.matrix[3][1] * b.matrix[1][2] +
			a.matrix[3][2] * b.matrix[2][2] +
			a.matrix[3][3] * b.matrix[3][2];

		returnMatrix.matrix[3][3] =
			a.matrix[3][0] * b.matrix[0][3] +
			a.matrix[3][1] * b.matrix[1][3] +
			a.matrix[3][2] * b.matrix[2][3] +
			a.matrix[3][3] * b.matrix[3][3];

		return returnMatrix;
	}

	Matrix4& operator*=(const Matrix4& right)
	{
		*this = *this * right;
		return *this;
	}

	// Invert the matrix - super slow
	void Invert();

	// Get the translation component of the matrix
	Vector3 GetTranslation() const
	{
		return Vector3(matrix[3][0], matrix[3][1], matrix[3][2]);
	}

	// Get the X axis of the matrix (forward)
	Vector3 GetXAxis() const
	{
		return Vector3(matrix[0][0], matrix[0][1], matrix[0][2]).Normalize();
	}

	// Get the Y axis of the matrix (left)
	Vector3 GetYAxis() const
	{
		return Vector3(matrix[1][0], matrix[1][1], matrix[1][2]).Normalize();
	}

	// Get the Z axis of the matrix (up)
	Vector3 GetZAxis() const
	{
		return Vector3(matrix[2][0], matrix[2][1], matrix[2][2]).Normalize();
	}

	// Extract the scale component from the matrix
	Vector3 GetScale() const
	{
		Vector3 returnVector;
		returnVector.x = Vector3(matrix[0][0], matrix[0][1], matrix[0][2]).Length();
		returnVector.y = Vector3(matrix[1][0], matrix[1][1], matrix[1][2]).Length();
		returnVector.z = Vector3(matrix[2][0], matrix[2][1], matrix[2][2]).Length();
		return returnVector;
	}

	// Create a scale matrix with x, y, and z scales
	static Matrix4 CreateScale(float xScale, float yScale, float zScale)
	{
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, zScale, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateScale(const Vector3& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
	}

	// Create a scale matrix with a uniform factor
	static Matrix4 CreateScale(float scale)
	{
		return CreateScale(scale, scale, scale);
	}

	// Rotation about x-axis
	static Matrix4 CreateRotationX(float theta)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f , 0.0f },
			{ 0.0f, Math::Cos(theta), Math::Sin(theta), 0.0f },
			{ 0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Rotation about y-axis
	static Matrix4 CreateRotationY(float theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ Math::Sin(theta), 0.0f, Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Rotation about z-axis
	static Matrix4 CreateRotationZ(float theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f },
			{ -Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Create a rotation matrix from a quaternion
	static Matrix4 CreateFromQuaternion(const class Quaternion& q);

	static Matrix4 CreateTranslation(const Vector3& trans)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zAxis = (target - eye).Normalize();
		Vector3 xAxis = up.Cross(zAxis).Normalize();
		Vector3 yAxis = zAxis.Cross(xAxis).Normalize();
		Vector3 translate;
		translate.x = -xAxis.Dot(eye);
		translate.y = -yAxis.Dot(eye);
		translate.z = -zAxis.Dot(eye);

		float returnMatrix[4][4] =
		{
			{ xAxis.x, yAxis.x, zAxis.x, 0.0f },
			{ xAxis.y, yAxis.y, zAxis.y, 0.0f },
			{ xAxis.z, yAxis.z, zAxis.z, 0.0f },
			{ translate.x, translate.y, translate.z, 1.0f }
		};
		return Matrix4(returnMatrix);
	}

	static Matrix4 CreateOrtho(float width, float height, float near, float far)
	{
		float returnMatrix[4][4] =
		{
			{ 2.0f / width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2.0f / height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f / (far - near), 0.0f },
			{ 0.0f, 0.0f, near / (near - far), 1.0f }
		};
		return Matrix4(returnMatrix);
	}

	static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far)
	{
		float xScale = Math::Cot(fovY / 2.0f);
		float yScale = xScale * width / height;
		float returnMatrix[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, far / (far - near), 1.0f },
			{ 0.0f, 0.0f, -near * far / (far - near), 0.0f }
		};
		return Matrix4(returnMatrix);
	}

	static Matrix4 CreateSimpleViewProj(float width, float height)
	{
		float returnMatrix[4][4] =
		{
			{ 2.0f / width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2.0f / height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f }
		};
		return Matrix4(returnMatrix);
	}

	static const Matrix4 Identity;
};

// (Unit) Quaternion
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;
public:
	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	// This directly sets the quaternion components --
	// don't use for axis/angle
	explicit Quaternion(float inX, float inY, float inZ, float inW)
	{
		Set(inX, inY, inZ, inW);
	}

	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	explicit Quaternion(const Vector3& axis, float angle)
	{
		float scalar = Math::Sin(angle / 2.0f);
		x = axis.x * scalar;
		y = axis.y * scalar;
		z = axis.z * scalar;
		w = Math::Cos(angle / 2.0f);
	}

	explicit Quaternion(float angle, const Vector3& axis) {
		Quaternion(axis, angle);
	}
public:
	friend Quaternion operator*(const Quaternion& p, const Quaternion& q) {
		float w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
		float x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
		float y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
		float z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;

		return Quaternion(x, y, z, w);
	}

	friend Quaternion operator*(const Quaternion& q, float scalar) {
		return Quaternion(q.x * scalar, q.y * scalar, q.z * scalar, q.w * scalar);
	}
	
	friend Quaternion operator*(float scalar, const Quaternion& q) {
		return q * scalar;
	}

	friend Quaternion operator/(const Quaternion& q, float scalar) {
		return q * (1 / scalar);
	}

	friend Quaternion operator+(const Quaternion& p, const Quaternion& q) {
		return Quaternion(p.w + q.w, p.x + q.x, p.y + q.y, p.z + q.z);
	}
public:
	// Directly set the internal components
	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}
	
	void SetVector(const Vector3& vector) {
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;
	}

	void SetScalar(float scalar) {
		this->w = scalar;
	}

	Quaternion Conjugate()
	{
		return Quaternion(-this->x, -this->y, -this->z, this->w);
	}

	Quaternion Invert() {
		// Only work with Unit quaternion
		return this->Conjugate();
	}

	float LengthSq() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	float Length() const
	{
		return Math::Sqrt(LengthSq());
	}

	Quaternion Normalize() const
	{
		return Quaternion(this->x, this->y, this->z, this->w) / this->Length();
	}

	float Dot(const Quaternion& other) const {
		// Dot product of two unit quaternions varies in range [-1, 1]
		return w * other.w + x * other.x + y * other.y + z * other.z;
	}

	float GetAlpha() {
		return acosf(this->w);
	}

	Quaternion Exp(float exponent) {
		// Avoid divided by zero
		if (fabs(w) < 0.9999f) {
			float alpha = this->GetAlpha();
			// Calculate new w component
			float expAlpha = alpha * exponent;
			float expW = cosf(expAlpha);
			// Calculate new vector component
			float multi = sin(expAlpha) / sin(alpha);
			float expX = this->x * multi;
			float expY = this->y * multi;
			float expZ = this->z * multi;

			return Quaternion(expW, expX, expY, expZ);
		}

		return *this;
	}

	// Return an angular displacement from this quaternion to other quaternion
	Quaternion Difference(const Quaternion& other) {
		return other * this->Invert();
	}

	Vector3 GetVector() const {
		return Vector3(this->x, this->y, this->z);
	}
public:
	// Linear interpolation
	static Quaternion Lerp(const Quaternion& p, const Quaternion& q, float t)
	{
		Quaternion returnQuaternion;
		returnQuaternion.x = Math::Lerp(p.x, q.x, t);
		returnQuaternion.y = Math::Lerp(p.y, q.y, t);
		returnQuaternion.z = Math::Lerp(p.z, q.z, t);
		returnQuaternion.w = Math::Lerp(p.w, q.w, t);
		return returnQuaternion.Normalize();
	}

	// Spherical Linear Interpolation from p to q
	static Quaternion Slerp(const Quaternion& p, const Quaternion& q, float t)
	{
		// Omega is the difference angular displacement between two quaternions
		float cosOmega = p.Dot(q);
		// Negate one of the input quaternion to take the shortest arc in 4D
		Quaternion quaternion = p;
		if (cosOmega < 0.0f) {
			cosOmega = -cosOmega;
			quaternion.w = -p.w;
			quaternion.x = -p.x;
			quaternion.y = -p.y;
			quaternion.z = -p.z;
		}

		float k0, k1;
		// Do simple linear interpolation to avoid divided by zero if omega is very close
		if (cosOmega > 0.999f) {
			k0 = 1 - t;
			k1 = t;
		}
		else {
			float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
			float omega = atan2(sinOmega, cosOmega);
			float oneOverSinOmega = 1.0f / omega;

			k0 = sin(1 - t) * omega * oneOverSinOmega;
			k1 = sin(t) * omega * oneOverSinOmega;
		}

		return quaternion * k0 + q * k1;
	}

	// Concatenate: Rotate by q FOLLOWED BY p
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
	{
		// Vector component:
		Vector3 qv = q.GetVector();
		Vector3 pv = p.GetVector();
		Vector3 vector = p.w * qv + q.w * pv + pv.Cross(qv);

		// Scalar component:
		float scalar = p.w * q.w - pv.Dot(qv);

		return Quaternion(vector.x, vector.y, vector.z, scalar);
	}

	static const Quaternion Identity;
};

namespace Color
{
	static const Vector3 Black(0.0f, 0.0f, 0.0f);
	static const Vector3 White(1.0f, 1.0f, 1.0f);
	static const Vector3 Red(1.0f, 0.0f, 0.0f);
	static const Vector3 Green(0.0f, 1.0f, 0.0f);
	static const Vector3 Blue(0.0f, 0.0f, 1.0f);
	static const Vector3 Yellow(1.0f, 1.0f, 0.0f);
	static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
	static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
	static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
	static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
}
