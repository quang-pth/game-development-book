#pragma once

#include<include/SpriteComponent.h>
#include<include/CustomMath.h>
#include <vector>

class BackgroundSpriteComponent : public SpriteComponent
{
public:
	BackgroundSpriteComponent(class GameObject* owner, int drawOrder = 10, 
		std::string name = "BackgroundSpriteComponent");
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetBackgroundTextures(const std::vector<SDL_Texture*>& textures, bool vertical = false, bool horizontal = false);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(Vector2 speed) { mScrollSpeed = speed; }
	Vector2 GetScrollSpeed() const { return mScrollSpeed; }
private:
	struct BackgroundTexture {
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BackgroundTexture> mBackgroundTextures;
	Vector2 mScreenSize;
	Vector2 mScrollSpeed;
};

