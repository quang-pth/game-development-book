#include "include/BackgroundSpriteComponent.h"

BackgroundSpriteComponent::BackgroundSpriteComponent(GameObject* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder), mScrollSpeed(0.0f)
{
}

void BackgroundSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& texture : mBackgroundTextures) {
		texture.mOffset.x += mScrollSpeed * deltaTime;
		if (texture.mOffset.x < -mScreenSize.x) {
			texture.mOffset.x = (mBackgroundTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BackgroundSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& texture : mBackgroundTextures) {
		SDL_Rect rect;
		rect.w = static_cast<int>(mScreenSize.x);
		rect.h = static_cast<int>(mScreenSize.y);
		rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2.0f + texture.mOffset.x);
		rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2.0f + texture.mOffset.y);

		SDL_RenderCopy(renderer, texture.mTexture, nullptr, &rect);
	}
}

void BackgroundSpriteComponent::SetBackgroundTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto texture : textures) {
		BackgroundTexture tempTexture;
		tempTexture.mTexture = texture;
		tempTexture.mOffset.x = count * mScreenSize.x;
		tempTexture.mOffset.y = 0;
		mBackgroundTextures.emplace_back(tempTexture);
		count++;
	}
}
