#include "AIState.h"

#include "include/Game.h"
#include "include/Enemy.h"
#include "include/Mario.h"
#include "include/AIComponent.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"

AIState::AIState(AIComponent* owner) : mOwner(owner)
{
	mAgent = static_cast<Enemy*>(mOwner->GetOwner());
}

AIState::~AIState()
{
}

bool AIState::CanAttack() const
{
	const Vector2& distanceVector = mAgent->pTransform->GetPosition() - mAgent->GetGame()->GetHero()->pTransform->GetPosition();
	bool isNear = std::abs(distanceVector.x) < mAgent->GetAttackRadius() && 
		std::abs(distanceVector.y) < 5.0f;
	//const Vector2& velocity = mAgent->GetMoveComponent()->GetVelocity().Normalize();
	//const Vector2& playerPos = mAgent->GetGame()->GetHero()->pTransform->GetPosition().Normalize();
	//bool canSeeHero = Vector2::Dot(velocity, playerPos) <= 0.0f;

	//if (canSeeHero) {
	//	// 
	//}

	return isNear;
}
