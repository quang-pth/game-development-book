#pragma once

#include "include/InputObserver.h"
#include "include/MoveComponent.h"
#include "include/InputSystem.h"
#include"include/ControlState.h"
#include<SDL2/SDL.h>
#include<unordered_map>
#include<memory>

class InputComponent : public MoveComponent, InputObserver
{
	friend class KeyboardControlState;
	friend class ControllerControlState;
public:
	InputComponent(class GameObject* owner, int updateOrder = 4);
	~InputComponent();
	virtual void Update(float deltaTime) override;
	virtual void OnControllerInputHandler(ControllerState* controller, InputObserver::Event inputEvent) override;
	virtual void ProcessInput(const InputState& inputState) override;
	ControllerState* GetController() const { return mController; }
	bool IsMoving() const;
	ButtonState GetMappedActionState(const std::string& actionName);
	bool GetMappedActionValue(const std::string& actionName);
private:
	void ChangeState(ControlState::State state);
private:
	ControllerState* mController;
	std::shared_ptr<ControlState> mCurrentState;
	std::unordered_map<ControlState::State, std::shared_ptr<ControlState>> mStates;
};