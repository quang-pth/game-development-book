#pragma once

#include <string>
#include"include/InputSystem.h"

class Component
{
public:
	std::string mName;
	Component() = default;
	/*
	* updateOrder: component with smaller updateOrder is updated first
	*/
	Component(class GameObject* owner, int updateOrder = 100, const std::string& name = "");
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const InputState& inputState);
	virtual void OnUpdateWorldTransform();
	int GetUpdateOrder() const { return mUpdateOrder; }
	class GameObject* GetOwner() const { return mOwner; }
protected:
	class GameObject* mOwner;
	int mUpdateOrder;
};

