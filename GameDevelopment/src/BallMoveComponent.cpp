#include "include/BallMoveComponent.h"
#include "include/Game.h"
#include "include/Collision.h"
#include "include/PhysicWorld.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"

BallMoveComponent::BallMoveComponent(GameObject* owner, int updateOrder, const std::string& name) :
	MoveComponent(owner, updateOrder, name)
{
}

void BallMoveComponent::Update(float deltaTime)
{
	// Treat ball movement as a line segment
	const float segmentLength = 30.0f;
	Vector3 start = mOwner->GetTransform()->GetPosition();
	Vector3 end = start + mOwner->GetForward() * segmentLength;
	LineSegment l;
	l.mStart = start;
	l.mEnd = end;
	CollisionInfo collisionInfo;
	
	PhysicWorld* physicWorld = mOwner->GetGame()->GetPhysicWorld();
	if (physicWorld->SegmentCast(l, collisionInfo)) {
		Vector3 bounceDir = Vector3::Reflect(mOwner->GetForward(), collisionInfo.mNormal);
		mOwner->RotateToNewForward(bounceDir);
	}

	MoveComponent::Update(deltaTime);
}
