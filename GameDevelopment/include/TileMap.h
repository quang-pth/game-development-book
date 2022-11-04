#pragma once

#include "include/GameObject.h"
#include "include/Enums.h"
#include<SDL2/SDL.h>
#include<vector>
#include <string>

class TileMap : public GameObject
{
public:
	enum class State {
		EMoveable,
		EUnMoveable,
	};
	TileMap(class Game* game, const std::string& name = "TileMap");
	void UpdateGameObject(float deltaTime) override;
	void Init(const char* srcTextureFilePath, const char* layoutFilePath);
	void SetState(EMovement state);
	void SetTileDimension(const Vector2& dimension);
	void SetTilePerRow(unsigned int numOfTiles);
	EMovement GetState() const;
	bool AtRightBounds();
	bool AtLeftBounds();
private:
	void LoadTileData(const char* filePath);
	void SetTexture(const char* filePath);
	SDL_Texture* mTexture;
	std::vector<class Tile*> mTiles;
	unsigned int mTileWidth, mTileHeight, mTilePerRow;
	Vector2 mOffset;
	float mXBound;
	EMovement mState;
};

