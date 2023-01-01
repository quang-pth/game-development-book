#pragma once

#include<SDL2/SDL.h>
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(class GameObject* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);
	int GetDrawOrder() const { return mDrawOrder; }
	inline int GetTextureWidth() const { return mTextureWidth; }
	inline int GetTextureHeight() const { return mTextureHeight; }
	inline void SetVisible(bool visible) { mVisible = visible; }
	inline const bool& GetVisible() const { return mVisible; }
protected:
	class Texture* mTexture;
	int mDrawOrder;
	int mTextureWidth;
	int mTextureHeight;
	bool mVisible;
};

