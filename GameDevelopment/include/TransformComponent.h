#pragma once

#include<include/Component.h>
#include<CustomMath.h>
#include<string>

class TransformComponent : public Component
{
public:
	Vector2 mPosition; // Center point of the gameobject
	float mScale; // Scale factor
	float mRotation; // Rotation angle in radians
	
	TransformComponent();
	TransformComponent(class GameObject* owner, int updateOrder, std::string name);
	
	void SetScale(float scale) { mScale = scale; }
	void SetPosition(const Vector2& position) { mPosition.x = position.x; mPosition.y = position.y; }
	void SetRotation(float rotation) { mRotation = rotation; }
};

