#include "DeathState.h"
#include "include/Mario.h"
#include "include/AnimatorComponent.h"

DeathState::DeathState(Hero* owner) : 
	GameObjectState(owner),
	mDuration(1.0f)
{

}

DeathState::~DeathState()
{
}

void DeathState::HandleInput(const uint8_t* keyState)
{
	if (mDuration > 0.0f) return;

	mOwner->Deactivate();
}

void DeathState::Update(float deltaTime)
{
	mDuration -= deltaTime;
}

void DeathState::Enter()
{
	mOwner->animator->SetAnimation("Hurt");
}

void DeathState::Exit()
{
}
