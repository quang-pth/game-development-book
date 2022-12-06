#pragma once

#include"include/Component.h"

class MeshComponent : public Component
{
public:
	MeshComponent(class GameObject* owner);
	~MeshComponent();
	virtual void Draw(class Shader* shader);
	virtual void SetMesh(class Mesh* mesh);
	class Mesh* GetMesh() const;
	void SetTextureIndex(size_t idx);
protected:
	class Mesh* mMesh;
	size_t mTextureIdx;
};

