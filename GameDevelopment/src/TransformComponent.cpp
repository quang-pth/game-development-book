#include "include/GameObject.h"
#include "include/TransformComponent.h"
#include "include/Component.h"

TransformComponent::TransformComponent() : mPosition(), mRotation(), mScale()
{
}

TransformComponent::TransformComponent(GameObject* owner, int updateOrder, std::string name)
	: Component(owner, updateOrder, name)
{
	mPosition = Vector2(0.0f, 0.0f);
	mRotation = 0.0f;
	mScale = 1.0f;
}

void TransformComponent::FlipPosition()
{
	mPosition = mPosition * (-1);
}

void TransformComponent::FlipX()
{
	mPosition.x = -mPosition.x;
}

void TransformComponent::FlipY()
{
	mPosition.y = -mPosition.y;
}