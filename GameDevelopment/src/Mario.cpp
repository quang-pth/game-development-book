#include "include/Mario.h"
#include "include/Game.h"
#include "include/CooldownManager.h"
#include "include/TransformComponent.h"
#include "include/SpriteComponent.h"
#include "include/InputComponent.h"
#include "include/CircleComponent.h"
#include "include/AnimatorComponent.h"
#include "include/RigidBodyComponent.h"
#include "include/Laser.h"
#include "include/Unit.h"
#include "include/Asteroid.h"
#include "include/Animation.h"
#include "include/WalkState.h"
#include "include/IdleState.h"
#include <SDL2/SDL.h>
#include <iostream>
#include<memory>

Hero::Hero(Game* game, std::string name) :
	GameObject(game, name),
	mFireCooldown(0.3f),
	mActivateLaserIdx(0), mSpawnCooldown(1.5f),
	mMoveDirection(Direction::Right),
	mCapacity(30), mLasers(), mFireDirection(Direction::Right),
	mCurrentFireCooldown(0.0f)
{
	mCenterPosition = Vector2(game->GetWindowWidth() / 2 - 30.0f, game->GetWindowHeight() / 2);
	pTransform->SetPosition(mCenterPosition);
	pTransform->SetScale(1.0f);
	
	/*
	* ANIMATIONS
	*/
	// Walking
	std::vector<SDL_Texture*> walkingTextures = {
		game->GetTexture("Assets/Shooter/Hero/Running/tile000.png"),
		game->GetTexture("Assets/Shooter/Hero/Running/tile001.png"),
		game->GetTexture("Assets/Shooter/Hero/Running/tile002.png"),
		game->GetTexture("Assets/Shooter/Hero/Running/tile003.png"),
		game->GetTexture("Assets/Shooter/Hero/Running/tile004.png"),
		game->GetTexture("Assets/Shooter/Hero/Running/tile005.png"),
	};
	std::shared_ptr<Animation> walkingAnimation =  std::make_shared<Animation>("Walk", walkingTextures);
	walkingAnimation->SetFPS(10.0f);
	// Idle
	std::vector<SDL_Texture*> idleTextures = {
		game->GetTexture("Assets/Shooter/Hero/Idle/tile000.png"),
		game->GetTexture("Assets/Shooter/Hero/Idle/tile001.png"),
	};
	std::shared_ptr<Animation> idleAnimation =  std::make_shared<Animation>("Idle", idleTextures);
	idleAnimation->SetFPS(1.5f);
	// Jump
	std::vector<SDL_Texture*> jumpTextures = {
		game->GetTexture("Assets/Shooter/Hero/Jump/tile000.png"),
		game->GetTexture("Assets/Shooter/Hero/Jump/tile001.png"),
	};
	std::shared_ptr<Animation> jumpAnimation = std::make_shared<Animation>("Jump", jumpTextures, false);
	idleAnimation->SetFPS(1.5f);

	// Animator
	animator = new AnimatorComponent(this);
	animator->AddAnimation(walkingAnimation);
	animator->AddAnimation(idleAnimation);
	animator->AddAnimation(jumpAnimation);
	animator->SetAnimation(walkingAnimation->name);

	inputComponent = new InputComponent(this);
	inputComponent->SetForwardSpeed(50.0f);

	circleComponent = new CircleComponent(this);
	circleComponent->SetRadius(20.0f * pTransform->GetScale());

	rigidBodyComponent = new RigidBodyComponent(this);
	rigidBodyComponent->SetBodyType(EBody::DYNAMIC);
	rigidBodyComponent->SetPosition(pTransform->GetPosition());
	rigidBodyComponent->SetDimension(Vector2(8 * pTransform->GetScale(), 8 * pTransform->GetScale()));
	rigidBodyComponent->Init();

	mState = new IdleState();
	mState->Enter(this);

	this->InstantiateLaser();
}

void Hero::UpdateGameObject(float deltaTime)
{
	mCurrentFireCooldown -= deltaTime;

	Vector2 position = Unit::MetersToPixels(rigidBodyComponent->GetBody()->GetPosition());
	pTransform->SetPosition(position.x, position.y);

	mState->Update(this);
	this->ConstraintInScreenBounds();
}

void Hero::ProcessGameObjectInput(const uint8_t* keyState)
{
	GameObjectState* state = mState->HandleInput(this, keyState);
	if (state != nullptr) {
		delete mState;
		mState = state;
		mState->Enter(this);
	}
}

void Hero::StartCooldown()
{
	GameObject::SetState(GameObject::State::EDeactive);
	GameObject::GetGame()->GetCooldownManager()->Observe(this);
}

void Hero::Cooldown(float deltaTime)
{
	mSpawnCooldown -= deltaTime;
	if (mSpawnCooldown <= 0) {
		this->ActAfterCooldown();
	}
}

void Hero::SetDirection(Direction direction)
{
	mMoveDirection = direction;
}

void Hero::Fire()
{
	if (mCurrentFireCooldown > 0.0f) return;

	mActivateLaserIdx++;
	if (mActivateLaserIdx >= mLasers.size()) {
		mActivateLaserIdx = 0;
	}

	Laser* laser = mLasers[mActivateLaserIdx];

	if (mMoveDirection == Direction::Left) {
		Vector2 offset(-5.0f, animator->GetTextureHeight() / 2 - 3.5f);
		laser->pTransform->SetPosition(pTransform->GetPosition() + offset);
		laser->SetDirection(-1);
	}
	else if (mMoveDirection == Direction::Right) {
		Vector2 offset(8.0f, animator->GetTextureHeight() / 2 - 3.5f);
		laser->pTransform->SetPosition(pTransform->GetPosition() + offset);
		laser->SetDirection(1);
	}

	laser->SetState(GameObject::State::EActive);
	mCurrentFireCooldown = mFireCooldown;
}

bool Hero::IsMoving() const
{
	return inputComponent->GetForwardSpeed() != 0.0f;
}

Hero::Direction Hero::GetMoveDirection() const
{
	return mMoveDirection;
}

void Hero::SetMoveDirection(Hero::Direction direction)
{
	mMoveDirection = direction;
}

InputComponent* Hero::GetInputComponent() const
{
	return inputComponent;
}

bool Hero::MoveExceedCenterPoint(bool toTheRight)
{
	if (toTheRight) {
		bool atCenter = pTransform->GetPosition().x > mCenterPosition.x;
		bool isMovingRight = inputComponent->RightKeyIsClicked();
		return atCenter && isMovingRight;
	}
	else {
		bool atCenter = pTransform->GetPosition().x <= mCenterPosition.x;
		bool isMovingLeft = !inputComponent->RightKeyIsClicked();
		return atCenter && isMovingLeft;
	}
}

bool Hero::IsImageFlipped()
{
	return mMoveDirection == Direction::Right;
}

void Hero::ActAfterCooldown()
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
	inputComponent->ResetForce();
}

void Hero::ConstraintInScreenBounds()
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

	if (inputComponent->GetState() == EMovement::EUnMoveable) {
		newXPos = mCenterPosition.x;
	}

	pTransform->SetPosition(Vector2(newXPos, newYPos));
}

void Hero::InstantiateLaser()
{
	for (unsigned int idx = 0; idx < mCapacity; idx++) {
		Laser* laser = new Laser(GameObject::GetGame());
		laser->SetState(GameObject::State::EDeactive);
		laser->pTransform->SetScale(1.5f);
		mLasers.emplace_back(laser);
	}
}
