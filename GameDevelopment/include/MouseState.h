#pragma once

#include<SDL2/SDL.h>
#include"include/CustomMath.h"

class InputSystem;
enum ButtonState;

class MouseState
{
public:
	friend InputSystem;
public:
	MouseState();
	const Vector2& GetPosition() const { return mCurrentPosition; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool GetButtonValue(unsigned int button) const;
	ButtonState GetButtonState(unsigned int button) const;
private:
	Vector2 mCurrentPosition;
	Vector2 mScrollWheel;
	Uint32 mCurrentButtons;
	Uint32 mPreviousButtons;
	bool mIsRelative;
};

