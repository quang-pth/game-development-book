#include<include/GameObject.h>
#include<include/Game.h>
#include<include/Component.h>

GameObject::GameObject(Game* game) : mGame(game), mRotation(0.0f), 
		mScale(1.0f), mTransform(Vector2::Zero), mState(GameObject::State::EActive)
{
	mGame->AddGameObject(this);
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
