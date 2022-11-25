#pragma once

#include<SOIL/SOIL.h>
#include<string>

class Texture
{
public:
	Texture() = default;
	~Texture();
	bool Load(const std::string& filePath);
	void Unload();
	void SetActive();
	inline std::int32_t GetWidth() const { return mWidth; }
	inline std::int32_t GetHeight() const { return mHeight; }
	inline std::uint32_t GetTextureID() const { return mTextureID; }
private:
	std::int32_t mWidth, mHeight;
	std::uint32_t mTextureID;
};

