#pragma once

#include"include/Collision.h"
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
	class Shader* GetShader() const { return mShader; }
	std::string GetShaderName() const { return mShaderName; }
	float GetRadius() const { return mRadius; }
	float GetSpecularPower() const { return mSpecPower; }
	const AABB& GetBox() const { return mBox; }
private:
	AABB mBox;
	class std::vector<class Texture*> mTextures;
	class VertexArray* mVertexArray;
	std::string mShaderName;
	class Shader* mShader;
	float mRadius, mSpecPower;
};

