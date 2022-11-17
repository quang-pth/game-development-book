#include "include/TileMap.h";
#include "include/TileDataComponent.h";
#include "include/Tile.h";
#include "include/TransformComponent.h";
#include "include/InputComponent.h";
#include "include/Game.h";
#include "include/Mario.h";
#include "include/Unit.h";
#include<fstream>
#include<sstream>
#include <iostream>
#include<string>

TileMap::TileMap(Game* game, const std::string& name) : 
	GameObject(game, name), mTexture(),
	mTileWidth(TILE_SIZE), mTileHeight(TILE_SIZE),
	mTilePerRow(7), mOffset(Vector2::Zero), mXBound(0.0f),
	mState(EMovement::EMoveable), mScale(1.0f)
{
}

void TileMap::UpdateGameObject(float deltaTime)
{
	Hero* mario = GameObject::GetGame()->GetHero();
	Vector2 distance = mario->pTransform->GetPosition();
	Vector2 center = GameObject::GetGame()->GetCenterPoint();

	for (Tile* tile : mTiles) {
		tile->GetTileDataComponent()->SetOffset(mOffset);
	}
}

void TileMap::Init(const char* srcTextureFilePath, const char* layoutFilePath)
{
	this->SetTexture(srcTextureFilePath);
	this->LoadTileData(layoutFilePath);
}

void TileMap::SetState(EMovement state)
{
	mState = state;
}

void TileMap::SetScale(float scale)
{
	mScale = scale;
}

void TileMap::SetTileDimension(const Vector2& dimension)
{
	mTileWidth = dimension.x;
	mTileHeight = dimension.y;
}

float TileMap::GetTileWidth() const
{
	return mTileWidth;
}

float TileMap::GetTileHeight() const
{
	return mTileHeight;
}

void TileMap::SetTilePerRow(unsigned int numOfTiles)
{
	mTilePerRow = numOfTiles;
}

EMovement TileMap::GetState() const
{
	return mState;
}

bool TileMap::AtRightBounds()
{
	return mOffset.x >= mXBound;
}

bool TileMap::AtLeftBounds()
{
	return mOffset.x <= 0;
}

void TileMap::LoadTileData(const char* filePath)
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
	mXBound = tiles[0].size() * mTileWidth * pTransform->GetScale() -
		GameObject::GetGame()->GetWindowWidth();
	// Generate tile data
	for (unsigned int row = 0; row < tiles.size(); row++) {
		for (unsigned int col = 0; col < tiles[row].size(); col++) {
			int index = tiles[row][col];

			if (index == -1) continue;

			const Vector2& dimension = Vector2(mTileWidth, mTileHeight);
			// Setup tile data
			const Vector2& srcPosition = Vector2(mTileWidth * (index % mTilePerRow),
				mTileHeight * (index / mTilePerRow));
			const Vector2& layout = Vector2(col, row);
			// Create tile game object
			Tile* tile = new Tile(GameObject::GetGame(), mScale);
			tile->SetTileData(dimension, srcPosition, layout, mTexture);

			mTiles.emplace_back(tile);
		}
	}
}

void TileMap::SetTexture(const char* filePath)
{
	mTexture = GameObject::GetGame()->GetTexture(filePath);
}
