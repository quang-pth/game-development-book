#include "AIPatrol.h"

#include "include/AIComponent.h"
#include "include/AnimatorComponent.h"
#include "include/Enemy.h"

AIPatrol::AIPatrol(AIComponent* owner) : 
	AIDamagable(owner),
	mName("AIPatrol")
{
}

AIPatrol::~AIPatrol()
{
}

void AIPatrol::Update(float deltaTime)
{
	AIDamagable::Update(deltaTime);

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
	mAgent->GetAnimatorComponent()->SetAnimation("Running");
}

void AIPatrol::OnExit()
{
}

const char* AIPatrol::GetName() const
{
	return mName;
}
