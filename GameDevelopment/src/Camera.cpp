#include "include/Camera.h"
#include "include/Game.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"

Camera::Camera(Game* game, const std::string& name) :
	GameObject(game, name), 
	mViewMatrix(Matrix4::Identity), 
	mTarget(Vector3::UnitX), mWorldUp(Vector3::UnitZ),
	mInputComponent(new InputComponent(this)),
	mRecomputeViewMatrix(true)
{
	GameObject::GetTransform()->SetPosition(Vector3::Zero);
	this->ComputeViewMatrix();
}

Camera::~Camera()
{
}

void Camera::UpdateGameObject(float deltaTime)
{
	this->ComputeViewMatrix();
}

void Camera::ComputeViewMatrix()
{
	const Vector3& position = GameObject::GetTransform()->GetPosition();
	mTarget = position + GameObject::GetForward();

	mViewMatrix = Matrix4::CreateLookAt(
		position,
		mTarget,
		mWorldUp
	);
}
