#include"include/GameObject.h"
#include"include/Component.h"

Component::Component(GameObject* owner, int updateOrder, const std::string& name) : 
	mOwner(owner), mUpdateOrder(updateOrder), name(name)
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

GameObject* Component::GetOwner() const
{
	return mOwner;
}
