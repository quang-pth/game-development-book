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
public:
	ControllerState* GetController() const { return mController; }
	bool IsMoving() const;
public:
	virtual void Update(float deltaTime) override;
	void ProcessInput(const InputState& inputState) override;
	void ChangeState(ControlState::State state);
	virtual void OnControllerInputHandler(ControllerState* controller, InputObserver::Event inputEvent) override;
private:
	Vector3 GetMoveDirectionFromController() const;
private:
	ControllerState* mController;
	std::shared_ptr<ControlState> mCurrentControlState;
	std::unordered_map<ControlState::State, std::shared_ptr<ControlState>> mControlStates;
};

