#pragma once

#include<cmath>

namespace EssentialMath 
{
	// Unit Quaternion
	class Quaternion
	{
	public:
		float w, x, y, z;
		float mMagnitude;

		Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {
			mMagnitude = this->Magnitude();
		}
		
		Quaternion operator*(Quaternion other) {
			float w = this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z;
			float x = this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y;
			float y = this->w * other.y + this->y * other.w + this->z * other.x - this->x * other.z;
			float z = this->w * other.z + this->z * other.w + this->x * other.y - this->y * other.x;
			
			return Quaternion(w, x, y, z);
		}

		Quaternion Conjungate(Quaternion quaternion) {
			return Quaternion(quaternion.w, -quaternion.x, -quaternion.y, -quaternion.z);
		}

		Quaternion Inverse(Quaternion quaterion) {
			return Conjungate(quaterion);
		}

	private:
		float Magnitude() {
			return sqrtf(w * w + x * x + y * y + z * z);
		}
	};
}


