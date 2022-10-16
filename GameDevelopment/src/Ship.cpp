#include "include/Ship.h"
#include "include/Game.h"
#include "include/TransformComponent.h"
#include "include/SpriteComponent.h"
#include "include/InputComponent.h"
#include "include/CircleComponent.h"
#include "include/Laser.h"
#include <SDL2/SDL.h>

Ship::Ship(Game* game) : 
	GameObject(game, "Ship"), 
	mFireKey(SDL_SCANCODE_SPACE), mFireCooldown(0.3f), mActivateLaserIdx(0)
{
	GameObject::GetTransform()->SetPosition(Vector2(game->GetWindowWidth() / 2, game->GetWindowHeight() / 2));

	mSpriteComponent = new SpriteComponent(this);
	mSpriteComponent->SetTexture(game->GetTexture("Assets/Chapter3/Ship.png"));

	mInputComponent = new InputComponent(this);

	this->InitLaserPool();
}

void Ship::UpdateGameObject(float deltaTime)
{
	mFireCooldown -= deltaTime;

	TransformComponent* transform = GameObject::GetTransform();
	float newXPos = transform->GetPosition().x;
	float newYPos = transform->GetPosition().y;

	if (transform->GetPosition().x > GetGame()->GetWindowWidth()) {
		newXPos = GetGame()->GetWindowWidth();
	}
	else if (transform->GetPosition().x < 0.0f) {
		newXPos = 0.0f;
	}

	if (transform->GetPosition().y > GetGame()->GetWindowHeight()) {
		newYPos = GetGame()->GetWindowHeight();
	}
	else if (transform->GetPosition().y < 0.0f) {
		newYPos = 0.0f;
	}

	transform->SetPosition(Vector2(newXPos, newYPos));
}

void Ship::ProcessGameObjectInput(const uint8_t* keyState)
{
	if (keyState[mFireKey] && mFireCooldown < 0.0f) {
		Laser* laser = mLasers[mActivateLaserIdx];
		if (laser->GetState() == GameObject::State::EActive) return;
		
		Vector2 firePosition = GameObject::GetForward() * 10.0f;
		laser->SetState(GameObject::State::EActive);
		laser->GetTransform()->SetPosition(GameObject::GetTransform()->GetPosition() + firePosition);
		laser->GetTransform()->SetRotation(GameObject::GetTransform()->GetRotation());
		laser->GetMoveComponent()->SetForwardSpeed(400.0f);
		
		mFireCooldown = 0.3f;

		mActivateLaserIdx++;
		if (mActivateLaserIdx >= mLasers.size()) {
			mActivateLaserIdx = 0;
		}
	}
}

void Ship::InitLaserPool()
{
	for (unsigned int idx = 0; idx < 30; idx++) {
		Laser* laser = new Laser(GameObject::GetGame());
		laser->SetState(GameObject::State::EDeactive);
		mLasers.emplace_back(laser);
	}
}
