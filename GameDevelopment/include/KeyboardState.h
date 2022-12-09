#pragma once

#include<SDL2/SDL.h>

enum ButtonState;

class KeyboardState
{
public:
	KeyboardState() = default;
	friend class InputSystem;
	bool GetKeyValue(SDL_Scancode keyCode) const;
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	const Uint8* mCurrentState;
	Uint8 mPreviousState[SDL_NUM_SCANCODES];
};