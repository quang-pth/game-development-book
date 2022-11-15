#include "Tile.h"

#include "include/Game.h"
#include "include/TileDataComponent.h"
#include "include/TransformComponent.h"
#include "include/RigidBodyComponent.h"
#include "include/TileMap.h"
#include "include/CooldownManager.h"
#include "include/Unit.h"
#include <iostream>

Tile::Tile(Game* game, const std::string& name) :
	GameObject(game, name),
	mRigidBodyComponent(), mTileDataComponent()
{
	pTransform->SetScale(2.0f);
	game->GetCooldownManager()->Observe(this);
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
	mRigidBodyComponent->SetPosition(mTileDataComponent->GetCurrentPosition());
	mRigidBodyComponent->SetDimension(Vector2(8.0f * pTransform->GetScale(), 8.0f * pTransform->GetScale()));
	mRigidBodyComponent->Init();
}

void Tile::Cooldown(float deltaTime)
{
	if (this->IsInBound()) {
		GameObject::SetState(GameObject::State::EActive);
	}
	else {
		GameObject::SetState(GameObject::State::EDeactive);
	}
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
