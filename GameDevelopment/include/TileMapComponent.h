#pragma once

#include "include/SpriteComponent.h"
#include<vector>
#include <string>

class TileMapComponent : public SpriteComponent
{
public:
	enum class State {
		EMoveable,
		EUnMoveable,
	};
	TileMapComponent(class GameObject* owner, int drawOrder = 100, std::string name = "TileMapComponent");
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void Init(const char* filePath);
	void SetState(State state);
	State GetState() const;
private:
	void LoadTileData(const char* filePath);
	void SetTexture(const char* filePath);
	void CheckTileMapContent(const char* filePath);
	std::vector<std::vector<int>> mTilesData;
	unsigned int mTileWidth, mTileHeight, mTilePerRow;
	Vector2 mOffset;
	float mXBound;
	State mState;
};

