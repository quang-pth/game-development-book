#include "include/BoxComponent.h"
#include "include/Game.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"

BoxComponent::BoxComponent(GameObject* owner, int updateOrder, const std::string& name) :
	Component(owner, updateOrder, name),
	mObjectBox(), mWorldBox(), mShouldRotate(true)
{

}

void BoxComponent::OnUpdateWorldTransform()
{
	mWorldBox = mObjectBox;

	mWorldBox.mMin *= mOwner->GetTransform()->GetScale();
	mWorldBox.mMax *= mOwner->GetTransform()->GetScale();
	
	if (mShouldRotate) {
		mWorldBox.Rotate(mOwner->GetTransform()->GetRotation());
	}

	mWorldBox.mMin += mOwner->GetTransform()->GetPosition();
	mWorldBox.mMax += mOwner->GetTransform()->GetPosition();
}
