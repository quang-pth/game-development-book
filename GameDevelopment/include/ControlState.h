#pragma once

#include<vector>
#include<string>

class InputComponent;
struct InputState;
enum ButtonState;

class ControlState
{
public:
	enum class State {
		EController,
		EKeyboard,
	};
	virtual ~ControlState() = default;
	virtual void OnEnter(InputComponent* inputComponent) = 0;
	virtual void OnUpdate(InputComponent* owner, float deltaTime) = 0;
	virtual void OnProcessInput(InputComponent* inputComponent, const InputState& state) = 0;
	virtual void OnExit(InputComponent* inputComponent) = 0;
	virtual ButtonState GetMappedState(InputComponent* owner, const std::string& actionName) = 0;
	virtual bool GetMappedValue(InputComponent* owner, const std::string& actionName) = 0;
	virtual State GetEnumState() const = 0;
	virtual bool IsMoving() const = 0;
};
