#pragma once

#include"include/CustomMath.h"
#include<SDL2/SDL.h>
#include <cstdint>

enum ButtonState;

class ControllerState
{
public:
	friend class InputSystem;
public:
	ControllerState();
	bool GetButtonValue(SDL_GameControllerButton button) const;
	ButtonState GetButtonState(SDL_GameControllerButton button) const;
	bool GetIsConnected() const { return mIsConnected; }
	float GetLeftTrigger() const { return mLeftTrigger; }
	float GetRightTrigger() const { return mRightTrigger; }
	const Vector2& GetLeftStick() const { return mLeftStick; }
	const Vector2& GetRightStick() const { return mRightStick; }
	std::uint32_t GetInstanceID() const { return mID; }
	void SetIsUsed(bool isUsed) { mIsConnected = isUsed; }
private:
	Uint32 mCurrentButtons[SDL_CONTROLLER_BUTTON_MAX];
	Uint32 mPreviousButtons[SDL_CONTROLLER_BUTTON_MAX];
	Vector2 mLeftStick, mRightStick;
	float mLeftTrigger, mRightTrigger;
	bool mIsConnected, mIsUsed;
	std::uint32_t mID;
};

