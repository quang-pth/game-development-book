#include "AIAttack.h"
#include "include/AIComponent.h"

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
}

void AIAttack::OnEnter()
{
}

void AIAttack::OnExit()
{
}

const char* AIAttack::GetName() const
{
	return mName;
}
