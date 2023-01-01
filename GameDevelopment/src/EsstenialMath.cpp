#include "include/EsstenialMath.h"

namespace EssentialMath {
	Vector3 Vector3::Transform(const Vector3& vector, const Quaternion& quaternion) 
	{
		Quaternion vectorQuaternion = Quaternion(0.0f, vector);
		// Grammann product
		Quaternion concatedQuaternion = quaternion * vectorQuaternion * quaternion.Inverse();

		return concatedQuaternion.GetVector();
	}
}
