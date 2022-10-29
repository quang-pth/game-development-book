#include "include/GameObject.h"
#include "include/SpriteComponent.h"
#include "include/TransformComponent.h"
#include "include/CustomMath.h"
#include "include/Game.h"
#include <iostream>

SpriteComponent::SpriteComponent() :
	mDrawOrder(), mTexture(),
	mTextureWidth(), mTextureHeight(), mFlipX()
{
}

SpriteComponent::SpriteComponent(GameObject* owner, int drawOrder, std::string name) : 
	Component(owner, drawOrder, name), mTexture(nullptr),
	mDrawOrder(drawOrder), mTextureWidth(0), mTextureHeight(0), mFlipX(false)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture == nullptr || mOwner->GetState() == GameObject::State::EDeactive) return;

	SDL_Rect rect;
	rect.w = static_cast<int>(mTextureWidth * mOwner->pTransform->GetScale());
	rect.h = static_cast<int>(mTextureHeight * mOwner->pTransform->GetScale());
	rect.x = static_cast<int>(mOwner->pTransform->GetPosition().x - rect.w / 2.0f);
	rect.y = static_cast<int>(mOwner->pTransform->GetPosition().y - rect.h / 2.0f);
	
	if (mFlipX) {
		SDL_RenderCopyEx(renderer, mTexture, nullptr,
			&rect, -Math::ToDegrees(mOwner->pTransform->GetRotation()), nullptr, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopyEx(renderer, mTexture, nullptr,
			&rect, -Math::ToDegrees(mOwner->pTransform->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture, bool flipX)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}

SDL_Texture* SpriteComponent::GetTexture() const
{
	return mTexture;
}

void SpriteComponent::FlipTexture(bool isFlip) {
	mFlipX = isFlip;
}