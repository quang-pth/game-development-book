#include<include/Actor.h>
#include<include/Game.h>
#include<include/Component.h>

Actor::Actor(Game* game) : mGame(game), mRotation(0.0f), 
		mScale(1.0f), mTransform(Vector2::Zero), mState(Actor::State::EActive)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime) 
{
	if (mState == Actor::State::EActive) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto component : mComponents) {
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{

}

void Actor::AddComponent(Component* component)
{
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); iter++) {
		if ((*iter)->GetUpdateOrder() > component->GetUpdateOrder()) {
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}
