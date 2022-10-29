#include "include/Mario.h"
#include "include/Game.h"
#include "include/CooldownManager.h"
#include "include/TransformComponent.h"
#include "include/SpriteComponent.h"
#include "include/InputComponent.h"
#include "include/CircleComponent.h"
#include "include/Laser.h"
#include "include/Asteroid.h"
#include "include/AnimatorComponent.h"
#include "include/Animation.h"
#include "include/WalkState.h"
#include "include/IdleState.h"
#include <SDL2/SDL.h>
#include <iostream>
#include<memory>

Mario::Mario(Game* game, std::string name) :
	GameObject(game, name),
	mFireKey(SDL_SCANCODE_SPACE), mFireCooldown(0.3f),
	mActivateLaserIdx(0), mSpawnCooldown(1.5f),
	mMoveDirection(Direction::Right)
{
	mCenterPosition = Vector2(game->GetWindowWidth() / 2 , game->GetWindowHeight() / 2);
	pTransform->SetPosition(mCenterPosition);
	pTransform->SetScale(2.0f);
	
	// Animations
	std::vector<SDL_Texture*> walkingTextures = {
		game->GetTexture("MarioAssets/mario-2.png"),
		game->GetTexture("MarioAssets/mario-3.png"),
		game->GetTexture("MarioAssets/mario-4.png"),
	};
	std::shared_ptr<Animation> walkingAnimation =  std::make_shared<Animation>("Walk", walkingTextures);
	walkingAnimation->SetFPS(10.0f);
	std::vector<SDL_Texture*> idleTextures = {
		game->GetTexture("MarioAssets/mario-1.png"),
	};
	std::shared_ptr<Animation> idleAnimation =  std::make_shared<Animation>("Idle", idleTextures);
	idleAnimation->SetFPS(1.0f);
	// Animator
	pAnimator = new AnimatorComponent(this);
	pAnimator->AddAnimation(walkingAnimation->mName, walkingAnimation);
	pAnimator->AddAnimation(idleAnimation->mName, idleAnimation);
	pAnimator->SetAnimation(walkingAnimation->mName);

	pInputComponent = new InputComponent(this);
	pInputComponent->SetForwardSpeed(50.0f);

	pCircleComponent = new CircleComponent(this);
	pCircleComponent->SetRadius(20.0f * pTransform->GetScale());

	mpState = new IdleState();
	mpState->Enter(this);
}

void Mario::UpdateGameObject(float deltaTime)
{
	mpState->Update(this);
	this->ConstraintInScreenBounds();
}

void Mario::ProcessGameObjectInput(const uint8_t* keyState)
{
	GameObjectState* state = mpState->HandleInput(this, keyState);
	if (state != nullptr) {
		delete mpState;
		mpState = state;
		mpState->Enter(this);
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

Mario::Direction Mario::GetMoveDirection() const
{
	return mMoveDirection;
}

void Mario::SetMoveDirection(bool toTheRight)
{
	if (toTheRight) {
		mMoveDirection = Direction::Right;
	}
	else {
		mMoveDirection = Direction::Left;
	}
}

InputComponent* Mario::GetInputComponent() const
{
	return pInputComponent;
}

bool Mario::MoveExceedCenterPoint(bool toTheRight)
{
	if (toTheRight) {
		bool atCenter = pTransform->GetPosition().x > mCenterPosition.x;
		bool isMovingRight = pInputComponent->RightKeyIsClicked();
		return atCenter && isMovingRight;
	}
	else {
		bool atCenter = pTransform->GetPosition().x <= mCenterPosition.x;
		bool isMovingLeft = !pInputComponent->RightKeyIsClicked();
		return atCenter && isMovingLeft;
	}
}

bool Mario::IsImageFlipped()
{
	return mMoveDirection == Direction::Right;
}

void Mario::ActAfterCooldown()
{
	mSpawnCooldown = 1.5f;
	// Reset ship position to the center of the screen if collided with asteroid
	pTransform->SetPosition(Vector2(
		GameObject::GetGame()->GetWindowWidth() / 2.0f,
		GameObject::GetGame()->GetWindowHeight() / 2.0f
	));
	// Reset game object states
	pTransform->SetRotation(0.0f);
	GameObject::GetGame()->GetCooldownManager()->Release(this);
	GameObject::SetState(GameObject::State::EActive);
	pInputComponent->ResetForce();
}

void Mario::ConstraintInScreenBounds()
{
	float newXPos = pTransform->GetPosition().x;
	float newYPos = pTransform->GetPosition().y;

	if (pTransform->GetPosition().x > GameObject::GetGame()->GetWindowWidth()) {
		newXPos = GameObject::GetGame()->GetWindowWidth();
	}
	else if (pTransform->GetPosition().x < 0.0f) {
		newXPos = 0.0f;
	}

	if (pTransform->GetPosition().y > GameObject::GetGame()->GetWindowHeight()) {
		newYPos = GameObject::GetGame()->GetWindowHeight();
	}
	else if (pTransform->GetPosition().y < 0.0f) {
		newYPos = 0.0f;
	}

	if (pInputComponent->GetState() == EMovement::EUnMoveable) {
		newXPos = mCenterPosition.x;
	}

	pTransform->SetPosition(Vector2(newXPos, newYPos));
}