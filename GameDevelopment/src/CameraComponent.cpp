#include "include/CameraComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/AudioSystem.h"

CameraComponent::CameraComponent(GameObject* owner, int updateOrder, const std::string& name) :
	Component(owner, updateOrder, name)
{
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
