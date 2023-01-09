#pragma once

#include"include/MoveComponent.h"

class BallMoveComponent : MoveComponent
{
public:
	BallMoveComponent(class GameObject* owner, int updateOrder = 101, const std::string& name = "BallMoveComponent");
	virtual void Update(float deltaTime) override;
};

