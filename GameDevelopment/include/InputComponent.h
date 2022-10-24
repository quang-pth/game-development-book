#pragma once
#include "include/MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	enum class State {
		EMoveable,
		EUnMoveable,
	};
	InputComponent();
	InputComponent(class GameObject* owner, int updateOrder = 4);
	~InputComponent();
	void Update(float deltaTime) override;
	void ProcessInput(const uint8_t* keyState) override;
	float GetMaxForwardSpeed() const;
	void SetMaxForwardSpeed(float speed);
	int GetForwardLeftKey() const;
	int GetForwardRightKey() const;
	void SetState(State state);
	State GetState() const;
private:
	float mMaxForwardSpeed;
	int mForwardLeftKey, mForwardRightKey;
	State mState;
};

