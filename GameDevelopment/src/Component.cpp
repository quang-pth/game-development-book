#include"include/GameObject.h"
#include"include/Component.h"

Component::Component(GameObject* owner, int updateOrder, const std::string& name) : 
	mOwner(owner), mUpdateOrder(updateOrder), mName(name),
	mIsActive(true)
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

void Component::ProcessInput(const InputState& inputState)
{
}

void Component::OnUpdateWorldTransform()
{
}
