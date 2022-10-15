#include<include/GameObject.h>
#include<include/Game.h>
#include<include/Component.h>
#include<include/TransformComponent.h>
#include <iostream>

GameObject::GameObject(Game* game) : mGame(game), mState(GameObject::State::EActive)
{
	mGame->AddGameObject(this);
	this->AddTransformComponent();
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

void GameObject::AddTransformComponent()
{
	mTransform = new TransformComponent(this, 0, "TransformComponent");
	this->AddComponent(mTransform);
}
