#pragma once

#include"include/GameObject.h"

class Component
{
public:
	Component();
	Component(GameObject* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	GameObject* mOwner;
	int mUpdateOrder;
};

