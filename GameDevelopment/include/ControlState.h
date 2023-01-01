#pragma once

#include<vector>

class InputComponent;
struct InputState;

class ControlState
{
public:
	enum class State {
		EController,
		EKeyboard,
	};

	virtual ~ControlState() = default;
public:
	virtual void OnEnter(InputComponent* inputComponent) = 0;
	virtual void OnUpdate(InputComponent* owner, float deltaTime) = 0;
	virtual void OnProcessInput(InputComponent* inputComponent, const InputState& state) = 0;
	virtual void OnExit(InputComponent* inputComponent) = 0;
	virtual State GetEnumState() const = 0;
};
