#include "include/InputComponent.h"
#include "include/GameObject.h"
#include "include/CustomMath.h"
#include<SDL2/SDL.h>

InputComponent::InputComponent() : 
	MoveComponent(), 
	mMaxForwardSpeed(0.0f), mMaxAngularSpeed(0.0f),
	mForwardKey(), mBackwardKey(), 
	mClockwiseKey(), mCounterClockwiseKey()
{
}

InputComponent::InputComponent(GameObject* owner, int updateOrder) : 
	MoveComponent(owner, updateOrder),
	mMaxForwardSpeed(500.0f), mMaxAngularSpeed(Math::Pi),
	mForwardKey(SDL_SCANCODE_W), mBackwardKey(SDL_SCANCODE_S),
	mClockwiseKey(SDL_SCANCODE_A), mCounterClockwiseKey(SDL_SCANCODE_D)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::ProcessInput(const InputState& inputState)
{
	//// Set movement
	//float forwardSpeed = 0.0f;
	//if (keyState[mForwardKey]) {
	//	forwardSpeed += mMaxForwardSpeed;
	//}
	//if (keyState[mBackwardKey]) {
	//	forwardSpeed -= mMaxForwardSpeed;
	//}
	//MoveComponent::SetForwardSpeed(forwardSpeed);
	//// Set rotation
	//float angularSpeed = 0.0f;
	//if (keyState[mClockwiseKey]) {
	//	angularSpeed -= mMaxAngularSpeed;
	//}
	//if (keyState[mCounterClockwiseKey]) {
	//	angularSpeed += mMaxAngularSpeed;
	//}

	//MoveComponent::SetAngularSpeed(angularSpeed);
}

float InputComponent::GetMaxForwardSpeed() const
{
	return mMaxForwardSpeed;
}

float InputComponent::GetMaxAngularSpeed() const
{
	return mMaxAngularSpeed;
}

bool InputComponent::IsKeyPressed(const uint8_t* keyState)
{
	return keyState[mForwardKey] || keyState[mBackwardKey];
}

void InputComponent::SetMaxForwardSpeed(float speed)
{
	mMaxForwardSpeed = speed;
}

void InputComponent::SetMaxAngularSpeed(float speed)
{
	mMaxAngularSpeed = speed;
}
