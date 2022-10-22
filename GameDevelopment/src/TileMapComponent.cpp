#include "include/TileMapComponent.h";
#include "include/Game.h";
#include<fstream>
#include<sstream>
#include <iostream>
#include<string>

TileMapComponent::TileMapComponent(GameObject* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder), 
	mTileWidth(16), mTileHeight(16), 
	mTilePerRow(7), mOffsetX(0.0f), mXBound(0.0f)
{
}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent::Update(float dt)
{
	//mOffsetX += dt * 400.0f;

	if (mOffsetX >= mXBound) {
		mOffsetX = mXBound;
	}
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
			destrect.w = static_cast<int>(mTileWidth * mOwner->GetScale());
			destrect.h = static_cast<int>(mTileHeight * mOwner->GetScale());
			destrect.x = static_cast<int>(mOwner->GetPosition().x + destrect.w * col - mOffsetX);
			destrect.y = static_cast<int>(mOwner->GetPosition().y + destrect.h * row);

			SDL_RenderCopyEx(renderer, mTexture, &srcrect,
				&destrect, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
		}
	}
}

void TileMapComponent::Init(const char* filePath)
{
	this->LoadTileData(filePath);
	this->SetTexture("MarioAssets/decorationsAndBlocks.png");
	mXBound = mTilesData[0].size() * mTileWidth * mOwner->GetScale() - mOwner->GetGame()->GetWindowWidth();
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
