#include "include/EsstenialMath.h"

namespace EssentialMath {
	/*
	* VECTOR 2
	*/
	Vector2 Vector2::Zero = Vector2(0.0f);
	Vector2 Vector2::Min = Vector2(std::numeric_limits<float>::infinity());
	Vector2 Vector2::Max = Vector2(-std::numeric_limits<float>::infinity());
	/*
	* VECTOR 3
	*/
	Vector3 Vector3::Zero = Vector3(0.0f);
	Vector3 Vector3::Min = Vector3(std::numeric_limits<float>::infinity());
	Vector3 Vector3::Max = Vector3(-std::numeric_limits<float>::infinity());
}