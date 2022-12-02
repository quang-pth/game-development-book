#include "include/MeshComponent.h"
#include "include/TransformComponent.h"
#include "include/GameObject.h"
#include "include/Shader.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/Mesh.h"
#include "include/Texture.h"
#include "include/VertexArray.h"

MeshComponent::MeshComponent(GameObject* owner) : 
	Component(owner),
	mMesh(nullptr), mTextureIdx(0)
{
	mOwner->GetGame()->GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMesh(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mMesh) {
		shader->SetActive();
		shader->SetMatrixUniform("uWorldTransform", 
			mOwner->GetTransform()->GetWorldTransformMatrix());
		shader->SetFloatUniform("uSpecularPower", mMesh->GetSpecularPower());

		Texture* texture = mMesh->GetTexture(mTextureIdx);
		if (texture) {
			texture->SetActive();
		}
		VertexArray* vertexArray = mMesh->GetVetexArray();
		vertexArray->SetActive();
		glDrawElements(GL_TRIANGLES, vertexArray->GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void MeshComponent::SetMesh(Mesh* mesh)
{
	mMesh = mesh;
}

void MeshComponent::SetTextureIndex(size_t idx)
{
	mTextureIdx = idx;
}
