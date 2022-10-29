#include "include/GameObject.h"
#include "include/CircleComponent.h"
#include "include/TransformComponent.h"

CircleComponent::CircleComponent() : Component(), mRadius()
{
}

CircleComponent::CircleComponent(GameObject* owner, int updateOrder) :
	Component(owner, updateOrder, "CircleComponent"),
	mRadius(10.0f)
{

}

const Vector2& CircleComponent::GetCenter() const
{
	return mOwner->pTransform->GetPosition();
}

float CircleComponent::GetRadius() const
{
	return mRadius;
}

void CircleComponent::SetRadius(float radius)
{
	mRadius = radius;
}

bool CircleComponent::IsIntersect(const CircleComponent* circle1, const CircleComponent* circle2)
{
	Vector2 center1 = circle1->GetCenter();
	Vector2 center2 = circle2->GetCenter();
	Vector2 centerDistanceVector = center1 - center2;
	float centerDistance = centerDistanceVector.LengthSquared();
	float radiusDistance = std::pow(circle1->GetRadius() + circle2->GetRadius(), 2);

	return centerDistance <= radiusDistance;
}
