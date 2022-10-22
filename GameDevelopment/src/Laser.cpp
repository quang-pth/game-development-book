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
