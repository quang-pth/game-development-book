#include"include/Game.h"
#include"include/GameObject.h"
#include"include/Component.h"
#include"include/TransformComponent.h"
#include"include/CustomMath.h"
#include <iostream>

GameObject::GameObject(Game* game, std::string name) : mGame(game), mName(name), mState(GameObject::State::EActive)
{
	mGame->AddGameObject(this);
	this->AddDefaultComponents();
}

GameObject::~GameObject()
{
	mGame->RemoveGameObject(this);
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

void GameObject::Update(float deltaTime) 
{
	if (mState == GameObject::State::EActive) {
		UpdateComponents(deltaTime);
		UpdateGameObject(deltaTime);
	}
}

void GameObject::UpdateComponents(float deltaTime)
{
	for (auto component : mComponents) {
		component->Update(deltaTime);
	}
}

void GameObject::UpdateGameObject(float deltaTime)
{

}

void GameObject::AddComponent(Component* component)
{
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); iter++) {
		if ((*iter)->GetUpdateOrder() > component->GetUpdateOrder()) {
			break;
		}
	}
	mComponents.insert(iter, component);
}

void GameObject::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}

GameObject::State GameObject::GetState() const
{
	return mState;
}

TransformComponent* GameObject::GetTransform() const
{
	return mTransform;
}

Component* GameObject::GetComponent(std::string name)
{
	auto iter = std::find_if(mComponents.begin(), mComponents.end(), 
		[&](const Component* component){ return component->mName == name; });
	
	if (iter != mComponents.end()) {
		return (*iter);
	}

	std::cout << "Cannot find component with name: " << name << std::endl;
	return nullptr;
}

Vector2 GameObject::GetForward() const
{
	return Vector2(Math::Cos(mTransform->GetRotation()), -Math::Sin(mTransform->GetRotation()));
}

Game* GameObject::GetGame() const
{
	return mGame;
}

void GameObject::AddDefaultComponents()
{
	mTransform = new TransformComponent(this, 0, "TransformComponent");
}
