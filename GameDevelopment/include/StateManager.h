#pragma once

#include"include/GameObject.h"

class StateManager : public GameObject
{
public:
	StateManager(class Game* game, const std::string& name = "StateManger");
	~StateManager();
	void UpdateGameObject(float deltaTime) override;
private:
	void SetMoveMario();
	void SetMoveTilemap();
	bool TileMapCanMove();
	class Mario* mMario;
	class TileMapComponent* mTileMapComponent;
};

