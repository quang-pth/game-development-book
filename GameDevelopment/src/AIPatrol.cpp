#include "AIPatrol.h"
#include "include/AIComponent.h"

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
	/*bool iAmDead = 1 > 0;
	if (iAmDead) {
		mOwner->ChangeState("AIDeath");
	}*/
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
