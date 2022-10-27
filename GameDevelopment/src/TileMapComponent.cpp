#include "include/GameObject.h";
#include "include/TileMapComponent.h";
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
		Vector2 distance = mario->GetTransform()->GetPosition();
		Vector2 center = mOwner->GetGame()->GetCenterPoint();
	
		mOffset += mario->GetInputComponent()->GetVelocity() * deltaTime;
		
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
			destrect.x = static_cast<int>(mOwner->GetTransform()->GetPosition().x + destrect.w * col - mOffset.x);
			destrect.y = static_cast<int>(mOwner->GetTransform()->GetPosition().y + destrect.h * row);

			SDL_RenderCopyEx(renderer, mTexture, &srcrect,
				&destrect, -Math::ToDegrees(mOwner->GetTransform()->GetRotation()), nullptr, SDL_FLIP_NONE);
		}
	}
}

void TileMapComponent::Init(const char* filePath)
{
	this->LoadTileData(filePath);
	this->SetTexture("MarioAssets/decorationsAndBlocks.png");
	mXBound = mTilesData[0].size() * mTileWidth * mOwner->GetTransform()->GetScale() - mOwner->GetGame()->GetWindowWidth();
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
