#pragma once

#include <string>
#include"include/InputSystem.h"

class Component
{
public:
	std::string mName;
	Component();
	/*
	* updateOrder: component with smaller updateOrder is updated first
	*/
	Component(class GameObject* owner, int updateOrder = 100, std::string name = "");
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const InputState& inputState);
	virtual void OnUpdateWorldTransform();
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class GameObject* mOwner;
	int mUpdateOrder;
};

