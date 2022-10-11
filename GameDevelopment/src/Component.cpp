#include"include/Component.h"

Component::Component()
{
}

Component::Component(GameObject* owner, int updateOrder) : mOwner(owner)
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