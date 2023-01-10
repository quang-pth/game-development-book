#pragma once

#include"include/InputSubject.h"
#include"include/InputObserver.h"
#include"include/KeyboardState.h"
#include"include/MouseState.h"
#include"include/ControllerState.h"
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

struct RelativeMouse {
	Vector2 Position;
	std::uint32_t Buttons;
};

class InputSystem : public InputSubject
{
public:
	InputSystem(class Game* game);
	bool Initialize();
	void Shutdown();
	void ProcessEvent(SDL_Event& e);
	void PrepareBeforeUpdate();
	void Update();
	void SetRelativeMouseMode(bool isRelative);
	RelativeMouse GetRelativeMouse() const;
	float Filter1D(float input);
	Vector2 Filter2D(float x, float y);
	Vector2 Filter2D(const Vector2& input);
	const InputState& GetInputState() const { return mState; }
	ButtonState GetMappedButtonState(const std::string& actionName, const ControllerState* controller);
	bool GetMappedButtonValue(const std::string& actionName, const ControllerState* controller);
	ButtonState GetMappedKeyState(const std::string& actionName);
	bool GetMappedKeyValue(const std::string& actionName);
private:
	void UpdateMouse();
	void UpdateKeyboard();
	void UpdateControllers();
	void LowerCaseString(std::string& str);
	bool InitActionMaps(const std::string& filePath);
private:
	InputState mState;
	SDL_GameController* mControllers[MAX_CONTROLLERS];
	class Game* mGame;
	std::unordered_map<std::string, SDL_GameControllerButton> mControllerActionMap;
	std::unordered_map<std::string, SDL_Scancode> mKeyboardActionMap;
};
