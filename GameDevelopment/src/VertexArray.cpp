#include "include/VertexArray.h"
#include<GL/glew.h>

VertexArray::VertexArray(const float* vertices, const std::uint32_t numOfVertices,
	const std::uint32_t* indices, const std::uint32_t numOfIndices) :
	mNumOfVertices(numOfVertices), mNumOfIndices(numOfIndices)
{
	// VAO
	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);
	// VBO
	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, mNumOfVertices * 8 * sizeof(float), vertices, GL_STATIC_DRAW);
	// EBO
	glGenBuffers(1, &mIndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumOfIndices * sizeof(std::uint32_t), 
		indices, GL_STATIC_DRAW);
	// Config attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferId);
	glDeleteBuffers(1, &mIndexBufferId);
	glDeleteVertexArrays(1, &mVertexArrayId);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArrayId);
}

std::uint32_t VertexArray::GetNumOfVertices() const
{
	return mNumOfVertices;
}

std::uint32_t VertexArray::GetNumOfIndices() const
{
	return mNumOfIndices;
}
