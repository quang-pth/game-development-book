#include "include/GameObject.h"
#include "include/TransformComponent.h"
#include "include/BackgroundSpriteComponent.h"

BackgroundSpriteComponent::BackgroundSpriteComponent(GameObject* owner, int drawOrder, std::string name) :
	SpriteComponent(owner, drawOrder, name), mScrollSpeed(Vector2::Zero)
{
}

void BackgroundSpriteComponent::Update(float deltaTime)
{
	for (auto& texture : mBackgroundTextures) {
		texture.mOffset += mScrollSpeed * deltaTime;
		if (texture.mOffset.x < -mScreenSize.x) {
			texture.mOffset.x = (mBackgroundTextures.size() - 1) * mScreenSize.x - 1;
		}
		if (texture.mOffset.y > mScreenSize.y) {
			texture.mOffset.y = -((mBackgroundTextures.size() - 1) * mScreenSize.y - 1);
		}
	}
}

void BackgroundSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& texture : mBackgroundTextures) {
		SDL_Rect rect;
		rect.w = static_cast<int>(mScreenSize.x);
		rect.h = static_cast<int>(mScreenSize.y);
		rect.x = static_cast<int>(mOwner->pTransform->GetPosition().x - rect.w / 2.0f + texture.mOffset.x);
		rect.y = static_cast<int>(mOwner->pTransform->GetPosition().y - rect.h / 2.0f + texture.mOffset.y);

		SDL_RenderCopy(renderer, texture.mTexture, nullptr, &rect);
	}
}

void BackgroundSpriteComponent::SetBackgroundTextures(const std::vector<SDL_Texture*>& textures, bool vertical, bool horizontal)
{
	int count = 0;
	for (auto texture : textures) {
		BackgroundTexture tempTexture;
		tempTexture.mTexture = texture;
		tempTexture.mOffset.x = count * mScreenSize.x * horizontal;
		tempTexture.mOffset.y = count * mScreenSize.y * (-1) * vertical;
		mBackgroundTextures.emplace_back(tempTexture);
		count++;
	}
}
