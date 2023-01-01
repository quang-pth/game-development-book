#include"include/Game.h"
#include"include/GameObject.h"
#include"include/Component.h"
#include"include/TransformComponent.h"
#include"include/CustomMath.h"
#include <iostream>

GameObject::GameObject() : mGame(), name(), mState(), mTransform()
{
}

GameObject::GameObject(Game* game, const std::string& name) :
	mGame(game), name(name), mState(GameObject::State::EActive)
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
	if (this->IsActived()) {
		mTransform->ComputeWorldTransform();
		UpdateComponents(deltaTime);
		UpdateGameObject(deltaTime);
		mTransform->ComputeWorldTransform();
	}
}

void GameObject::UpdateComponents(float deltaTime)
{
	for (Component* component : mComponents) {
		component->Update(deltaTime);
	}
}

void GameObject::ProcessInput(const InputState& inputState)
{
	if (this->IsActived()) {
		for (Component* component : mComponents) {
			component->ProcessInput(inputState);
		}
	
		ProcessGameObjectInput(inputState);
	}
}

void GameObject::UpdateGameObject(float deltaTime)
{

}

void GameObject::ProcessGameObjectInput(const InputState& inputState)
{
}

void GameObject::AddComponent(Component* component)
{
	std::vector<Component*>::iterator iter = mComponents.begin();
	for (; iter != mComponents.end(); iter++) {
		if ((*iter)->GetUpdateOrder() > component->GetUpdateOrder()) {
			break;
		}
	}
	mComponents.insert(iter, component);
}

void GameObject::RemoveComponent(Component* component)
{
	std::vector<Component*>::iterator iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}

GameObject::State GameObject::GetState() const
{
	return mState;
}

void GameObject::SetState(State state)
{
	mState = state;
}

TransformComponent* GameObject::GetTransform() const
{
	return mTransform;
}

Component* GameObject::GetComponent(std::string name)
{
	std::vector<Component*>::iterator iter = std::find_if(mComponents.begin(), mComponents.end(),
		[&](const Component* component){ return component->mName == name; });
	
	if (iter != mComponents.end()) {
		return (*iter);
	}

	std::cout << "Cannot find component with name: " << name << std::endl;
	return nullptr;
}

std::vector<class Component*> GameObject::GetComponents() const
{
	return mComponents;
}

Vector3 GameObject::GetForward() const
{
	return Vector3::Transform(Vector3::UnitX, mTransform->GetRotation());
}

Vector3 GameObject::GetRight() const
{
	return Vector3::Transform(Vector3::UnitY, mTransform->GetRotation());
}

Game* GameObject::GetGame() const
{
	return mGame;
}

void GameObject::AddDefaultComponents()
{
	mTransform = new TransformComponent(this, 0, "TransformComponent");
}
