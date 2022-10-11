#pragma once

#include<cmath>

namespace EssentialMath 
{
	class Vector3
	{
	public:
		float x, y, z;

		Vector3() : x(), y(), z() {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		Vector3 operator*(float scalar) {
			return Vector3(x * scalar, y * scalar, z * scalar);
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
}
