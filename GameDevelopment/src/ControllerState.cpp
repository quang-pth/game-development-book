#include "include/ControllerState.h"
#include "include/InputSystem.h"

ControllerState::ControllerState() : 
	mLeftStick(Vector2::Zero), mRightStick(Vector2::Zero),
	mLeftTrigger(0.0f), mRightTrigger(0.0f),
	mIsConnected(false)
{
}

bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
	return mCurrentButtons[button] == 1 ? true : false;
}

ButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const
{
	if (!mPreviousButtons[button]) {
		if (mCurrentButtons[button]) {
			return ButtonState::EPressed;
		}
		else {
			return ButtonState::ENone;
		}
	}
	else {
		if (mCurrentButtons[button]) {
			return ButtonState::EHeld;
		}
		else {
			return ButtonState::EReleased;
		}
	}
}
