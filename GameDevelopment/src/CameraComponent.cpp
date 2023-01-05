#include "include/CameraComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/AudioSystem.h"

CameraComponent::CameraComponent(GameObject* owner, int updateOrder, const std::string& name) :
	Component(owner, updateOrder, name),
	mYawAngle(0.0f), mPitchAngle(0.0f),
	mYawSpeed(0.0f), mPitchSpeed(0.0f),
	mRecomputeMatix(true), mViewMatrix(Matrix4::Identity)
{
}

void CameraComponent::Update(float deltaTime)
{
}

void CameraComponent::OnEnter()
{
	Component::SetIsActive(true);
}

void CameraComponent::OnExit()
{
	Component::SetIsActive(false);
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::SetViewMatrix(const Matrix4& viewMatrix)
{
	Game* game = mOwner->GetGame();
	game->GetRenderer()->SetViewMatrix(viewMatrix);
	game->GetAudioSystem()->SetListener(viewMatrix);
}
