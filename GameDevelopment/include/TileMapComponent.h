#pragma once

#include "include/SpriteComponent.h"
#include "include/Enums.h"
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
	void SetState(EMovement state);
	EMovement GetState() const;
	bool AtRightBounds();
	bool AtLeftBounds();
private:
	void LoadTileData(const char* filePath);
	void SetTexture(const char* filePath);
	std::vector<class TileDataComponent*> mTilesData;
	unsigned int mTileWidth, mTileHeight, mTilePerRow;
	Vector2 mOffset;
	float mXBound;
	EMovement mState;
};

