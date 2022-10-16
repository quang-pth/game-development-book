#pragma once

#include"include/Component.h"
#include"include/CustomMath.h"

class CircleComponent : public Component
{
public:
	CircleComponent();
	CircleComponent(class GameObject* owner, int updateOrder = 100);
	const Vector2& GetCenter() const;
	float GetRadius() const;
	void SetRadius(float radius);
	static bool IsIntersect(const CircleComponent* circle1, const CircleComponent* circle2);
private:
	float mRadius;
};

