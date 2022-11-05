#pragma once

#include"include/GameObject.h"
#include"include/ICooldownable.h"
#include<SDL2/SDL.h>

class Tile : public GameObject, ICooldownable
{
public:
	Tile(class Game* game, class TileDataComponent* tileDataComponent, const std::string& name = "Tile");
	~Tile();
	void UpdateGameObject(float deltaTime) override;
	void SetTileData(class TileDataComponent* data);
	void Cooldown(float deltaTime) override;
	class TileDataComponent* GetTileDataComponent() const;
private:
	bool IsInBound();
	class TileDataComponent* mTileDataComponent;
	class RigidBodyComponent* mRigidBodyComponent;
};

