#include "include/JumpState.h"
#include "include/WalkState.h"
#include "include/Mario.h"
#include "include/AnimatorComponent.h"
#include "include/InputComponent.h"

JumpState::~JumpState()
{
}

GameObjectState* JumpState::HandleInput(Hero* mOwner, const uint8_t* keyState)
{
	bool isWalked = keyState[mOwner->inputComponent->GetInputKey("Left")]
		|| keyState[mOwner->inputComponent->GetInputKey("Right")];

	if (isWalked) {
		return new WalkState();
	}

    return nullptr;
}

void JumpState::Update(Hero* mOwner)
{
}

void JumpState::Enter(Hero* mOwner)
{
    mOwner->animator->SetAnimation("Jump");
}

void JumpState::Exit()
{
}
