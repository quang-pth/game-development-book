#include "include/MouseState.h"
#include"include/InputSystem.h"

MouseState::MouseState() : 
	mCurrentPosition(Vector2::Zero),
	mScrollWheel(Vector2::Zero),
	mCurrentButtons(),
	mPreviousButtons(),
	mIsRelative(false)
{
}

bool MouseState::GetButtonValue(unsigned int button) const
{
	int x = 0, y = 0;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	return buttons & SDL_BUTTON(button);
}

ButtonState MouseState::GetButtonState(unsigned int button) const
{
	if (!(mPreviousButtons & SDL_BUTTON(button))) {
		if (mCurrentButtons & SDL_BUTTON(button)) {
			return ButtonState::EPressed;
		} 
		else {
			return ButtonState::ENone;
		}
	}
	else {
		if (mCurrentButtons & SDL_BUTTON(button)) {
			return ButtonState::EHeld;
		}
		else {
			return ButtonState::EReleased;
		}
	}
}
