#include "include/GameObject.h"
#include "include/TransformComponent.h"
#include "include/Component.h"

TransformComponent::TransformComponent(GameObject* owner, int updateOrder, std::string name) :
	Component(owner, updateOrder, name),
	mRecomputeWorldTransform(true),
	mPosition(Vector3::Zero),
	mScale(1.0f), 
	mRotation(Quaternion::Identity)
{
	this->ComputeWorldTransform();
}

Matrix4 TransformComponent::GetWorldTransformMatrix() const
{
	return mWorldTransform;
}

void TransformComponent::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform) {
		mRecomputeWorldTransform = false;
		
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);
		
		for (auto component : mOwner->GetComponents()) {
			component->OnUpdateWorldTransform();
		}
	}
}
