#pragma once

#include<include/SpriteComponent.h>
#include<include/CustomMath.h>

class BackgroundSpriteComponent : public SpriteComponent
{
public:
	BackgroundSpriteComponent(class Actor* owner, int drawOrder = 10);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetBackgroundTextures(const std::vector<SDL_Texture*>& textures);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	struct BackgroundTexture {
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BackgroundTexture> mBackgroundTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

