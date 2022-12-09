#include "include/KeyboardState.h"
#include "include/InputSystem.h"

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return mCurrentState[keyCode];
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (!mPreviousState[keyCode]) 
	{
		if (mCurrentState[keyCode]) {
			return ButtonState::EPressed;
		}
		else {
			return ButtonState::ENone;
		}
	}
	else {
		if (!mCurrentState[keyCode]) {
			return ButtonState::EReleased;
		}
		else {
			return ButtonState::EHeld;
		}
	}
}
