#include "include/InputComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/Mario.h"
#include "include/CustomMath.h"
#include<SDL2/SDL.h>

InputComponent::InputComponent() : 
	MoveComponent(), 
	mMaxForwardSpeed(0.0f),
	mForwardLeftKey(), mForwardRightKey()
{
}

InputComponent::InputComponent(GameObject* owner, int updateOrder) : 
	MoveComponent(owner, updateOrder),
	mMaxForwardSpeed(500.0f),
	mForwardLeftKey(SDL_SCANCODE_A), 
	mForwardRightKey(SDL_SCANCODE_D)
{
}

InputComponent::~InputComponent()
{
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
