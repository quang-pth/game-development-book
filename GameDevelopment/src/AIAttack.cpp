#include "AIAttack.h"

#include "include/AIComponent.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "include/AnimatorComponent.h"
#include "include/Enemy.h"

AIAttack::AIAttack(AIComponent* owner) : 
	AIDamagable(owner),
	mName("AIAttack"), mRemainingDuration(1.5f)
{
}

AIAttack::~AIAttack()
{
}

void AIAttack::Update(float deltaTime)
{
	AIDamagable::Update(deltaTime);

	mRemainingDuration -= deltaTime;

	if (mAgent->IsDead()) {
		mOwner->ChangeState("AIDeath");
		return;
	}

	mAgent->ActAsState(deltaTime);

	if (mRemainingDuration > 0) return;

	if (!AIState::CanAttack()) {
		mOwner->ChangeState("AIPatrol");
		return;
	}
}

void AIAttack::OnEnter()
{
	mAgent->GetMoveComponent()->SetForwardSpeed(0.0f);
}

void AIAttack::OnExit()
{
	mAgent->SetIsAttacked(false);
	mRemainingDuration = 1.5f;
}

const char* AIAttack::GetName() const
{
	return mName;
}
