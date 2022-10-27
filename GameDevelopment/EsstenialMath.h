#pragma once

#include<cmath>
#include<vector>
#include<iostream>

namespace EssentialMath
{
#define PI 3.14159265
#define DEGREE_TO_RADIAN (PI / 180.0)
#define RADIAN_TO_DEGREE (180.0 / PI)

	class Vector3
	{
	public:
		float x, y, z;

		Vector3() : x(), y(), z() {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		Vector3 operator*(float scalar) {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		Vector3 Normalize() {
			float magnitude = this->Magnitude();

			return Vector3(x / magnitude, y / magnitude, z / magnitude);
		}

		float Magnitude() {
			return sqrtf(x * x + y * y + z * z);
		}

		float MagnitudeSquared() {
			return x * x + y * y + z * z;
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
		Quaternion(float theta, const Vector3& n) {
			InitQuaternion(theta, n.x, n.y, n.z);
		}
		
		Quaternion operator*(const Quaternion& other) {
			float w = this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z;
			float x = this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y;
			float y = this->w * other.y + this->y * other.w + this->z * other.x - this->x * other.z;
			float z = this->w * other.z + this->z * other.w + this->x * other.y - this->y * other.x;
			
			return Quaternion(w, x, y, z);
		}
		
		Quaternion operator*(float scalar) const {
			return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
		}

		Quaternion operator+(const Quaternion& other) {
			return Quaternion(this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z);
		}

		float Dot(const Quaternion& other) const {
			// Dot product of two unit quaternions varies in range [-1, 1]
			return w * other.w + x * other.x + y * other.y + z * other.z;
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

		Quaternion Conjungate() const {
			return Quaternion(w, -x, -y, -z);
		}

		Quaternion Inverse() const {
			// This property only works with Unit Quaternion
			return this->Conjungate();
		}
		
		// Return an angular displacement from this quaternion to other quaternion
		Quaternion Difference(const Quaternion& other) {
			return this->Inverse() * other;
		}
		
		float GetAlpha() const {
			return acosf(w);
		}

		static Quaternion Identity() {
			return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
		}

		static Quaternion Slerp(const Quaternion& startQuaterion, const Quaternion& endQuaternion, float t) {
			// Omega is the difference angular displacement between two quaternions
			float cosOmega = startQuaterion.Dot(endQuaternion);
			// Negate one of the input quaternion to take the shortest arc in 4D
			Quaternion quaternion = startQuaterion;
			if (cosOmega < 0.0f) {
				cosOmega = -cosOmega;
				quaternion.w = -startQuaterion.w;
				quaternion.x = -startQuaterion.x;
				quaternion.y = -startQuaterion.y;
				quaternion.z = -startQuaterion.z;
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

			return quaternion * k0 + endQuaternion * k1;
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

	class EulerAngle
	{
	public:
		float head, pitch, bank;

		EulerAngle(float head, float pitch, float bank) : 
			head(head), pitch(pitch), bank(bank) 
		{
		}

		EulerAngle(float angle) : head(angle), pitch(angle), bank(angle) 
		{
		}

		// Wrap theta in range (-180; 180] degrees
		static float WrapPI(float theta) {
			if (fabs(theta) > PI) {
				float resolution = floor((theta + PI) / (2 * PI));
				theta -= 2 * PI * resolution;
			}
			return theta;
		};
	};

	class RepresentationConverter {
	public:
		// Convert an Euler Angle to a Matrix
		// head, pitch and bank must be mesured in object's space 
		static void EulerAngleToObjectToUpRightMatrix(const EulerAngle& angle, float matrix[3][3]) {
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

		// Convert an Object-To-Upright Matrix to an Euler Angle
		static EulerAngle MatrixToEulerAngle(float matrix[3][3]) {
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

		// Convert a Unit Quaternion to a Matrix
		static void QuaternionToMatrix(const Quaternion& quaternion, float matrix[3][3]) {
			matrix[0][0] = 1 - 2 * std::pow(quaternion.y, 2) - 2 * std::pow(quaternion.z, 2);
			matrix[0][1] = 2 * quaternion.x * quaternion.y + 2 * quaternion.w * quaternion.z;
			matrix[0][2] = 2 * quaternion.x * quaternion.z - 2 * quaternion.w * quaternion.y;

			matrix[1][0] = 2 * quaternion.x * quaternion.y - 2 * quaternion.w * quaternion.z;
			matrix[1][1] = 1 - 2 * std::pow(quaternion.x, 2) - 2 * std::pow(quaternion.z, 2);
			matrix[1][2] = 2 * quaternion.y * quaternion.z + 2 * quaternion.w * quaternion.x;

			matrix[2][0] = 2 * quaternion.x * quaternion.z + 2 * quaternion.w * quaternion.y;
			matrix[2][1] = 2 * quaternion.y * quaternion.z - 2 * quaternion.w * quaternion.x;
			matrix[2][2] = 1 - 2 * std::pow(quaternion.x, 2) - 2 * std::pow(quaternion.y, 2);
		}

		// Convert a Matrix to an Unit Quaternion
		static Quaternion MatrixToQuaternion(float matrix[3][3]) {
			float w = std::sqrtf(matrix[0][0] + matrix[1][1] + matrix[2][2] + 1) / 2;
			float x = std::sqrtf(matrix[0][0] - matrix[1][1] - matrix[2][2] + 1) / 2;
			float y = std::sqrtf(-matrix[0][0] + matrix[1][1] - matrix[2][2] + 1) / 2;
			float z = std::sqrtf(-matrix[0][0] - matrix[1][1] + matrix[2][2] + 1) / 2;
			float temp[] = { w, x, y, z };

			float maxValue = w;
			for (unsigned int i = 0; i < 4; i++) {
				if (temp[i] > maxValue) {
					maxValue = temp[i];
				}
			}

			float delimeter = 4 * maxValue;
			if (maxValue == w) {
				x = (matrix[1][2] - matrix[2][1]) / delimeter;
				y = (matrix[2][0] - matrix[0][2]) / delimeter;
				z = (matrix[0][1] - matrix[1][0]) / delimeter;
			}
			else if (maxValue == x) {
				w = (matrix[1][2] - matrix[2][1]) / delimeter;
				y = (matrix[0][1] + matrix[1][0]) / delimeter;
				z = (matrix[2][0] + matrix[0][2]) / delimeter;
			}
			else if (maxValue == y) {
				w = (matrix[2][0] - matrix[0][2]) / delimeter;
				x = (matrix[0][1] + matrix[1][0]) / delimeter;
				z = (matrix[1][2] + matrix[2][1]) / delimeter;
			}
			else {
				w = (matrix[0][1] - matrix[1][0]) / delimeter;
				x = (matrix[2][0] + matrix[0][2]) / delimeter;
				y = (matrix[1][2] + matrix[2][1]) / delimeter;
			}

			return { w, x, y , z };
		}

		// Convert an Euler Angle to an unit Object-To-UpRight Quaternion
		static Quaternion EulerAngleToObjectToUpRightQuaternion(const EulerAngle& angle, bool objToUpRight = true) {
			Quaternion head = Quaternion(cosf(angle.head * 0.5f), 0.0f, sinf(angle.head * 0.5f), 0.0f);
			Quaternion pitch = Quaternion(cosf(angle.pitch * 0.5f), sinf(angle.pitch * 0.5f), 0.0f, 0.0f);
			Quaternion bank = Quaternion(cosf(angle.bank * 0.5f), 0.0f, 0.0f, sinf(angle.bank * 0.5f));

			if (objToUpRight) {
				return head * pitch * bank;
			}

			return (head * pitch * bank).Conjungate();
		}

		// Convert an Unit Quaternion to an Euler Angle
		static EulerAngle QuaternionToEulerAngle(const Quaternion& quaternion, bool objToUpright = true) {
			float w, x, y, z;
			w = quaternion.w;

			if (objToUpright) {
				x = quaternion.x;
				y = quaternion.y;
				z = quaternion.z;
			}
			else {
				x = -quaternion.x;
				y = -quaternion.y;
				z = -quaternion.z;
			}
		
			float head, pitch, bank;
			float sinPitch = -2 * (y * z - w * x);
			// Avoid Glimbal lock
			if (abs(sinPitch) > 0.9999f) {
				pitch = (PI / 2) * sinPitch; // Look straight up or down
				head = atan2(-x * z + w * y, 0.5 - y * y - z * z);
				bank = 0;
			}
			else {
				pitch = asinf(sinPitch);
				head = atan2(x * z + w * y, 0.5 - x * x - y * y);
				bank = atan2(x * y + w * z, 0.5 - x * x - z * z);
			}

			return { head, pitch, bank };
		}
	};
}