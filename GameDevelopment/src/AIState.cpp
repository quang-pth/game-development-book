#include "AIState.h"

#include "include/Game.h"
#include "include/Enemy.h"
#include "include/Mario.h"
#include "include/AIComponent.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include <iostream>

AIState::AIState(AIComponent* owner) : mOwner(owner)
{
	mAgent = static_cast<Enemy*>(mOwner->GetOwner());
}

AIState::~AIState()
{
}

bool AIState::CanAttack() const
{
	return mAgent->IsNearPlayer() && mAgent->IsSawPlayer();
}
