#include "include/Ship.h"
#include "include/Game.h"
#include "include/TransformComponent.h"
#include "include/SpriteComponent.h"
#include "include/InputComponent.h"

Ship::Ship(Game* game) : GameObject(game, "Ship"), mRightSpeed(0.0f), mDownSpeed(0.0f)
{
	GetTransform()->SetPosition(Vector2(game->GetWindowWidth() / 2, game->GetWindowHeight() / 2));

	mSpriteComponent = new SpriteComponent(this);
	mSpriteComponent->SetTexture(game->GetTexture("Assets/Chapter3/Ship.png"));

	mInputComponent = new InputComponent(this);
}

void Ship::UpdateGameObject(float deltaTime)
{
	TransformComponent* transform = GameObject::GetTransform();
	float newXPos = transform->GetPosition().x;
	float newYPos = transform->GetPosition().y;

	if (transform->GetPosition().x > GetGame()->GetWindowWidth()) {
		newXPos = GetGame()->GetWindowWidth();
	}
	else if (transform->GetPosition().x < 0.0f) {
		newXPos = 0.0f;
	}

	if (transform->GetPosition().y > GetGame()->GetWindowHeight()) {
		newYPos = GetGame()->GetWindowHeight();
	}
	else if (transform->GetPosition().y < 0.0f) {
		newYPos = 0.0f;
	}

	transform->SetPosition(Vector2(newXPos, newYPos));
}
