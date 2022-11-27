#include "Tile.h"

#include "include/Game.h"
#include "include/TileDataComponent.h"
#include "include/TransformComponent.h"
#include "include/RigidBodyComponent.h"
#include "include/CircleComponent.h"
#include "include/TileMap.h"
#include "include/CooldownManager.h"
#include "include/Unit.h"
#include <iostream>

Tile::Tile(Game* game, float scale, const std::string& name) :
	GameObject(game, name),
	mRigidBodyComponent(), mTileDataComponent()
{
	pTransform->SetScale(scale);
}

Tile::~Tile()
{
}

void Tile::UpdateGameObject(float deltaTime)
{
}

void Tile::SetTileData(const Vector2& dimension, const Vector2& srcPosition, 
	const Vector2& layout, SDL_Texture* texture)
{
	mTileDataComponent = new TileDataComponent(this);
	mTileDataComponent->SetData(dimension, srcPosition, layout);
	mTileDataComponent->SetTexture(texture);

	mRigidBodyComponent = new RigidBodyComponent(this);
	const Vector2& offsetPos = Vector2(dimension.x * pTransform->GetScale() * 0.5f, 0.0f);
	mRigidBodyComponent->SetPosition(mTileDataComponent->GetCurrentPosition() + offsetPos);
	mRigidBodyComponent->SetDimension(dimension * pTransform->GetScale() * 0.5f);
	mRigidBodyComponent->Init();
}

void Tile::Cooldown(float deltaTime)
{
	if (this->IsInBound()) {
		GameObject::SetState(State::EActive);
	}
	else {
		GameObject::SetState(State::EDeactive);
	}
}

Vector2 Tile::GetPosition() const
{
	return mTileDataComponent->GetCurrentPosition();
}

TileDataComponent* Tile::GetTileDataComponent() const
{
	return mTileDataComponent;
}

bool Tile::IsInBound()
{
	Vector2 position = mTileDataComponent->GetCurrentPosition();
	bool inBoundX = position.x >= 0 && position.x <= mGame->GetWindowWidth();
	bool inBoundY = position.y >= 0 && position.y <= mGame->GetWindowHeight();
	return inBoundX && inBoundY;
}
