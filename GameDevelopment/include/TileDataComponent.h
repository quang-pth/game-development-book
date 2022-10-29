#pragma once

#include"include/SpriteComponent.h"
#include"include/CustomMath.h"

class TileDataComponent : public SpriteComponent
{
public:
	TileDataComponent(class GameObject* mOwner, int updateOrder = 100, const std::string& name = "TileDataComponent");
	~TileDataComponent();
	void Draw(SDL_Renderer* renderer) override;
	void SetData(const Vector2& dimension, const Vector2& position, const Vector2& layout);
	void SetOffset(const Vector2& offset);
private:
	SDL_Texture* mSrcTexture;
	Vector2 mDimension;
	Vector2 mSrcPosition;
	Vector2 mLayoutPosition;
	Vector2 mOffset;
};

