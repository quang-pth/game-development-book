#include"include/Game.h"
#include"include/GameObject.h"
#include"include/Component.h"
#include"include/TransformComponent.h"
#include"include/CustomMath.h"
#include <iostream>

GameObject::GameObject() : mpGame(), name(), mState(), pTransform()
{
}

GameObject::GameObject(Game* game, std::string name) :
	mpGame(game), name(name), mState(GameObject::State::EActive)
{
	this->AddDefaultComponents();
	mpGame->AddGameObject(this);
}

GameObject::~GameObject()
{
	mpGame->RemoveGameObject(this);
	while (!mpComponents.empty()) {
		delete mpComponents.back();
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
	for (Component* component : mpComponents) {
		component->Update(deltaTime);
	}
}

void GameObject::ProcessInput(const uint8_t* keyState)
{
	if (mState == GameObject::State::EActive) {
		for (Component* component : mpComponents) {
			component->ProcessInput(keyState);
		}
	
		ProcessGameObjectInput(keyState);
	}
}

void GameObject::UpdateGameObject(float deltaTime)
{

}

void GameObject::ProcessGameObjectInput(const uint8_t* keyState)
{
}

void GameObject::AddComponent(Component* component)
{
	std::vector<Component*>::iterator iter = mpComponents.begin();
	for (; iter != mpComponents.end(); iter++) {
		if ((*iter)->GetUpdateOrder() > component->GetUpdateOrder()) {
			break;
		}
	}
	mpComponents.insert(iter, component);
}

void GameObject::RemoveComponent(Component* component)
{
	std::vector<Component*>::iterator iter = std::find(mpComponents.begin(), 
		mpComponents.end(), component);
 	if (iter != mpComponents.end()) {
		mpComponents.erase(iter);
	}
}

void GameObject::RemoveGameObjectComponent(Component* component)
{
}

GameObject::State GameObject::GetState() const
{
	return mState;
}

void GameObject::SetState(State state)
{
	mState = state;
}

Component* GameObject::GetComponent(std::string name)
{
	std::vector<Component*>::iterator iter = std::find_if(mpComponents.begin(), mpComponents.end(),
		[&](const Component* component){ return component->name == name; });
	
	if (iter != mpComponents.end()) {
		return (*iter);
	}

	std::cout << "Cannot find component with name: " << name << std::endl;
	return nullptr;
}

Vector2 GameObject::GetForward() const
{
	return Vector2(Math::Cos(pTransform->GetRotation()), -Math::Sin(pTransform->GetRotation()));
}

Game* GameObject::GetGame() const
{
	return mpGame;
}

void GameObject::AddDefaultComponents()
{
	pTransform = new TransformComponent(this, 0, "TransformComponent");
}
