#include "include/Laser.h"
#include "include/Game.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/CircleComponent.h"
#include "include/TransformComponent.h"
#include "include/Asteroid.h"
#include "include/Ship.h"
#include "include/Texture.h"
#include "include/Renderer.h"
#include <iostream>

Laser::Laser(Game* game, std::string name) : 
	GameObject(game, name)
{
	mMoveComponent = new MoveComponent(this);
	GameObject::GetTransform()->SetScale(0.3f);

	mSpriteComponent = new SpriteComponent(this);
	mSpriteComponent->SetTexture(GameObject::GetGame()->GetRenderer()->GetTexture("Assets/Chapter3/Laser.png"));

	mCircleComponent = new CircleComponent(this);
	mCircleComponent->SetRadius(mSpriteComponent->GetTextureWidth() - 3.0f);
}

void Laser::UpdateGameObject(float deltaTime)
{
	//std::vector<Asteroid*> asteroids = GameObject::GetGame()->GetAsteroids();
	//for (Asteroid* asteriod : asteroids) {
	//	if (asteriod->GetState() == GameObject::State::EActive) {
	//		bool isIntersect = CircleComponent::IsIntersect(this->mCircleComponent, 
	//			asteriod->GetCircleComponent());
	//		if (isIntersect) {
	//			asteriod->SetState(GameObject::State::EDeactive);
	//			GameObject::SetState(GameObject::State::EDeactive);
	//			mMoveComponent->ResetForce();
	//			break;
	//		}
	//	}
	//}
	// Deactivate the laser if out of screen bounds
	/*float xBound = GameObject::GetGame()->GetWindowWidth() / 2.0f + mSpriteComponent->GetTextureWidth();
	float yBound = GameObject::GetGame()->GetWindowHeight() / 2.0f + mSpriteComponent->GetTextureHeight();
	Vector3 position = GameObject::GetTransform()->GetPosition();
	if (position.x < -xBound || position.x > xBound) {
		GameObject::SetState(GameObject::State::EDeactive);
		mMoveComponent->ResetForce();
	}
	if (position.y < -yBound || position.y > yBound) {
		GameObject::SetState(GameObject::State::EDeactive);
		mMoveComponent->ResetForce();
	}*/
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
