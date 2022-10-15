#include "include/Ship.h"
#include "include/AnimatorComponent.h"
#include "include/Animation.h"
#include "include/Game.h"
#include "include/TransformComponent.h"

Ship::Ship(Game* game) : GameObject(game, "Ship"), mRightSpeed(0.0f), mDownSpeed(0.0f)
{
	mAnimator = new AnimatorComponent(this);
	// Walking 1 6
	std::string walkingName = "Walk";
	std::vector<SDL_Texture*> walkingTextures = {
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png"),
	};
	Animation* walkingAnimation = new Animation(walkingName, walkingTextures);
	walkingAnimation->SetFPS(8.0f);
	// Jumping 7 15
	std::string jumpingName = "Jump";
	std::vector<SDL_Texture*> jumpingTextures = {
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
		game->GetTexture("Assets/Character13.png"),
		game->GetTexture("Assets/Character14.png"),
		game->GetTexture("Assets/Character15.png"),
	};
	Animation* jumpingAnimation = new Animation(jumpingName, jumpingTextures, false);
	jumpingAnimation->SetFPS(24.0f);
	// Punch 16 18
	std::string punchName = "Punch";
	std::vector<SDL_Texture*> punchTextures = {
		game->GetTexture("Assets/Character16.png"),
		game->GetTexture("Assets/Character17.png"),
		game->GetTexture("Assets/Character18.png"),
	};
	Animation* punchAnimation = new Animation(punchName, punchTextures, false);
	punchAnimation->SetFPS(9.0f);

	mAnimator->AddAnimation(walkingName, walkingAnimation);
	mAnimator->AddAnimation(jumpingName, jumpingAnimation);
	mAnimator->AddAnimation(punchName, punchAnimation);
	mAnimator->SetAnimation(walkingName);
}

void Ship::UpdateGameObject(float deltaTime)
{
	Vector2 position = GetTransform()->GetPosition();
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

	GetTransform()->SetPosition(position);
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
