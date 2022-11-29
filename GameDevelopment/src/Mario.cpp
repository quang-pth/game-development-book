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
#include "include/JumpState.h"
#include "include/HurtState.h"
#include "include/DeathState.h"
#include "include/Weapon.h"
#include "include/Health.h"
#include <SDL2/SDL.h>
#include <iostream>

Hero::Hero(Game* game, const std::string& name) :
	GameObject(game, name), mStateMap(), mIsAttacked(false)
{
	mCenterPosition = Vector2(game->GetWindowWidth() / 2 - 30.0f, game->GetWindowHeight() / 2);
	pTransform->SetPosition(mCenterPosition);
	pTransform->SetScale(1.8f);
	
	mWeapon.reset(new Weapon(this));

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
	// Hurt
	std::vector<SDL_Texture*> hurtTextures = {
		game->GetTexture("Assets/Shooter/Hero/Hurt/tile000.png")
	};
	std::shared_ptr<Animation> hurtAnimation = std::make_shared<Animation>("Hurt", hurtTextures, false);
	hurtAnimation->SetFPS(1.5f);

	// Animator
	animator = new AnimatorComponent(this);
	animator->AddAnimation(walkingAnimation);
	animator->AddAnimation(idleAnimation);
	animator->AddAnimation(jumpAnimation);
	animator->AddAnimation(hurtAnimation);
	animator->SetAnimation(walkingAnimation->name);

	inputComponent = new InputComponent(this);
	inputComponent->SetForwardSpeed(50.0f);

	circleComponent = new CircleComponent(this);
	circleComponent->SetRadius(20.0f * pTransform->GetScale());

	const Vector2& offsetPos = Vector2(TILE_SIZE * pTransform->GetScale() * 0.5f, 0.0f);
	rigidBodyComponent = new RigidBodyComponent(this);
	rigidBodyComponent->SetBodyType(EBody::DYNAMIC);
	rigidBodyComponent->SetPosition(pTransform->GetPosition() + offsetPos);
	rigidBodyComponent->SetDimension(Vector2(TILE_SIZE, TILE_SIZE) * pTransform->GetScale() * 0.3f);
	rigidBodyComponent->Init();

	mHealth.reset(new Health(20));

	mStateMap.emplace("IdleState", new IdleState(this));
	mStateMap.emplace("WalkState", new WalkState(this));
	mStateMap.emplace("JumpState", new JumpState(this));
	mStateMap.emplace("HurtState", new HurtState(this));
	mStateMap.emplace("DeathState", new DeathState(this));
	this->ChangeState("IdleState");
	mCurrentState->Enter();
}

void Hero::UpdateGameObject(float deltaTime)
{
	mWeapon->Update(deltaTime);

	const Vector2& position = Unit::MetersToPixels(rigidBodyComponent->GetBody()->GetPosition());
	pTransform->SetPosition(position);

	mCurrentState->Update(deltaTime);
	this->ConstraintInScreenBounds();
}

void Hero::ProcessGameObjectInput(const uint8_t* keyState)
{
	mCurrentState->HandleInput(keyState);
}

void Hero::DeactivateGameObject()
{
	rigidBodyComponent->SetActive(false);
}

void Hero::StartCooldown()
{
	GameObject::SetState(State::EDeactive);
}

bool Hero::IsMoving() const
{
	return inputComponent->GetForwardSpeed() != 0.0f;
}

bool Hero::IsDead() const
{
	return mHealth->IsDead();
}

void Hero::SetMoveDirection(Direction direction)
{
	inputComponent->SetDirection(direction);
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
	return inputComponent->GetDirection() == Direction::Left;
}

void Hero::Fire()
{
	mWeapon->Fire();
}

void Hero::ReceiveDamage(float amount)
{
	this->SetIsAttacked(true);
	mHealth->ReceiveDamage(amount);
}

bool Hero::IsAttacked() const
{
	return mIsAttacked;
}

void Hero::SetIsAttacked(bool isAttacked)
{
	mIsAttacked = isAttacked;	
}

void Hero::ChangeState(const std::string& name)
{
	if (mCurrentState != nullptr) mCurrentState->Exit();

	GameObjectState* state = mStateMap[name];

	if (state == nullptr) {
		SDL_Log("Cannot find state with name: {0}", name);
		return;
	}

	if (state != mCurrentState) {
		mCurrentState = state;
		mCurrentState->Enter();
	}
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