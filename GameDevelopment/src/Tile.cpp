#include "Tile.h"

#include "include/Game.h"
#include "include/TileDataComponent.h"
#include "include/TransformComponent.h"
#include "include/RigidBodyComponent.h"
#include "include/CooldownManager.h"
#include "include/Unit.h"
#include <iostream>

Tile::Tile(Game* game, TileDataComponent* tileDataComponent, const std::string& name) :
	GameObject(game, name),
	mRigidBodyComponent()
{
	mTileDataComponent = new TileDataComponent(this);
	this->SetTileData(tileDataComponent);
	game->GetCooldownManager()->Observe(this);
}

Tile::~Tile()
{
}

void Tile::UpdateGameObject(float deltaTime)
{
}

void Tile::SetTileData(TileDataComponent* data)
{
	if (data != nullptr) {
		mTileDataComponent = data;
		mRigidBodyComponent = new RigidBodyComponent(this);
		mRigidBodyComponent->SetPosition(mTileDataComponent->GetCurrentPosition());
		mRigidBodyComponent->SetDimension(Vector2(8.0f, 8.0f));
		mRigidBodyComponent->Init();
	}
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
