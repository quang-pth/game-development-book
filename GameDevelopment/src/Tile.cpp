#include "Tile.h"

#include "include/Game.h"
#include "include/TileDataComponent.h"
#include "include/TransformComponent.h"
#include "include/CooldownManager.h"

Tile::Tile(Game* game, const std::string& name) :
	GameObject(game, name)
{
	mpTileData = new TileDataComponent(this);
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
		mpTileData = data;
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
	return mpTileData;
}

bool Tile::IsInBound()
{
	Vector2 position = mpTileData->GetCurrentPosition();
	bool inBoundX = position.x >= 0 && position.x <= mpGame->GetWindowWidth();
	bool inBoundY = position.y >= 0 && position.y <= mpGame->GetWindowHeight();
	return inBoundX && inBoundY;
}
