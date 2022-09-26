#include "include/Ship.h"
#include "include/AnimationSpriteComponent.h"
#include "include/Game.h"

Ship::Ship(Game* game) : Actor(game), mRightSpeed(0.0f), mDownSpeed(0.0f)
{
	AnimationSpriteComponent* animationSpriteComponent = new AnimationSpriteComponent(this);
	std::vector<SDL_Texture*> shipTextures = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	animationSpriteComponent->SetAnimationTextures(shipTextures);
}

void Ship::UpdateActor(float deltaTime)
{
	Vector2 position = GetPosition();
	position.x += mRightSpeed * deltaTime;
	position.y += mDownSpeed * deltaTime;
	if (position.x < 4.0f) {
		position.x = 4.0f;
	}
	if (position.x > 796.0f) {
		position.x = 796.0f;
	}
	if (position.y < 4.0f) {
		position.y = 4.0f;
	}
	if (position.y > 598.0f) {
		position.y = 598.0f;
	}
	SetPosition(position);
}

void Ship::ProcesKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	if (state[SDL_SCANCODE_D]) {
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A]) {
		mRightSpeed -= 250.0f;
	}
	if (state[SDL_SCANCODE_W]) {
		mDownSpeed -= 250.0f;
	}
	if (state[SDL_SCANCODE_S]) {
		mDownSpeed += 250.0f;
	}
}
