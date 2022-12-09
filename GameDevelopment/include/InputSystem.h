#pragma once

#include"include/KeyboardState.h"
#include"include/MouseState.h"

enum ButtonState {
	ENone,
	EPressed,
	EReleased,
	EHeld
};

struct InputState {
	KeyboardState KeyBoard;
	MouseState Mouse;
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
	const InputState& GetInputState() const { return mState; }
private:
	InputState mState;
	class Game* mGame;
};
