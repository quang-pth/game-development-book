#include "IdleState.h"
#include "include/Mario.h"
#include "include/InputComponent.h"
#include "include/AnimatorComponent.h"
#include "include/WalkState.h"
#include "include/JumpState.h"

IdleState::~IdleState()
{
}

GameObjectState* IdleState::HandleInput(Hero* mOwner, const uint8_t* keyState)
{
	bool isWalked = keyState[mOwner->inputComponent->GetInputKey("Left")]
		|| keyState[mOwner->inputComponent->GetInputKey("Right")];
	
	if (isWalked) {
		return new WalkState();
	}

	if (keyState[mOwner->inputComponent->GetInputKey("Jump")]) {
		return new JumpState();
	}

    return nullptr;
}

void IdleState::Update(Hero* mOwner)
{
}

void IdleState::Enter(Hero* mOwner)
{
	mOwner->animator->SetAnimation("Idle");
}

void IdleState::Exit()
{
}
