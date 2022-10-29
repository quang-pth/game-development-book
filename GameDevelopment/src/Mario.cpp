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
	GameObject::GetTransform()->SetPosition(mCenterPosition);
	GameObject::GetTransform()->SetScale(2.0f);
	
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
	mAnimator = new AnimatorComponent(this);
	mAnimator->AddAnimation(walkingAnimation->mName, walkingAnimation);
	mAnimator->AddAnimation(idleAnimation->mName, idleAnimation);
	mAnimator->SetAnimation(walkingAnimation->mName);

	mInputComponent = new InputComponent(this);
	mInputComponent->SetForwardSpeed(50.0f);

	mCircleComponent = new CircleComponent(this);
	mCircleComponent->SetRadius(20.0f * GameObject::GetTransform()->GetScale());

	mState = new IdleState();
	mState->Enter(this);
}

void Mario::UpdateGameObject(float deltaTime)
{
	mState->Update(this);
	this->ConstraintInScreenBounds();
}

void Mario::ProcessGameObjectInput(const uint8_t* keyState)
{
	GameObjectState* state = mState->HandleInput(this, keyState);
	if (state != nullptr) {
		delete mState;
		mState = state;
		mState->Enter(this);
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
	return mInputComponent;
}

bool Mario::MoveExceedCenterPoint(bool toTheRight)
{
	if (toTheRight) {
		bool atCenter = GameObject::GetTransform()->GetPosition().x > mCenterPosition.x;
		bool isMovingRight = mInputComponent->RightKeyIsClicked();
		return atCenter && isMovingRight;
	}
	else {
		bool atCenter = GameObject::GetTransform()->GetPosition().x <= mCenterPosition.x;
		bool isMovingLeft = !mInputComponent->RightKeyIsClicked();
		return atCenter && isMovingLeft;
	}
}

bool Mario::FlipImage()
{
	return mMoveDirection == Direction::Right;
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

	if (mInputComponent->GetState() == EMovement::EUnMoveable) {
		newXPos = mCenterPosition.x;
	}

	GameObject::GetTransform()->SetPosition(Vector2(newXPos, newYPos));
}