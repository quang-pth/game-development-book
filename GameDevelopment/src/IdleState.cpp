#include "IdleState.h"
#include "include/Mario.h"
#include "include/InputComponent.h"
#include "include/AnimatorComponent.h"
#include "include/WalkState.h"
#include "include/JumpState.h"

IdleState::IdleState(Hero* owner) : DamagableState(owner)
{

}

IdleState::~IdleState()
{
}

void IdleState::HandleInput(const uint8_t* keyState)
{
	DamagableState::HandleInput(keyState);

	if (keyState[mOwner->inputComponent->GetInputKey("Jump")]) {
		mOwner->ChangeState("JumpState");
	}

	if (mOwner->IsMoving()) {
		mOwner->ChangeState("WalkState");
	}

}

void IdleState::Update(float deltaTime)
{
}

void IdleState::Enter()
{
	mOwner->animator->SetAnimation("Idle");
}

void IdleState::Exit()
{

}