#include "include/StateManager.h"
#include "include/Game.h"
#include "include/Mario.h"
#include "include/TileMap.h"
#include "include/TransformComponent.h"
#include "include/InputComponent.h"
#include "include/CustomMath.h"
#include "include/Enums.h"
#include<iostream>

StateManager::StateManager(Game* game, const std::string& name) : GameObject(game, name)
{
	mpMario = game->GetMario();
	mpTileMap = game->GetTileMap();
}

StateManager::~StateManager()
{
}

void StateManager::UpdateGameObject(float deltaTime)
{
	if (mpTileMap->AtLeftBounds()) {
		this->SetMoveMario();
		if (mpMario->MoveExceedCenterPoint(true)) {
			this->SetMoveTilemap();
		}
	}
	else if (mpTileMap->AtRightBounds()) {
		this->SetMoveMario();
		if (mpMario->MoveExceedCenterPoint(false)) {
			this->SetMoveTilemap();
		}
	}
}

void StateManager::SetMoveMario()
{
	mpMario->GetInputComponent()->SetState(EMovement::EMoveable);
	mpTileMap->SetState(EMovement::EUnMoveable);
}

void StateManager::SetMoveTilemap()
{
	mpMario->GetInputComponent()->SetState(EMovement::EUnMoveable);
	mpTileMap->SetState(EMovement::EMoveable);
}

bool StateManager::TileMapCanMove()
{
	return false;
}
