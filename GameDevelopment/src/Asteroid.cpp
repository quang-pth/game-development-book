#include "include/Game.h"
#include "include/Asteroid.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/TransformComponent.h"
#include "include/CircleComponent.h"
#include "include/Texture.h"
#include "include/CustomMath.h"
#include "include/Random.h"

Asteroid::Asteroid(Game* game, std::string name) : GameObject(game, name)
{
	Vector3 randomPosition = Random::GetVector(Vector3::Zero, 
		Vector3(game->GetWindowWidth(), game->GetWindowHeight(), 0.0f));
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
	float boundX = game->GetWindowWidth() * 0.5f + mSpriteComponent->GetTextureWidth();
	float boundY = game->GetWindowHeight() * 0.5f + mSpriteComponent->GetTextureHeight();

	if (transform->GetPosition().x > boundX) {
		newXPos = -boundX;
	}
	else if (transform->GetPosition().x < -boundX) {
		newXPos = boundX;
	}

	if (transform->GetPosition().y > boundY) {
		newYPos = -boundY;
	}
	else if (transform->GetPosition().y < -boundY) {
		newYPos = boundY;
	}

	transform->SetPosition(Vector3(newXPos, newYPos, 0.0f));
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
