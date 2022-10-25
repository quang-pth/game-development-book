#pragma once

#include<memory>
#include<SDL2/SDL.h>
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent();
	SpriteComponent(class GameObject* owner, int drawOrder = 100, std::string = "SpriteComponent");
	virtual ~SpriteComponent();
	
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture, bool flipX = false);
	void FlipTexture(bool isFlip);
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTextureWidth() const { return mTextureWidth; }
	int GetTextureHeight() const { return mTextureHeight; }
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTextureWidth;
	int mTextureHeight;
	bool mFlipX;
};

