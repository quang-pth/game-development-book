#include "include/Game.h"
#include "include/InputSystem.h"
#include "include/KeyboardState.h"
#include<iostream>

InputSystem::InputSystem(Game* game) : 
	mGame(game), mControllers()
{
}

bool InputSystem::Initialize()
{
	mState.KeyBoard.mCurrentState = SDL_GetKeyboardState(NULL);
	memset(mState.KeyBoard.mPreviousState, 0, SDL_NUM_SCANCODES);
	
	for (std::uint16_t i = 0; i < MAX_CONTROLLERS; i++) {
		memset(mState.Controllers[i].mPreviousButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
		memset(mState.Controllers[i].mCurrentButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
	}

	return true;
}

void InputSystem::Shutdown()
{
	for (std::uint16_t i = 0; i < MAX_CONTROLLERS; i++) {
		SDL_GameControllerClose(mControllers[i]);
	}
}

void InputSystem::ProcessEvent(SDL_Event& e)
{
	std::uint32_t controllerIdx;
	std::uint32_t instanceID;
	switch (e.type)
	{
	case SDL_MOUSEWHEEL:
		mState.Mouse.mScrollWheel = Vector2(
			static_cast<float>(e.wheel.x),
			static_cast<float>(e.wheel.y)
		);
		break;
	case SDL_CONTROLLERDEVICEADDED:
		controllerIdx = e.cdevice.which;
		if (controllerIdx < MAX_CONTROLLERS) {
			mControllers[controllerIdx] = SDL_GameControllerOpen(controllerIdx);
			mState.Controllers[controllerIdx].mID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(mControllers[controllerIdx]));
			mState.Controllers[controllerIdx].mIsConnected = true;
		}
		break;
	case SDL_CONTROLLERDEVICEREMOVED:
		instanceID = e.cdevice.which;
		SDL_GameControllerClose(SDL_GameControllerFromInstanceID(instanceID));
		for (std::uint16_t i = 0; i < MAX_CONTROLLERS; i++) {
			if (mState.Controllers[i].mID == instanceID) {
				mControllers[i] = nullptr;
				mState.Controllers[i].mIsConnected = false;
			}
		}
		break;
	default:
		break;
	}
}

void InputSystem::PrepareBeforeUpdate()
{
	memcpy(mState.KeyBoard.mPreviousState, mState.KeyBoard.mCurrentState, SDL_NUM_SCANCODES);
	
	for (std::uint16_t i = 0; i < MAX_CONTROLLERS; i++) {
		memcpy(mState.Controllers[i].mPreviousButtons, mState.Controllers[i].mCurrentButtons, SDL_CONTROLLER_BUTTON_MAX);
	}

	mState.Mouse.mPreviousButton = mState.Mouse.mCurrentButton;
	mState.Mouse.mScrollWheel = Vector2::Zero; // Reset mouse scrollwheel for new frame
}

void InputSystem::Update()
{
	this->UpdateMouse();
	this->UpdateControllers();
}

void InputSystem::SetRelativeMouseMode(bool isRelative)
{
	SDL_bool mode = isRelative ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(mode);
	mState.Mouse.mIsRelative = isRelative;
}

float InputSystem::Filter1D(float input)
{
	const std::uint32_t deadZone = 300.0f;
	const std::uint32_t maxValue = 30'000.0f;
	float returnValue = 0.0f;
	float absValue = std::abs(static_cast<float>(input));

	if (absValue > deadZone) {
		returnValue = static_cast<float>(absValue - deadZone) / (maxValue - deadZone);
		returnValue = input > 0 ? returnValue : returnValue * (-1.0f);

		returnValue = Math::Clamp(returnValue, -1.0f, 1.0f);
	}

	return returnValue;
}

Vector2 InputSystem::Filter2D(float x, float y)
{
	float deadZone = 8000.0f;
	float maxValue = 30'000.0f;

	Vector2 direction(x, y);
	float length = direction.Length();
	
	if (length < deadZone) {
		direction = Vector2::Zero;
	}
	else {
		float fraction = (length - deadZone) / (maxValue - deadZone);
		fraction = Math::Clamp(fraction, 0.0f, 1.0f);
		direction = (direction / length) * fraction;
	}

	return direction;
}

Vector2 InputSystem::Filter2D(const Vector2& input)
{
	return this->Filter2D(input.x, input.y);
}

void InputSystem::UpdateMouse()
{
	int x = 0, y = 0;
	if (mState.Mouse.mIsRelative) {
		mState.Mouse.mCurrentButton = SDL_GetRelativeMouseState(&x, &y);
	}
	else {
		mState.Mouse.mCurrentButton = SDL_GetMouseState(&x, &y);
		// Convert coords from SDL to OpenGL
		x = x - mGame->GetWindowWidth() / 2;
		y = mGame->GetWindowHeight() / 2 - y;
	}
	mState.Mouse.mCurrentPosition.x = static_cast<float>(x);
	mState.Mouse.mCurrentPosition.y = static_cast<float>(y);
}

void InputSystem::UpdateControllers()
{
	for (std::uint16_t controllerIdx = 0; controllerIdx < MAX_CONTROLLERS; controllerIdx++) {
		if (!mState.Controllers[controllerIdx].mIsConnected) continue;
		
		SDL_GameController* controller = mControllers[controllerIdx];
		// Controller buttons
		for (std::uint8_t buttonIdx = 0; buttonIdx < SDL_CONTROLLER_BUTTON_MAX; buttonIdx++) {
			mState.Controllers[controllerIdx].mCurrentButtons[buttonIdx] = SDL_GameControllerGetButton(controller,
				SDL_GameControllerButton(buttonIdx));
		}
		// Triggers
		mState.Controllers[controllerIdx].mLeftTrigger = this->Filter1D(SDL_GameControllerGetAxis(controller,
			SDL_CONTROLLER_AXIS_TRIGGERLEFT));
		mState.Controllers[controllerIdx].mRightTrigger = this->Filter1D(SDL_GameControllerGetAxis(controller,
			SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
		// Left stick
		float leftX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		float leftY = -SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
		mState.Controllers[controllerIdx].mLeftStick = this->Filter2D(leftX, leftY);
		// Right Stick
		float rightX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
		float rightY = -SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
		mState.Controllers[controllerIdx].mRightStick = this->Filter2D(rightX, rightY);
	}
}
