#include "include/SpriteComponent.h"
#include "include/CustomMath.h"
#include "include/Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component(owner), mTexture(nullptr),
		mDrawOrder(drawOrder), mTextureWidth(0), mTextureHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture == nullptr) return;

	SDL_Rect rect;
	rect.w = static_cast<int>(mTextureWidth * mOwner->GetScale());
	rect.h = static_cast<int>(mTextureHeight * mOwner->GetScale());
	rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2.0f);
	rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2.0f);
	
	SDL_RenderCopyEx(renderer, mTexture, nullptr,
		&rect, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}
