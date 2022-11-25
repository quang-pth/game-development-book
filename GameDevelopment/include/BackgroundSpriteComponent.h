#pragma once

#include<include/SpriteComponent.h>
#include<include/CustomMath.h>
#include <vector>

class BackgroundSpriteComponent : public SpriteComponent
{
public:
	BackgroundSpriteComponent(class GameObject* owner, int drawOrder = 10);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void Draw(class Shader* shader) override;
	void SetBackgroundTextures(const std::vector<class Texture*>& textures);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	struct BackgroundTexture {
		class Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BackgroundTexture> mBackgroundTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

