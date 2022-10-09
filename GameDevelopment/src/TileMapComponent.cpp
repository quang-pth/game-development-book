#include "include/TileMapComponent.h";
#include<fstream>
#include<sstream>
#include <iostream>
#include<string>

TileMapComponent::TileMapComponent(GameObject* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder), mTileWidth(0.0f), mTileHeight(0.0f)
{
}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{

}

void TileMapComponent::LoadTileMap(const char* filePath)
{
	mFilePath = filePath;
	// TODO: Load CSV files
	std::ifstream fstream(filePath);
	std::string line;

	unsigned int tileCode;

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

	CheckTileMapContent();
}

void TileMapComponent::CheckTileMapContent()
{
	std::cout << "================================" << std::endl;
	std::cout << "Tilemap filepath: " << mFilePath << std::endl;
	std::cout << "================================" << std::endl;
	for (unsigned int row = 0; row < mTilesData.size(); row++) {
		for (unsigned int col = 0; col < mTilesData[row].size(); col++) {
			std::cout << mTilesData[row][col] << " ";
		}
		std::cout << std::endl;
	}
}
