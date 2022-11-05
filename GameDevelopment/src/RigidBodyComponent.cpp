#include "RigidBodyComponent.h"
#include "include/Game.h"
#include "include/GameObject.h"
#include "include/Unit.h"
#include<box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

RigidBodyComponent::RigidBodyComponent(GameObject* mOwner, int updateOrder, const std::string& name) :
	Component(mOwner, updateOrder, name),
	mType(EBody::STATIC), mBody(),
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

void RigidBodyComponent::SetPosition(const Vector2& position)
{
	mPosition = Unit::PixelsToMeters(position);
}

void RigidBodyComponent::SetDimension(const Vector2& dimension)
{
	mDimension = Unit::PixelsToMeters(dimension);
}

void RigidBodyComponent::Init()
{
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;

	switch (mType)
	{
	case EBody::DYNAMIC:
		mBodyDef.type = b2_dynamicBody;
		mBodyDef.position.Set(mPosition.x, mPosition.y);
		mBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(mOwner);
		mBody = mOwner->GetGame()->GetPhysicWorld()->CreateBody(&mBodyDef);
		polygonShape.SetAsBox(mDimension.x, mDimension.y);
		fixtureDef.shape = &polygonShape;
		fixtureDef.density = this->density;
		fixtureDef.friction = this->friction;
		mBody->CreateFixture(&fixtureDef);
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
