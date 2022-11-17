#include "AIState.h"

#include "include/Enemy.h"
#include "include/AIComponent.h"

AIState::AIState(AIComponent* owner) : mOwner(owner)
{
	mActor = (Enemy*)mOwner->GetOwner();
}

AIState::~AIState()
{
}
