#include "include/TileDataComponent.h"
#include "include/TileMap.h"
#include "include/TransformComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include <iostream>

TileDataComponent::TileDataComponent(GameObject* mOwner, int updateOrder, const std::string& name) : 
	SpriteComponent(mOwner, updateOrder, name),
	mSrcTexture(nullptr), mSrcRect(), mDestRect(),
	mLayout(Vector2::Zero), mOffset(Vector2::Zero)
{

}

TileDataComponent::~TileDataComponent()
{

}

void TileDataComponent::Draw(SDL_Renderer* renderer)
{
	if (mSrcTexture == nullptr) return;

	mDestRect.x = static_cast<int>(mOwner->pTransform->GetPosition().x + mDestRect.w * mLayout.x - mOffset.x);
	mDestRect.y = static_cast<int>(mOwner->pTransform->GetPosition().y + mDestRect.h * mLayout.y - mOffset.y);
	SDL_RenderCopyEx(renderer, mSrcTexture, &mSrcRect,
		&mDestRect, -Math::ToDegrees(mOwner->pTransform->GetRotation()), nullptr, SDL_FLIP_NONE);
}

void TileDataComponent::SetData(const Vector2& dimension, const Vector2& srcPosition, const Vector2& layoutPosition)
{
	// Config source rect
	mSrcRect.w = static_cast<int>(dimension.x);
	mSrcRect.h = static_cast<int>(dimension.y);
	mSrcRect.x = static_cast<int>(srcPosition.x);
	mSrcRect.y = static_cast<int>(srcPosition.y);
	// Config destination rect
	mDestRect.w = static_cast<int>(dimension.x * mOwner->pTransform->GetScale());
	mDestRect.h = static_cast<int>(dimension.y * mOwner->pTransform->GetScale());
	mDestRect.x = static_cast<int>(mOwner->pTransform->GetPosition().x + mDestRect.w * layoutPosition.x);
	mDestRect.y = static_cast<int>(mOwner->pTransform->GetPosition().y + mDestRect.h * layoutPosition.y);

	mLayout = layoutPosition;
}

void TileDataComponent::SetOffset(const Vector2& offset)
{
	mOffset = offset;
}

void TileDataComponent::SetTexture(SDL_Texture* texture)
{
	mSrcTexture = texture;
}

Vector2 TileDataComponent::GetCurrentPosition()
{
	return Vector2(mDestRect.x, mDestRect.y);
}
