#include "include/Mario.h"
#include "include/AnimatorComponent.h"
#include "include/Animation.h"
#include "include/Game.h"

Mario::Mario(Game* game) : GameObject(game), mRightSpeed(0.0f), mDownSpeed(0.0f)
{
	mAnimator = new AnimatorComponent(this);
	std::string walkingName = "Walk";
	std::vector<SDL_Texture*> walkingTextures = {
		game->GetTexture("MarioAssets/mario-1.png"),
		game->GetTexture("MarioAssets/mario-2.png"),
		game->GetTexture("MarioAssets/mario-3.png"),
		game->GetTexture("MarioAssets/mario-4.png"),
	};
	Animation* walkingAnimation = new Animation(walkingName, walkingTextures);
	walkingAnimation->SetFPS(8.0f);
	
	mAnimator->AddAnimation(walkingName, walkingAnimation);
	mAnimator->SetAnimation(walkingName);
}

void Mario::UpdateGameObject(float deltaTime)
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

void Mario::ProcesKeyboard(const uint8_t* state)
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
	// State controller
	if (state[SDL_SCANCODE_SPACE]) {
		mAnimator->SetAnimation("Jump");
	}
	if (state[SDL_SCANCODE_Q]) {
		mAnimator->SetAnimation("Punch");
	}	
	if (state[SDL_SCANCODE_E]) {
		mAnimator->SetAnimation("Walk");
	}
}
