#pragma once

#include"include/InputObserver.h"
#include"include/KeyboardState.h"
#include"include/MouseState.h"
#include"include/ControllerState.h"
#include"include/Subject.h"
#include<SDL2/SDL.h>
#include<cstdint>
#include<vector>
#include<unordered_map>

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
	Vector2 GetMouseRelativePosition() const;
	float Filter1D(float input);
	Vector2 Filter2D(float x, float y);
	Vector2 Filter2D(const Vector2& input);
	const InputState& GetInputState() const { return mState; }
	ButtonState GetMappedButtonState(const std::string& actionName, const ControllerState* controller) const;
	ButtonState GetMappedKeyState(const std::string& actionName, const KeyboardState* keyboard) const;
	bool GetMappedKeyValue(const std::string& actionName, const KeyboardState* keyboard) const;
private:
	void UpdateMouse();
	void UpdateKeyboard();
	void UpdateControllers();
	bool InitActionMaps(const std::string& filePath);
private:
	InputState mState;
	SDL_GameController* mControllers[MAX_CONTROLLERS];
	class Game* mGame;
	std::unordered_map<std::string, SDL_GameControllerButton> mControllerActionMap;
	std::unordered_map<std::string, SDL_Scancode> mKeyboardActionMap;
};
