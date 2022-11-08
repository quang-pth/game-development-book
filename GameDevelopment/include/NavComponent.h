#pragma once

#include"include/MoveComponent.h"
#include "include/CustomMath.h"

class NavComponent : public	MoveComponent
{
public:
	NavComponent(class GameObject* owner, int updateOrder, const std::string& name = "NavComponent");
	~NavComponent();
	void Update(float deltaTime) override;
private:
	void TurnTo(const Vector2& nextPoint);
	Vector2& GetNextPoint() const;
	Vector2 mNextPoint;
};

