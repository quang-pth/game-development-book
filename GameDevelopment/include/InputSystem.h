#pragma once

#include"include/InputObserver.h"
#include"include/KeyboardState.h"
#include"include/MouseState.h"
#include"include/ControllerState.h"
#include"include/Subject.h"
#include<SDL2/SDL.h>
#include<cstdint>
#include<vector>

static const std::uint16_t MAX_CONTROLLERS = 4;

enum ButtonState {
	ENone,
	EPressed,
	EReleased,
	EHeld
};

struct InputState {
	KeyboardState KeyBoard;
	MouseState Mouse;
	ControllerState Controllers[MAX_CONTROLLERS];
};

class InputSystem : public Subject
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
	void UpdateMouse();
	void UpdateControllers();
private:
	InputState mState;
	SDL_GameController* mControllers[MAX_CONTROLLERS];
	class Game* mGame;
};
