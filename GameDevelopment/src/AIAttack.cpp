#include "AIAttack.h"

#include "include/AIComponent.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "include/Enemy.h"

AIAttack::AIAttack(AIComponent* owner) : 
	AIState(owner),
	mName("AIAttack")
{
}

AIAttack::~AIAttack()
{
}

void AIAttack::Update(float deltaTime)
{
	if (mAgent->IsDead()) {
		mOwner->ChangeState("AIDeath");
		return;
	}

	if (!AIState::CanAttack()) {
		mOwner->ChangeState("AIPatrol");
		return;
	}

 	mAgent->ActAsState(deltaTime);
}

void AIAttack::OnEnter()
{
	mAgent->GetMoveComponent()->SetForwardSpeed(0.0f);
}

void AIAttack::OnExit()
{
}

const char* AIAttack::GetName() const
{
	return mName;
}
