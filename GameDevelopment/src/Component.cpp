#include"include/GameObject.h"
#include"include/Component.h"

Component::Component() : mOwner(), mUpdateOrder(), mName()
{
}

Component::Component(GameObject* owner, int updateOrder, const std::string& name) : 
	mOwner(owner), mUpdateOrder(updateOrder), mName(name)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}

void Component::ProcessInput(const uint8_t* keyState)
{
}
