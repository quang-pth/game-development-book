#include "include/ControllerState.h"

ControllerState::ControllerState() : mIsConnected(false)
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
