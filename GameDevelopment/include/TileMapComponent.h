#pragma once

#include "include/SpriteComponent.h"
#include<vector>
#include <string>

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class GameObject* owner, int drawOrder = 100);
	~TileMapComponent();
	void Draw(SDL_Renderer* renderer) override;
	void LoadTileMap(const char* filePath);
private:
	void CheckTileMapContent();
	std::vector<std::vector<int>> mTilesData;
	float mTileWidth, mTileHeight;
	std::string mFilePath;
};

