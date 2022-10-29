#include "include/Game.h"
#include "include/Asteroid.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/TransformComponent.h"
#include "include/CircleComponent.h"
#include "include/CustomMath.h"
#include "include/Random.h"

Asteroid::Asteroid(Game* game, std::string name) : GameObject(game, name)
{
	Vector2 randomPosition = Random::GetVector(Vector2::Zero, 
		Vector2(game->GetWindowWidth(), game->GetWindowHeight()));
	pTransform->SetPosition(randomPosition);

	float randomRotation = Random::GetFloatRange(0.0f, Math::TwoPi);
	pTransform->SetRotation(randomRotation);

	mMoveComponent = new MoveComponent(this);
	mMoveComponent->AddForce(GameObject::GetForward() * 1000.0f, MoveComponent::ForceMode::Impulse);
	mSpriteComponent = new SpriteComponent(this, 20);
	mSpriteComponent->SetTexture(game->GetTexture("Assets/Chapter3/Asteroid.png"));
	
	mCircleComponent = new CircleComponent(this);
	mCircleComponent->SetRadius(mSpriteComponent->GetTextureWidth() - 10.0f);
}

Asteroid::~Asteroid()
{

}

void Asteroid::UpdateGameObject(float deltaTime)
{
	Game* game = GameObject::GetGame();
	float newXPos = pTransform->GetPosition().x;
	float newYPos = pTransform->GetPosition().y;

	if (pTransform->GetPosition().x > game->GetWindowWidth() + mSpriteComponent->GetTextureWidth()) {
		newXPos = -mSpriteComponent->GetTextureWidth();
	}
	else if (pTransform->GetPosition().x < 0.0f - mSpriteComponent->GetTextureWidth()) {
		newXPos = game->GetWindowWidth() + mSpriteComponent->GetTextureWidth();
	}

	if (pTransform->GetPosition().y > game->GetWindowHeight() + mSpriteComponent->GetTextureHeight()) {
		newYPos = -mSpriteComponent->GetTextureHeight();
	}
	else if (pTransform->GetPosition().y < 0.0f - mSpriteComponent->GetTextureHeight()) {
		newYPos = game->GetWindowHeight() + mSpriteComponent->GetTextureHeight();
	}

	pTransform->SetPosition(Vector2(newXPos, newYPos));
}

MoveComponent* Asteroid::GetMoveComponent() const
{
	return mMoveComponent;
}

SpriteComponent* Asteroid::GetSpriteComponent() const
{
	return mSpriteComponent;
}

CircleComponent* Asteroid::GetCircleComponent() const
{
	return mCircleComponent;
}
