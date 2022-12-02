#pragma once

#include<string>
#include<vector>

class Mesh
{
public:
	Mesh();
	~Mesh();
	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();
	class VertexArray* GetVetexArray() const { return mVertexArray; }
	class Texture* GetTexture(size_t index) const;
	std::string GetShaderName() const { return mShaderName; }
	float GetRadius() const { return mRadius; }
	float GetSpecularPower() const { return mSpecPower; }
private:
	class std::vector<class Texture*> mTextures;
	class VertexArray* mVertexArray;
	std::string mShaderName;
	float mRadius, mSpecPower;
};

