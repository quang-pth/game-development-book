#pragma once

#include <string>

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
	virtual void ProcessInput(const uint8_t* keyState);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class GameObject* mOwner;
	int mUpdateOrder;
};

