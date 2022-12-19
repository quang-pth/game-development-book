#pragma once

#include"include/KeyboardState.h"
#include"include/MouseState.h"
#include"include/ControllerState.h"
#include<SDL2/SDL.h>
#include<cstdint>

enum ButtonState {
	ENone,
	EPressed,
	EReleased,
	EHeld
};

struct InputState {
	KeyboardState KeyBoard;
	MouseState Mouse;
	ControllerState Controller;
};

class InputSystem
{
public:
	InputSystem(class Game* game);
	bool Initialize();
	void Shutdown();
	void ProcessEvent(SDL_Event& e);
	void PrepareBeforeUpdate();
	void Update();
	void SetRelativeMouseMode(bool isRelative);
	float Filter1D(float input);
	Vector2 Filter2D(float x, float y);
	Vector2 Filter2D(const Vector2& input);
	const InputState& GetInputState() const { return mState; }
private:
	InputState mState;
	SDL_GameController* mController;
	class Game* mGame;
};
