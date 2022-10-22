#include "include/Laser.h"
#include "include/Game.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/CircleComponent.h"
#include "include/TransformComponent.h"
#include "include/Asteroid.h"
#include "include/Mario.h"
#include <iostream>

Laser::Laser() : GameObject(), mMoveComponent(), mSpriteComponent(), mCircleComponent()
{
}

Laser::Laser(Game* game, std::string name) : 
	GameObject(game, name)
{
	mMoveComponent = new MoveComponent(this);

	mSpriteComponent = new SpriteComponent(this);
	mSpriteComponent->SetTexture(GameObject::GetGame()->GetTexture("Assets/Chapter3/Laser.png"));

	mCircleComponent = new CircleComponent(this);
	mCircleComponent->SetRadius(mSpriteComponent->GetTextureWidth() - 3.0f);
}

void Laser::UpdateGameObject(float deltaTime)
{
	std::vector<Asteroid*> asteroids = GameObject::GetGame()->GetAsteroids();
	for (Asteroid* asteriod : asteroids) {
		if (asteriod->GetState() == GameObject::State::EActive) {
			bool isIntersect = CircleComponent::IsIntersect(this->mCircleComponent, 
				asteriod->GetCircleComponent());
			if (isIntersect) {
				asteriod->SetState(GameObject::State::EDeactive);
				GameObject::SetState(GameObject::State::EDeactive);
				mMoveComponent->ResetForce();
				break;
			}
		}
	}
	// Deactivate the laser if out of screen bounds
	Vector2 position = GameObject::GetTransform()->GetPosition();
	if (position.x < -mSpriteComponent->GetTextureWidth() || 
		position.x > GameObject::GetGame()->GetWindowWidth() + mSpriteComponent->GetTextureWidth()) {
		GameObject::SetState(GameObject::State::EDeactive);
		mMoveComponent->ResetForce();
	}
	if (position.y < -mSpriteComponent->GetTextureHeight() || 
		position.y > GameObject::GetGame()->GetWindowHeight() + mSpriteComponent->GetTextureHeight()) {
		GameObject::SetState(GameObject::State::EDeactive);
		mMoveComponent->ResetForce();
	}
}

MoveComponent* Laser::GetMoveComponent() const
{
	return mMoveComponent;
}

SpriteComponent* Laser::GetSpriteComponent() const
{
	return mSpriteComponent;
}

CircleComponent* Laser::GetCircleComponent() const
{
	return mCircleComponent;
}
