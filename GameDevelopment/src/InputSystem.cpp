#include "include/Game.h"
#include "include/InputSystem.h"
#include "include/KeyboardState.h"
#include<iostream>

InputSystem::InputSystem(Game* game) : mGame(game)
{
}

bool InputSystem::Initialize()
{
	mState.KeyBoard.mCurrentState = SDL_GetKeyboardState(NULL);
	memset(mState.KeyBoard.mPreviousState, 0, SDL_NUM_SCANCODES);
	
	return true;
}

void InputSystem::Shutdown()
{
}

void InputSystem::ProcessEvent(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_MOUSEWHEEL:
		mState.Mouse.mScrollWheel = Vector2(
			static_cast<float>(e.wheel.x),
			static_cast<float>(e.wheel.y)
		);
		break;
	default:
		break;
	}
}

void InputSystem::PrepareBeforeUpdate()
{
	memcpy(mState.KeyBoard.mPreviousState, mState.KeyBoard.mCurrentState, SDL_NUM_SCANCODES);

	mState.Mouse.mPreviousButtons = mState.Mouse.mCurrentButtons;
	mState.Mouse.mScrollWheel = Vector2::Zero; // Reset mouse scrollwheel for new frame
}

void InputSystem::Update()
{
	int x = 0, y = 0;
	if (mState.Mouse.mIsRelative) {
		mState.Mouse.mCurrentButtons = SDL_GetRelativeMouseState(&x, &y);
	}
	else {
		mState.Mouse.mCurrentButtons = SDL_GetMouseState(&x, &y);
		// Convert coords from SDL to OpenGL
		x = x - mGame->GetWindowWidth() / 2;
		y = mGame->GetWindowHeight() / 2 - y;
	}
	mState.Mouse.mCurrentPosition.x = static_cast<float>(x);
	mState.Mouse.mCurrentPosition.y = static_cast<float>(y);
}

void InputSystem::SetRelativeMouseMode(bool isRelative)
{
	SDL_bool mode = isRelative ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(mode);
	mState.Mouse.mIsRelative = isRelative;
}
