#include "include/Ship.h"
#include "include/Game.h"
#include "include/CooldownManager.h"
#include "include/TransformComponent.h"
#include "include/SpriteComponent.h"
#include "include/InputComponent.h"
#include "include/CircleComponent.h"
#include "include/Laser.h"
#include "include/Asteroid.h"
#include "include/Renderer.h"
#include "include/Texture.h"
#include <SDL2/SDL.h>
#include <iostream>

Ship::Ship(Game* game) : 
	GameObject(game, "Ship"),
	mFireKey(SDL_SCANCODE_SPACE), mFireCooldown(0.3f), 
	mActivateLaserIdx(0), mSpawnCooldown(1.5f)
{
	mSpriteComponent = new SpriteComponent(this, 21);
	mSpriteComponent->SetTexture(game->GetRenderer()->GetTexture("Assets/Chapter3/Ship.png"));
	
	mInputComponent = new InputComponent(this);
	mInputComponent->SetMaxForwardSpeed(300.0f);
	mInputComponent->SetAngularSpeed(135.0f);

	mCircleComponent = new CircleComponent(this);
	mCircleComponent->SetRadius(mSpriteComponent->GetTextureWidth() * 0.3f);

	this->InitLaserPool();
}

void Ship::UpdateGameObject(float deltaTime)
{
	mFireCooldown -= deltaTime;
	this->ConstraintInScreenBounds();
	this->CheckCollsision();
}

void Ship::ProcessGameObjectInput(const InputState& keyState)
{
	/*if (keyState[mFireKey] && mFireCooldown < 0.0f) {
		Laser* laser = mLasers[mActivateLaserIdx];
		if (laser->GetState() == GameObject::State::EActive) return;
		
		Vector3 offsetForward = GameObject::GetForward() * 10.0f;
		laser->SetState(GameObject::State::EActive);
		laser->GetTransform()->SetPosition(GameObject::GetTransform()->GetPosition() + 
			offsetForward);
		laser->GetTransform()->SetRotation(GameObject::GetTransform()->GetRotation());
		laser->GetMoveComponent()->AddForce(GameObject::GetForward() * 2000.0f, 
			MoveComponent::ForceMode::Constant);

		mFireCooldown = 0.3f;

		mActivateLaserIdx++;
		if (mActivateLaserIdx >= mLasers.size()) {
			mActivateLaserIdx = 0;
		}
	}*/
}

void Ship::StartCooldown()
{
	GameObject::SetState(GameObject::State::EDeactive);
}

void Ship::Cooldown(float deltaTime)
{
	mSpawnCooldown -= deltaTime;
	if (mSpawnCooldown <= 0) {
		this->Respawn();
	}
}

void Ship::Respawn()
{
	mSpawnCooldown = 1.5f;
	// Reset ship position to the center of the screen if collided with asteroid
	GameObject::GetTransform()->SetPosition(Vector3::Zero);
	// Reset game object states
	GameObject::GetTransform()->SetRotation(Quaternion::Identity);
	GameObject::SetState(GameObject::State::EActive);
}

void Ship::InitLaserPool()
{
	for (unsigned int idx = 0; idx < 6; idx++) {
		Laser* laser = new Laser(GameObject::GetGame());
		laser->SetState(GameObject::State::EDeactive);
		mLasers.emplace_back(laser);
	}
}

void Ship::ConstraintInScreenBounds()
{
	float newXPos = GameObject::GetTransform()->GetPosition().x;
	float newYPos = GameObject::GetTransform()->GetPosition().y;
	float xBound = GameObject::GetGame()->GetWindowWidth() / 2.0f;
	float yBound = GameObject::GetGame()->GetWindowHeight() / 2.0f;

	if (GameObject::GetTransform()->GetPosition().x > xBound) {
		newXPos = xBound;
	}
	else if (GameObject::GetTransform()->GetPosition().x < -xBound) {
		newXPos = -xBound;
	}

	if (GameObject::GetTransform()->GetPosition().y > yBound) {
		newYPos = yBound;
	}
	else if (GameObject::GetTransform()->GetPosition().y < -yBound) {
		newYPos = -yBound;
	}

	GameObject::GetTransform()->SetPosition(Vector3(newXPos, newYPos, 0.0f));
}

void Ship::CheckCollsision()
{
	/*for (Asteroid* asteroid : GameObject::GetGame()->GetAsteroids()) {
		if (asteroid->GetState() == GameObject::State::EActive) {
			bool isCollided = CircleComponent::IsIntersect(this->mCircleComponent, 
				asteroid->GetCircleComponent());
			if (isCollided) {
				this->StartCooldown();
			}
		}
	}*/
}
