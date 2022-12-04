#pragma once

#include<include/Component.h>
#include<CustomMath.h>
#include<string>

class TransformComponent : public Component
{
public:
	TransformComponent() = default;
	TransformComponent(class GameObject* owner, int updateOrder, std::string name);
	
	Vector3 GetPosition() const { return mPosition; }
	Quaternion GetRotation() const { return mRotation; }
	const Vector3& GetScale() const { return mScale; }
	Matrix4 GetWorldTransformMatrix() const;
	inline void SetScale(float scaleX, float scaleY, float scaleZ)
	{ 
		mScale.x = scaleX;
		mScale.y = scaleY;
		mScale.z = scaleZ;
		mRecomputeWorldTransform = true; 
	}
	inline void SetScale(const Vector3& scale)
	{ 
		mScale = scale;
		mRecomputeWorldTransform = true; 
	}
	inline void SetScale(float scale) { mScale = Vector3(scale); mRecomputeWorldTransform = true; }
	inline void SetPosition(const Vector3& position) { mPosition = position; mRecomputeWorldTransform = true; };
	inline void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	void ComputeWorldTransform();
private:
	bool mRecomputeWorldTransform;
	Matrix4 mWorldTransform;
	Vector3 mPosition; // Center point of the gameobject
	Vector3 mScale; // Scale factor
	Quaternion mRotation; // Rotation angle in radians
};

