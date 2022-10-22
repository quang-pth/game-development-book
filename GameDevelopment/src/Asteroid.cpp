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
	GameObject::GetTransform()->SetPosition(randomPosition);

	float randomRotation = Random::GetFloatRange(0.0f, Math::TwoPi);
	GameObject::GetTransform()->SetRotation(randomRotation);

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
	TransformComponent* transform = GameObject::GetTransform();
	Game* game = GameObject::GetGame();
	float newXPos = transform->GetPosition().x;
	float newYPos = transform->GetPosition().y;

	if (transform->GetPosition().x > game->GetWindowWidth() + mSpriteComponent->GetTextureWidth()) {
		newXPos = -mSpriteComponent->GetTextureWidth();
	}
	else if (transform->GetPosition().x < 0.0f - mSpriteComponent->GetTextureWidth()) {
		newXPos = game->GetWindowWidth() + mSpriteComponent->GetTextureWidth();
	}

	if (transform->GetPosition().y > game->GetWindowHeight() + mSpriteComponent->GetTextureHeight()) {
		newYPos = -mSpriteComponent->GetTextureHeight();
	}
	else if (transform->GetPosition().y < 0.0f - mSpriteComponent->GetTextureHeight()) {
		newYPos = game->GetWindowHeight() + mSpriteComponent->GetTextureHeight();
	}

	transform->SetPosition(Vector2(newXPos, newYPos));
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
