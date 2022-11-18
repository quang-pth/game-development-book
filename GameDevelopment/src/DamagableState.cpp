#include "DamagableState.h"
#include "include/Mario.h"

DamagableState::DamagableState(Hero* owner) : GameObjectState(owner)
{
}

DamagableState::~DamagableState()
{
}

void DamagableState::HandleInput(const uint8_t* keyState)
{
	if (mOwner->IsAttacked()) {
		mOwner->ChangeState("HurtState");
	}
}

void DamagableState::Update(float deltaTime)
{
}

void DamagableState::Enter()
{
}

void DamagableState::Exit()
{
}
