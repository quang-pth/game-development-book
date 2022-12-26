#pragma once

#include"include/Component.h"
#include"include/CustomMath.h"

class CameraComponent : public Component
{
public:
	CameraComponent(class GameObject* owner, int updateOrder = 100, const std::string& name = "CameraComponent");
	virtual void Update(float deltaTime) override;
	virtual ~CameraComponent();
	virtual const Matrix4& GetViewMatrix() const = 0;
protected:
	void SetViewMatrix(const Matrix4& viewMatrix);
};

