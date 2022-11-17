#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/RigidBodyComponent.h"
#include "include/TileMap.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/Mario.h"
#include "include/Unit.h"
#include "include/CustomMath.h"
#include<SDL2/SDL.h>

InputComponent::InputComponent(GameObject* owner, int updateOrder) :
	MoveComponent(owner, updateOrder),
	mMaxForwardSpeed(200.0f),
	mForwardLeftKey(SDL_SCANCODE_A), 
	mForwardRightKey(SDL_SCANCODE_D), mJumpKey(SDL_SCANCODE_SPACE), mFireKey(SDL_SCANCODE_P),
	mState(EMovement::EMoveable), mRightKeyIsClicked(false)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update(float deltaTime)
{
	MoveComponent::Update(deltaTime);
	Hero* hero = (Hero*)mOwner;
	if (hero != nullptr) {
		Vector2 velocity = MoveComponent::GetVelocity();
		velocity.y = 0.0f;
		hero->rigidBodyComponent->Move(velocity * deltaTime);
	}
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	if (keyState[mForwardRightKey]) {
		forwardSpeed += mMaxForwardSpeed;
		mRightKeyIsClicked = true;
		((Hero*)mOwner)->SetDirection(Direction::Right);
	}
	if (keyState[mForwardLeftKey]) {
		forwardSpeed -= mMaxForwardSpeed;
		mRightKeyIsClicked = false;
		((Hero*)mOwner)->SetDirection(Direction::Left);
	}
	MoveComponent::SetForwardSpeed(forwardSpeed);

	if (keyState[mFireKey]) {
		((Hero*)mOwner)->Fire();
	}
}

float InputComponent::GetMaxForwardSpeed() const
{
	return mMaxForwardSpeed;
}

void InputComponent::SetMaxForwardSpeed(float speed)
{
	mMaxForwardSpeed = speed;
}

int InputComponent::GetInputKey(const std::string& keyName) const
{
	if (keyName == "Left") {
		return mForwardLeftKey;
	}
	else if (keyName == "Right") {
		return mForwardRightKey;
	}
	else if (keyName == "Jump") {
		return mJumpKey;
	}
	return -1;
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
