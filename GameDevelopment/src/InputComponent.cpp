#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/TileMapComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/Mario.h"
#include "include/CustomMath.h"
#include<SDL2/SDL.h>

InputComponent::InputComponent(GameObject* owner, int updateOrder) :
	MoveComponent(owner, updateOrder),
	mMaxForwardSpeed(200.0f),
	mForwardLeftKey(SDL_SCANCODE_A), mForwardRightKey(SDL_SCANCODE_D),
	mState(EMovement::EUnMoveable), mRightKeyIsClicked(false)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update(float deltaTime)
{
	if (mState == EMovement::EMoveable) {
		MoveComponent::Update(deltaTime);
	}
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Set movement
	float forwardSpeed = 0.0f;
	if (keyState[mForwardRightKey]) {
		forwardSpeed += mMaxForwardSpeed;
		mRightKeyIsClicked = true;
	}
	if (keyState[mForwardLeftKey]) {
		forwardSpeed -= mMaxForwardSpeed;
		mRightKeyIsClicked = false;
	}
	MoveComponent::SetForwardSpeed(forwardSpeed);
}

float InputComponent::GetMaxForwardSpeed() const
{
	return mMaxForwardSpeed;
}

void InputComponent::SetMaxForwardSpeed(float speed)
{
	mMaxForwardSpeed = speed;
}

int InputComponent::GetForwardLeftKey() const
{
	return mForwardLeftKey;
}

int InputComponent::GetForwardRightKey() const
{
	return mForwardRightKey;
}

void InputComponent::SetState(EMovement state)
{
	mState = state;
}

EMovement InputComponent::GetState() const
{
	return mState;
}

bool InputComponent::RightKeyIsClicked()
{
	return mRightKeyIsClicked;
}
