#include "include/GameObject.h"
#include "include/SpriteComponent.h"
#include "include/TransformComponent.h"
#include "include/CustomMath.h"
#include "include/Game.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include <iostream>

SpriteComponent::SpriteComponent(GameObject* owner, int drawOrder) : 
	Component(owner), mTexture(nullptr),
	mDrawOrder(drawOrder), mTextureWidth(32), mTextureHeight(32)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mOwner->GetState() == GameObject::State::EDeactive) return;

	Matrix4 scaleMatrix = Matrix4::CreateScale(
		static_cast<float>(mTextureWidth), 
		static_cast<float>(mTextureHeight),
		1.0f);
	Matrix4 worldTransform = scaleMatrix * mOwner->GetTransform()->GetWorldTransformMatrix();

	shader->SetMatrixUniform("uWorldTransform", worldTransform);
	mTexture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
}
