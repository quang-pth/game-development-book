#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/TileMapComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/Mario.h"
#include "include/CustomMath.h"
#include<SDL2/SDL.h>

InputComponent::InputComponent() : 
	MoveComponent(), 
	mMaxForwardSpeed(0.0f),
	mForwardLeftKey(), mForwardRightKey(), mState()
{
}

InputComponent::InputComponent(GameObject* owner, int updateOrder) : 
	MoveComponent(owner, updateOrder),
	mMaxForwardSpeed(200.0f),
	mForwardLeftKey(SDL_SCANCODE_A), mForwardRightKey(SDL_SCANCODE_D),
	mState(State::EUnMoveable)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update(float deltaTime)
{
	if (mState == State::EMoveable) {
		MoveComponent::Update(deltaTime);

		if (mOwner->GetTransform()->GetPosition().x > mOwner->GetGame()->GetCenterPoint().x
			|| mOwner->GetTransform()->GetPosition().x < mOwner->GetGame()->GetCenterPoint().x
		) {
			mState = State::EUnMoveable;
		}
	}
	else if (mState == State::EUnMoveable) {
		if (mOwner->GetGame()->GetTileMapComponent()->GetState() ==
			TileMapComponent::State::EUnMoveable) {
			mState = State::EMoveable;
		}
		else if (mOwner->GetGame()->GetTileMapComponent()->GetState() ==
			TileMapComponent::State::EMoveable) {
			mState = State::EUnMoveable;
		}
	}
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Set movement
	float forwardSpeed = 0.0f;
	if (keyState[mForwardRightKey]) {
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mForwardLeftKey]) {
		forwardSpeed -= mMaxForwardSpeed;
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

void InputComponent::SetState(State state)
{
	mState = state;
}

InputComponent::State InputComponent::GetState() const
{
	return mState;
}
