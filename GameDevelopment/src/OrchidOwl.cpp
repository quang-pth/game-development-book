#include "OrchidOwl.h"

#include "include/Game.h"
#include "include/Animation.h"
#include "include/TransformComponent.h"
#include "include/AnimatorComponent.h"
#include "include/CircleComponent.h"

OrchidOwl::OrchidOwl(Game* game, const std::string& name) :
	Enemy(game, name)
{
	pTransform->SetPosition(Vector2(600.0f, 50.0f));
	pTransform->SetScale(1.5f);

	/*
	* ANIMATIONS
	*/
	// Walking
	std::vector<SDL_Texture*> runningTextures = {
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Running/tile000.png"),
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Running/tile001.png"),
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Running/tile002.png"),
	};
	std::shared_ptr<Animation> runningAnimation = std::make_shared<Animation>("Running", runningTextures);
	runningAnimation->SetFPS(10.0f);
	// Idle
	std::vector<SDL_Texture*> idleTextures = {
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Idle/tile000.png"),
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Idle/tile001.png"),
	};
	std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>("Idle", idleTextures);
	idleAnimation->SetFPS(1.5f);
	// Jump
	std::vector<SDL_Texture*> hurtTextures = {
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Hurt/tile000.png"),
	};
	std::shared_ptr<Animation> hurtAnimation = std::make_shared<Animation>("Hurt", hurtTextures, false);
	idleAnimation->SetFPS(1.5f);

	// mAnimator
	mAnimator->AddAnimation(runningAnimation);
	mAnimator->AddAnimation(idleAnimation);
	mAnimator->AddAnimation(hurtAnimation);
	mAnimator->SetAnimation(runningAnimation->name);

	mCircleComponent->SetRadius(16.0f * pTransform->GetScale());
}

OrchidOwl::~OrchidOwl()
{
}

void OrchidOwl::UpdateGameObject(float deltaTime)
{
}

void OrchidOwl::Cooldown(float deltaTime)
{
}
