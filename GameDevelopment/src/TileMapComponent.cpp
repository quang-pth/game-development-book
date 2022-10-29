#include "include/GameObject.h";
#include "include/TileMapComponent.h";
#include "include/TileDataComponent.h";
#include "include/TransformComponent.h";
#include "include/InputComponent.h";
#include "include/Game.h";
#include "include/Mario.h";
#include<fstream>
#include<sstream>
#include <iostream>
#include<string>

TileMapComponent::TileMapComponent(GameObject* owner, int drawOrder, std::string name)
	: SpriteComponent(owner, drawOrder, name),
	mTileWidth(16), mTileHeight(16),
	mTilePerRow(7), mOffset(Vector2::Zero), mXBound(0.0f),
	mState(EMovement::EMoveable)
{
}

void TileMapComponent::Update(float deltaTime)
{	
	if (mState == EMovement::EMoveable) {
		Mario* mario = mOwner->GetGame()->GetMario();
		Vector2 distance = mario->pTransform->GetPosition();
		Vector2 center = mOwner->GetGame()->GetCenterPoint();
	
		mOffset += mario->pInputComponent->GetVelocity() * deltaTime;
		
		if (mOffset.x > mXBound) {
			mOffset.x = mXBound;
		}
		else if (mOffset.x < 0.0f) {
			mOffset.x = 0.0f;
		}
	}
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	for (TileDataComponent* tileData : mTilesData) {
		tileData->SetOffset(mOffset);
		tileData->Draw(renderer);
	}
}

void TileMapComponent::Init(const char* filePath)
{
	this->SetTexture("MarioAssets/decorationsAndBlocks.png");
	this->LoadTileData(filePath);
}

void TileMapComponent::SetState(EMovement state)
{
	mState = state;
}

EMovement TileMapComponent::GetState() const
{
	return mState;
}

bool TileMapComponent::AtRightBounds()
{
	return mOffset.x >= mXBound;
}

bool TileMapComponent::AtLeftBounds()
{
	return mOffset.x <= 0;
}

void TileMapComponent::LoadTileData(const char* filePath)
{
	std::vector<std::vector<int>> tiles = std::vector<std::vector<int>>();
	std::ifstream fstream(filePath);
	std::string line;

	if (!fstream.is_open())
	{
		std::cout << "Could not open the file - '" << filePath << "'" << std::endl;
	}
	// Get tiles layout from csv file
	while (std::getline(fstream, line))
	{
		std::stringstream lineStream(line);
		std::string col;
		std::vector<int> row;

		while (std::getline(lineStream, col, ','))
		{
			row.push_back(stoi(col));
		}

		tiles.push_back(row);
	}
	mXBound = tiles[0].size() * mTileWidth * mOwner->pTransform->GetScale() - 
		mOwner->GetGame()->GetWindowWidth();
	// Generate tile data
	for (unsigned int row = 0; row < tiles.size(); row++) {
		for (unsigned int col = 0; col < tiles[row].size(); col++) {
			int tile = tiles[row][col];

			if (tile == -1) continue;

			TileDataComponent* tileData = new TileDataComponent(mOwner);
			Vector2 dimension = Vector2(mTileWidth, mTileHeight);
			Vector2 srcPosition = Vector2(mTileWidth * (tile % mTilePerRow),
				mTileHeight * (tile / mTilePerRow));
			Vector2 layout = Vector2(col, row);
			tileData->SetData(dimension, srcPosition, layout);
			mTilesData.emplace_back(tileData);
		}
	}
}

void TileMapComponent::SetTexture(const char* filePath)
{
	SDL_Texture* texture = this->mOwner->GetGame()->GetTexture(filePath);
	SpriteComponent::SetTexture(texture);
}