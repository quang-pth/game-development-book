#include "include/Mario.h"
#include "include/Game.h"
#include "include/CooldownManager.h"
#include "include/TransformComponent.h"
#include "include/SpriteComponent.h"
#include "include/InputComponent.h"
#include "include/CircleComponent.h"
#include "include/Laser.h"
#include "include/Asteroid.h"
#include <SDL2/SDL.h>
#include <iostream>

Mario::Mario(Game* game) :
	GameObject(game, "Ship"),
	mFireKey(SDL_SCANCODE_SPACE), mFireCooldown(0.3f),
	mActivateLaserIdx(0), mSpawnCooldown(1.5f)
{
	GameObject::GetTransform()->SetPosition(Vector2(game->GetWindowWidth() / 2, game->GetWindowHeight() / 2));

	mSpriteComponent = new SpriteComponent(this);
	mSpriteComponent->SetTexture(game->GetTexture("Assets/Chapter3/Ship.png"));

	mInputComponent = new InputComponent(this);
	mInputComponent->SetMaxForwardSpeed(300.0f);
	mInputComponent->SetAngularSpeed(135.0f);

	mCircleComponent = new CircleComponent(this);
	mCircleComponent->SetRadius(mSpriteComponent->GetTextureWidth() * 0.3f);

	this->InitLaserPool();
}

void Mario::UpdateGameObject(float deltaTime)
{
	mFireCooldown -= deltaTime;
	this->ConstraintInScreenBounds();
	this->CheckCollsision();
}

void Mario::ProcessGameObjectInput(const uint8_t* keyState)
{
	if (keyState[mFireKey] && mFireCooldown < 0.0f) {
		Laser* laser = mLasers[mActivateLaserIdx];
		if (laser->GetState() == GameObject::State::EActive) return;

		Vector2 offsetForward = GameObject::GetForward() * 10.0f;
		laser->SetState(GameObject::State::EActive);
		laser->GetTransform()->SetPosition(GameObject::GetTransform()->GetPosition() + offsetForward);
		laser->GetTransform()->SetRotation(GameObject::GetTransform()->GetRotation());
		laser->GetMoveComponent()->AddForce(GameObject::GetForward() * 2000.0f,
			MoveComponent::ForceMode::Constant);

		mFireCooldown = 0.3f;

		mActivateLaserIdx++;
		if (mActivateLaserIdx >= mLasers.size()) {
			mActivateLaserIdx = 0;
		}
	}
}

void Mario::StartCooldown()
{
	GameObject::SetState(GameObject::State::EDeactive);
	GameObject::GetGame()->GetCooldownManager()->Observe(this);
}

void Mario::Cooldown(float deltaTime)
{
	mSpawnCooldown -= deltaTime;
	if (mSpawnCooldown <= 0) {
		this->ActAfterCooldown();
	}
}

void Mario::ActAfterCooldown()
{
	mSpawnCooldown = 1.5f;
	// Reset ship position to the center of the screen if collided with asteroid
	GameObject::GetTransform()->SetPosition(Vector2(
		GameObject::GetGame()->GetWindowWidth() / 2.0f,
		GameObject::GetGame()->GetWindowHeight() / 2.0f
	));
	// Reset game object states
	GameObject::GetTransform()->SetRotation(0.0f);
	GameObject::GetGame()->GetCooldownManager()->Release(this);
	GameObject::SetState(GameObject::State::EActive);
	mInputComponent->ResetForce();
}

void Mario::InitLaserPool()
{
	for (unsigned int idx = 0; idx < 6; idx++) {
		Laser* laser = new Laser(GameObject::GetGame());
		laser->SetState(GameObject::State::EDeactive);
		mLasers.emplace_back(laser);
	}
}

void Mario::ConstraintInScreenBounds()
{
	float newXPos = GameObject::GetTransform()->GetPosition().x;
	float newYPos = GameObject::GetTransform()->GetPosition().y;

	if (GameObject::GetTransform()->GetPosition().x > GameObject::GetGame()->GetWindowWidth()) {
		newXPos = GameObject::GetGame()->GetWindowWidth();
	}
	else if (GameObject::GetTransform()->GetPosition().x < 0.0f) {
		newXPos = 0.0f;
	}

	if (GameObject::GetTransform()->GetPosition().y > GameObject::GetGame()->GetWindowHeight()) {
		newYPos = GameObject::GetGame()->GetWindowHeight();
	}
	else if (GameObject::GetTransform()->GetPosition().y < 0.0f) {
		newYPos = 0.0f;
	}

	GameObject::GetTransform()->SetPosition(Vector2(newXPos, newYPos));
}

void Mario::CheckCollsision()
{
	for (Asteroid* asteroid : GameObject::GetGame()->GetAsteroids()) {
		if (asteroid->GetState() == GameObject::State::EActive) {
			bool isCollided = CircleComponent::IsIntersect(this->mCircleComponent,
				asteroid->GetCircleComponent());
			if (isCollided) {
				this->StartCooldown();
			}
		}
	}
}