#pragma once

#include<include/Component.h>
#include<CustomMath.h>
#include<string>

class TransformComponent : public Component
{
public:
	TransformComponent();
	TransformComponent(class GameObject* owner, int updateOrder, std::string name);
	
	Vector2 GetPosition() const { return mPosition; }
	void FlipPosition();
	void FlipX();
	void FlipY();
	float GetRotation() const { return mRotation; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	void SetPosition(const Vector2& position) { mPosition.x = position.x; mPosition.y = position.y; }
	void SetPosition(float x, float y) { mPosition.x = x; mPosition.y = y; }
	void SetRotation(float rotation) { mRotation = rotation; }
private:
	Vector2 mPosition; // Center point of the gameobject
	float mScale; // Scale factor
	float mRotation; // Rotation angle in radians
};

