#include "include/GameObject.h";
#include "include/TileMapComponent.h";
#include "include/TransformComponent.h";
#include "include/Game.h";
#include<fstream>
#include<sstream>
#include <iostream>
#include<string>

TileMapComponent::TileMapComponent(GameObject* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder), mTileWidth(32), mTileHeight(32), mTilePerRow(8)
{

}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture == nullptr) return;

	for (unsigned int row = 0; row < mTilesData.size(); row++) {
		for (unsigned int col = 0; col < mTilesData[row].size(); col++) {
			int tile = mTilesData[row][col];
			
			if (tile == -1) continue;

			SDL_Rect srcrect;
			srcrect.w = static_cast<int>(mTileWidth);
			srcrect.h = static_cast<int>(mTileHeight);
			srcrect.x = static_cast<int>(mTileWidth * (tile % mTilePerRow));
			srcrect.y = static_cast<int>(mTileHeight * (tile / mTilePerRow));

			SDL_Rect destrect;
			destrect.w = static_cast<int>(mTileWidth * mOwner->GetTransform()->GetScale());
			destrect.h = static_cast<int>(mTileHeight * mOwner->GetTransform()->GetScale());
			destrect.x = static_cast<int>(mOwner->GetTransform()->GetPosition().x + destrect.w * col);
			destrect.y = static_cast<int>(mOwner->GetTransform()->GetPosition().y + destrect.h * row);

			SDL_RenderCopyEx(renderer, mTexture, &srcrect,
				&destrect, -Math::ToDegrees(mOwner->GetTransform()->GetRotation()), nullptr, SDL_FLIP_NONE);
		}
	}
}

void TileMapComponent::Init(const char* filePath)
{
	this->LoadTileData(filePath);
	this->SetTexture("Assets/Tiles.png");
}

void TileMapComponent::LoadTileData(const char* filePath)
{
	std::ifstream fstream(filePath);
	std::string line;

	if (!fstream.is_open())
	{
		std::cout << "Could not open the file - '" << filePath << "'" << std::endl;
	}

	while (std::getline(fstream, line))
	{
		std::stringstream lineStream(line);
		std::string col;
		std::vector<int> row;

		while (std::getline(lineStream, col, ','))
		{
			row.push_back(stoi(col));
		}

		mTilesData.push_back(row);
	}
}

void TileMapComponent::SetTexture(const char* filePath)
{
	SDL_Texture* texture = this->mOwner->GetGame()->GetTexture(filePath);
	SpriteComponent::SetTexture(texture);
}

void TileMapComponent::CheckTileMapContent(const char* filePath)
{
	std::cout << "================================" << std::endl;
	std::cout << "TILEMAP CONTENT: " << filePath << std::endl;
	std::cout << "================================" << std::endl;
	for (unsigned int row = 0; row < mTilesData.size(); row++) {
		for (unsigned int col = 0; col < mTilesData[row].size(); col++) {
			std::cout << mTilesData[row][col] << " ";
		}
		std::cout << std::endl;
	}
}
