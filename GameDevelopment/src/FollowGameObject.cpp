#include "FollowGameObject.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/Mesh.h"
#include "include/TransformComponent.h"
#include "include/InputComponent.h"
#include "include/MeshComponent.h"
#include "include/FollowCamera.h"

FollowGameObject::FollowGameObject(Game* game, const std::string& name) :
	GameObject(game, name)
{
	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter9/RacingCar.gpmesh"));
	GameObject::GetTransform()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));

	mInputComponent = new InputComponent(this);
	mCamera = new FollowCamera(this);
	mCamera->SnapToIdeal();
}

FollowGameObject::~FollowGameObject()
{
}

void FollowGameObject::SetVisible(bool visible)
{
	mMeshComponent->SetVisible(visible);
}
