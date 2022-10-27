#include "include/StateManager.h"
#include "include/Game.h"
#include "include/Mario.h"
#include "include/TileMapComponent.h"
#include "include/TransformComponent.h"
#include "include/InputComponent.h"
#include "include/CustomMath.h"
#include "include/Enums.h"
#include<iostream>

StateManager::StateManager(Game* game, std::string name) : GameObject(game, name)
{
	mMario = game->GetMario();
	mTileMapComponent = game->GetTileMapComponent();
}

StateManager::~StateManager()
{
}

void StateManager::UpdateGameObject(float deltaTime)
{
	if (mTileMapComponent->AtLeftBounds()) {
		this->SetMoveMario();
		if (mMario->MoveRightExceedCenterPoint()) {
			this->SetMoveTilemap();
		}
	}
	else if (mTileMapComponent->AtRightBounds()) {
		this->SetMoveMario();
		if (mMario->MoveLeftExceedCenterPoint()) {
			this->SetMoveTilemap();
		}
	}
}

void StateManager::SetMoveMario()
{
	mMario->GetInputComponent()->SetState(EMovement::EMoveable);
	mTileMapComponent->SetState(EMovement::EUnMoveable);
}

void StateManager::SetMoveTilemap()
{
	mMario->GetInputComponent()->SetState(EMovement::EUnMoveable);
	mTileMapComponent->SetState(EMovement::EMoveable);
}

bool StateManager::TileMapCanMove()
{
	return false;
}
