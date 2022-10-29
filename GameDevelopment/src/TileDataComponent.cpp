#include "include/TileDataComponent.h"
#include "include/TilemapComponent.h"
#include "include/TransformComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"

TileDataComponent::TileDataComponent(GameObject* mOwner, int updateOrder, const std::string& name) : 
	SpriteComponent(mOwner, updateOrder, name),
	mDimension(Vector2::Zero), mSrcPosition(Vector2::Zero), mSrcTexture()
{
	mSrcTexture = mOwner->GetGame()->GetTileMapComponent()->GetTexture();
}

TileDataComponent::~TileDataComponent()
{
}

void TileDataComponent::Draw(SDL_Renderer* renderer)
{
	if (mSrcTexture == nullptr) return;

	SDL_Rect srcrect;
	srcrect.w = static_cast<int>(mDimension.x);
	srcrect.h = static_cast<int>(mDimension.y);
	srcrect.x = static_cast<int>(mSrcPosition.x);
	srcrect.y = static_cast<int>(mSrcPosition.y);

	SDL_Rect destrect;
	destrect.w = static_cast<int>(mDimension.x * mOwner->pTransform->GetScale());
	destrect.h = static_cast<int>(mDimension.y * mOwner->pTransform->GetScale());
	destrect.x = static_cast<int>(mOwner->pTransform->GetPosition().x + destrect.w * mLayoutPosition.x - mOffset.x);
	destrect.y = static_cast<int>(mOwner->pTransform->GetPosition().y + destrect.h * mLayoutPosition.y - mOffset.y);

	SDL_RenderCopyEx(renderer, mSrcTexture, &srcrect,
		&destrect, -Math::ToDegrees(mOwner->pTransform->GetRotation()), nullptr, SDL_FLIP_NONE);
}

void TileDataComponent::SetData(const Vector2& dimension, const Vector2& srcPosition, const Vector2& layoutPosition)
{
	mDimension = dimension;
	mSrcPosition = srcPosition;
	mLayoutPosition = layoutPosition;
}

void TileDataComponent::SetOffset(const Vector2& offset)
{
	mOffset = offset;
}
