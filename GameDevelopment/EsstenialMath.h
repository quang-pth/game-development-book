#pragma once

#include<cmath>
#include<vector>
#include<iostream>

namespace EssentialMath 
{
	class Vector3
	{
	public:
		float x, y, z;
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

		Vector3 operator*(float scalar) {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}
	};

	class Vector2 
	{
	public:
		float x, y;
		Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
		
		Vector2 operator*(float scalar) const {
			return Vector2(x * scalar, y * scalar);
		}
		Vector2 operator-(const Vector2& other) const {
			return Vector2(x - other.x, y - other.y);
		}
		Vector2 operator+(const Vector2& other) const {
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 Normalize() const {
			float length = this->LengthSquared();
			
			if (length < 0.001f) {
				return *this;
			}

			return Vector2(x / length, y / length);
		}

		float Dot(const Vector2& other) {
			Vector2 otherNormalized = other.Normalize();
			Vector2 thisNormalized = this->Normalize();

			return thisNormalized.x * otherNormalized.x + thisNormalized.y * otherNormalized.y;
		}

		float Length() const {
			return x * x + y * y;
		}

		float LengthSquared() const {
			return sqrtf(x * x + y * y);
		}

		static Vector2 GetForwardVector(float angle) {
			// Return a unit forward vector
			return Vector2(cosf(angle), sinf(angle));
		}

	};

	/*
	* Quaternion defines a shortest arc to rotate between two orientations
	*/
	// Unit Quaternion
	class Quaternion
	{
	public:
		float w, x, y, z;
		float magnitude;

		// Directly sets Quaternion components
		Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {
			magnitude = this->Magnitude();
		}

		// Set Quaternion component with an angle and an unit vector
		Quaternion(float theta, Vector3 n) {
			InitQuaternion(theta, n.x, n.y, n.z);
		}
		
		Quaternion operator*(Quaternion other) {
			float w = this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z;
			float x = this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y;
			float y = this->w * other.y + this->y * other.w + this->z * other.x - this->x * other.z;
			float z = this->w * other.z + this->z * other.w + this->x * other.y - this->y * other.x;
			
			return Quaternion(w, x, y, z);
		}
		
		Quaternion operator*(float scalar) {
			return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
		}

		Quaternion operator+(Quaternion other) {
			return Quaternion(this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z);
		}

		float Dot(Quaternion other) {
			// Dot product of two unit quaternions varies in range [-1, 1]
			return w * other.w + x * other.x + y * other.y + z * other.z;
		}

		// Return a quaternion in form of exponential map
		Quaternion Log() {
			Vector3 originalUnitVector = this->GetOriginalUnitVector();
			float alpha = this->GetAlpha();
			float x = originalUnitVector.x * alpha;
			float y = originalUnitVector.y * alpha;
			float z = originalUnitVector.z * alpha;

			return Quaternion(0.0f, x, y, z);
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

		Quaternion Conjungate() {
			return Quaternion(w, -x, -y, -z);
		}

		Quaternion Inverse() {
			// This property only works with Unit Quaternion
			return this->Conjungate();
		}
		
		// Return an angular displacement from this quaternion to other quaternion
		Quaternion Difference(Quaternion other) {
			return other * Inverse();
		}

		Vector3 GetOriginalUnitVector() const {
			float alpha = this->GetAlpha();
			float nx = x / sinf(alpha);
			float ny = y / sinf(alpha);
			float nz = z / sinf(alpha);

			return Vector3(nx, ny, nz);
		}
		
		float GetAlpha() const {
			return acosf(w);
		}

		static Quaternion Identity() {
			return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
		}

		static Quaternion Slerp(Quaternion startQuaterion, Quaternion endQuaternion, float t) {
			// Omega is the difference angular displacement between two quaternions
			float cosOmega = startQuaterion.Dot(endQuaternion);
			// Negate one of the input quaternion to take the shortest arc in 4D
			if (cosOmega < 0.0f) {
				cosOmega = -cosOmega;
				startQuaterion.w = -startQuaterion.w;
				startQuaterion.x = -startQuaterion.x;
				startQuaterion.y = -startQuaterion.y;
				startQuaterion.z = -startQuaterion.z;
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

			return startQuaterion * k0 + endQuaternion * k1;
		}
	private:
		float Magnitude() {
			return sqrtf(w * w + x * x + y * y + z * z);
		}

		void InitQuaternion(float theta, float x, float y, float z) {
			float alpha = theta / 2;
			
			this->w = cosf(alpha);
			this->x = sinf(alpha) * x;
			this->y = sinf(alpha) * y;
			this->z = sinf(alpha) * z;
			
			magnitude = this->Magnitude();
		}
	};

	#define PI 180.0f
	
	class EulerAngle
	{
	public:
		float head, pitch, bank;

		EulerAngle(float head = 0.0, float pitch = 0.0, float bank = 0.0) : 
			head(head), pitch(pitch), bank(bank) {}

		// Wrap theta in range (-180; 180] degrees
		static float WrapPI(float theta) {
			if (fabs(theta) > PI) {
				float resolution = floor((theta + PI) / (2 * PI));
				theta -= 2 * PI * resolution;
			}
			return theta;
		};

		static void ToCanonicalSet(float& head, float& pitch, float& bank)
		{
			// Head [-180, 180)
			// Pitch [-90, 90]
			// Bank [-180, 180)
		}
	};

#define PI 3.14159265
#define DEGREE_TO_RADIAN (PI / 180.0)

	class ConvertHelper {
	public:
		// Convert an Euler Angle representation to Matrix form
		// head, pitch and bank must be measured in object's space 
		static void ObjectToUprightRotationMatrix(const EulerAngle& angle, float matrix[3][3]) {
			float cosHead = cosf(angle.head);
			float sinHead = sinf(angle.head);
			float cosPitch = cosf(angle.pitch);
			float sinPitch = sinf(angle.pitch);
			float cosBank = cosf(angle.bank);
			float sinBank = sinf(angle.bank);
			
			matrix[0][0] = cosHead * cosBank + sinHead * sinPitch * sinBank;
			matrix[0][1] = sinBank * cosPitch;
			matrix[0][2] = -sinHead * cosBank + cosHead * sinPitch * sinBank;
		
			matrix[1][0] = -cosHead * sinBank + sinHead * sinPitch * cosBank;
			matrix[1][1] = cosBank * cosPitch;
			matrix[1][2] = sinBank * sinPitch + cosHead * sinPitch * cosBank;
			
			matrix[2][0] = sinHead * cosPitch;
			matrix[2][1] = -sinPitch;
			matrix[2][2] = cosHead * cosPitch;
		}

		static EulerAngle ObjectToUprightEulerAngle(float matrix[3][3]) {
			float head, pitch, bank;

			float sinPitch = -matrix[2][1];
			if (sinPitch <= -1.0f) {
				pitch = PI / 2;
			}
			else if (sinPitch >= 1.0f) {
				pitch = -PI / 2;
			}
			else {
				pitch = asin(sinPitch);
			}

			// Check for Glimbal lock case when pitch is 90 degree
			if (fabs(sinPitch) > 0.9999f) {
				bank = 0.0f;
				head = atan2(-matrix[0][2], matrix[0][0]);
			}
			else {
				head = atan2(matrix[2][0], matrix[2][2]);
				bank = atan2(matrix[0][1], matrix[1][1]);
			}

			return EulerAngle(head, pitch, bank);
		}
	};
}
