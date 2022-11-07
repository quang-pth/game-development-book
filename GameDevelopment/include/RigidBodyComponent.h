#pragma once

#include"include/Component.h"
#include"include/CustomMath.h"
#include<box2d/b2_body.h>

enum class EBody
{
	STATIC,
	DYNAMIC,
};

class RigidBodyComponent : public Component
{
public:
	RigidBodyComponent(class GameObject* mOwner, int updateOrder = 60,
		const std::string& name = "RigibodyComponent");
	~RigidBodyComponent();
	void SetBodyType(EBody type);
	void SetTransform(const Vector2& position);
	void SetPosition(const Vector2& position);
	void SetVelocity(const Vector2& velocity);
	void Jump(float force);
	void SetDimension(const Vector2& dimension);
	void Init();
	b2Body* GetBody() const;
	float density;
	float friction;
private:
	b2Body* mBody;
	EBody mType;
	b2Vec2 mPosition, mDimension;
	b2BodyDef mBodyDef;
};

