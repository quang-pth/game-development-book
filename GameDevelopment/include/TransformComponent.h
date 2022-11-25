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
	float GetRotation() const { return mRotation; }
	float GetScale() const { return mScale; }
	Matrix4 GetWorldTransformMatrix() const;
	inline void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	inline void SetPosition(const Vector3& position) { mPosition = position; mRecomputeWorldTransform = true; };
	inline void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	void ComputeWorldTransform();
private:
	bool mRecomputeWorldTransform;
	Matrix4 mWorldTransform;
	Vector3 mPosition; // Center point of the gameobject
	float mScale; // Scale factor
	float mRotation; // Rotation angle in radians
};

