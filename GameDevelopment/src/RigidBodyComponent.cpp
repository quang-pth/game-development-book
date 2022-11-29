#include "RigidBodyComponent.h"
#include "include/Game.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"
#include "include/TileMap.h"
#include "include/Unit.h"
#include<box2d/b2_polygon_shape.h>
#include <iostream>

RigidBodyComponent::RigidBodyComponent(GameObject* mOwner, int updateOrder, const std::string& name) :
	Component(mOwner, updateOrder, name),
	mType(EBody::STATIC), mBody(), mFixtureDef(), mFixture(),
	density(0.0f), friction(0.0f)
{
	mPosition.SetZero();
	mDimension.SetZero();
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::SetBodyType(EBody type)
{
	mType = type;
	density = 1.0f;
	friction = 0.3f;
}

void RigidBodyComponent::SetTransform(const Vector2& position)
{
	mBody->SetTransform(Unit::PixelsToMeters(position), mBody->GetAngle());
}

void RigidBodyComponent::SetPosition(const Vector2& position)
{
	mPosition = Unit::PixelsToMeters(position);
}

Vector2* RigidBodyComponent::GetPosition() const
{
	Vector2 position = Unit::MetersToPixels(mBody->GetPosition());
	return &position;
}

void RigidBodyComponent::Move(const Vector2& velocity)
{
	const b2Vec2& vec = Unit::PixelsToMeters(velocity);
	mBody->SetLinearVelocity(mBody->GetLinearVelocity() + vec);
}

void RigidBodyComponent::Jump(float force)
{
	b2Vec2 prevVelocity = mBody->GetLinearVelocity();
	prevVelocity.y = 0;
	b2Vec2 jumpVelocity = Unit::PixelsToMeters(Vector2(0.0f, -force));

	mBody->ApplyForceToCenter(jumpVelocity, true);
	//mBody->SetLinearVelocity((prevVelocity + jumpVelocity) * 0.8);
}

void RigidBodyComponent::SetDimension(const Vector2& dimension)
{
	mDimension = Unit::PixelsToMeters(dimension);
}

void RigidBodyComponent::SetGravity(float gravity)
{
	mBody->SetGravityScale(gravity);
}

void RigidBodyComponent::WakeUp(bool wakeUp)
{
	mBody->SetAwake(wakeUp);
}

void RigidBodyComponent::SetActive(bool isActive)
{
	mBody->SetEnabled(isActive);
}

b2Fixture* RigidBodyComponent::GetFixture() const
{
	return mFixture;
}

void RigidBodyComponent::Init()
{
	b2PolygonShape polygonShape;
	
	switch (mType)
	{
	case EBody::DYNAMIC:
		mBodyDef.type = b2_dynamicBody;
		mBodyDef.position.Set(mPosition.x, mPosition.y);
		mBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(mOwner);
		mBody = mOwner->GetGame()->GetPhysicWorld()->CreateBody(&mBodyDef);
		polygonShape.SetAsBox(mDimension.x, mDimension.y);
		mFixtureDef.shape = &polygonShape;
		mFixtureDef.density = this->density;
		mFixtureDef.friction = this->friction;
		mFixture = mBody->CreateFixture(&mFixtureDef);
		break;
	case EBody::STATIC:
		mBodyDef.position.Set(mPosition.x, mPosition.y);
		mBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(mOwner);
		mBody = mOwner->GetGame()->GetPhysicWorld()->CreateBody(&mBodyDef);
		polygonShape.SetAsBox(mDimension.x, mDimension.y);
		mBody->CreateFixture(&polygonShape, 0.0f);
		break;
	default:
		break;
	}
}

b2Body* RigidBodyComponent::GetBody() const
{
	return mBody;
}
