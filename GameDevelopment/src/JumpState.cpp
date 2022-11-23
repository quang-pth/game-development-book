#include "include/JumpState.h"
#include "include/WalkState.h"
#include "include/Mario.h"
#include "include/AnimatorComponent.h"
#include "include/InputComponent.h"
#include "include/RigidBodyComponent.h"

JumpState::JumpState(Hero* owner) : 
	DamagableState(owner),
	mMaxHeight(15.0f), mMaxTime(2.0f)
{
	float timeToApex = mMaxTime / 2.0f;
	mForce = (2 * mMaxHeight) / timeToApex;
}

JumpState::~JumpState()
{
}

void JumpState::HandleInput(const uint8_t* keyState)
{
	DamagableState::HandleInput(keyState);

	// TODO: CHECK IS GROUNDED

	bool isWalked = keyState[mOwner->inputComponent->GetInputKey("Left")]
		|| keyState[mOwner->inputComponent->GetInputKey("Right")];

	if (isWalked) {
		mOwner->ChangeState("WalkState");
	}

	if (mOwner->animator->IsFinishedAnimation()) {
		mOwner->ChangeState("IdleState");
	}
}

void JumpState::Update(float deltaTime)
{
}

void JumpState::Enter()
{
	mOwner->animator->SetAnimation("Jump");
	mOwner->rigidBodyComponent->Jump(mForce);
}

void JumpState::Exit() 
{

}