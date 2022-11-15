#include "AIDeath.h"
#include "include/AIComponent.h"

AIDeath::AIDeath(AIComponent* owner) : 
	AIState(owner),
	mName("AIDeath")
{
}

AIDeath::~AIDeath()
{
}

void AIDeath::Update(float deltaTime)
{
}

void AIDeath::OnEnter()
{
}

void AIDeath::OnExit()
{
}

const char* AIDeath::GetName() const
{
	return mName;
}
