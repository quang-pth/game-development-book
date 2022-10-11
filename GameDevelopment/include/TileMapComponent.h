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
	void Init(const char* filePath);
private:
	void LoadTileData(const char* filePath);
	void SetTexture(const char* filePath);
	void CheckTileMapContent(const char* filePath);
	std::vector<std::vector<int>> mTilesData;
	unsigned int mTileWidth, mTileHeight, mTilePerRow;
};

