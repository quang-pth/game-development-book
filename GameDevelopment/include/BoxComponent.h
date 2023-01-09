#pragma once

#include"include/Component.h"
#include"include/Collision.h"

class BoxComponent : public Component
{
public:
	BoxComponent(class GameObject* owner, int updateOrder = 200, const std::string& name = "BoxComponent");
	~BoxComponent() = default;
	virtual void OnUpdateWorldTransform() override;
	void SetShouldRotate(bool rotate) { mShouldRotate = rotate; }
	void SetObjectBox(const AABB& box) { mObjectBox = box; }
	const AABB& GetWorldBox() const { return mWorldBox; }
private:
	bool mShouldRotate;
	AABB mObjectBox;
	AABB mWorldBox;
};

