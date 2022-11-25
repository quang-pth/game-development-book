#pragma once

#include<SDL2/SDL.h>
#include<iostream>

class VertexArray
{
public:
	VertexArray() = default;
	VertexArray(const float* vertices, const std::uint32_t numOfVertices, const std::uint32_t* indices,
		const std::uint32_t numOfIndices);
	~VertexArray();
	void SetActive();
	std::uint32_t GetNumOfVertices() const;
	std::uint32_t GetNumOfIndices() const;
private:
	std::uint32_t mNumOfVertices, mNumOfIndices;
	std::uint32_t mVertexBufferId;
	std::uint32_t mIndexBufferId;
	std::uint32_t mVertexArrayId;
};

