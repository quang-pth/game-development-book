#include "NavComponent.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"

NavComponent::NavComponent(GameObject* owner, int updateOrder, const std::string& name) :
	MoveComponent(owner, updateOrder, name),
	mNextPoint(Vector2::Zero)
{
}

NavComponent::~NavComponent()
{
}

void NavComponent::Update(float deltaTime)
{
	Vector2 distance = mOwner->GetTransform()->GetPosition() - mNextPoint;
	if (distance.Length() <= 3.0f) {
		mNextPoint = this->GetNextPoint();
		this->TurnTo(mNextPoint);
	}
	MoveComponent::Update(deltaTime);
}

void NavComponent::TurnTo(const Vector2& nextPoint)
{
	Vector2 distance = mOwner->GetTransform()->GetPosition() - nextPoint;
	float angle = Math::Atan2(-distance.y, distance.x);
	mOwner->GetTransform()->SetRotation(angle);
}

Vector2& NavComponent::GetNextPoint() const
{
	Vector2 nextPoint = Vector2::Zero;
	return nextPoint;
}
