#include "AIPatrol.h"

#include "include/AIComponent.h"
#include "include/Enemy.h"

AIPatrol::AIPatrol(AIComponent* owner) : 
	AIState(owner),
	mName("AIPatrol")
{
}

AIPatrol::~AIPatrol()
{
}

void AIPatrol::Update(float deltaTime)
{
	if (AIState::CanAttack()) {
		mOwner->ChangeState("AIAttack");
		return;
	}

	if (mAgent->IsDead()) {
		mOwner->ChangeState("AIDeath");
		return;
	}
	
	mAgent->ActAsState(deltaTime);
}

void AIPatrol::OnEnter()
{
}

void AIPatrol::OnExit()
{
}

const char* AIPatrol::GetName() const
{
	return mName;
}
