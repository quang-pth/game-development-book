#include "include/ControllerState.h"

ControllerState::ControllerState() : 
	mLeftStick(Vector2::Zero), mRightStick(Vector2::Zero),
	mLeftTrigger(0.0f), mRightTrigger(0.0f),
	mIsConnected(false)
{
}

bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
	return false;
}

ButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const
{
	return ButtonState();
}
