#include "include/OrbitGameObject.h"

#include "include/Game.h"
#include "include/Renderer.h"
#include "include/InputSystem.h"
#include "include/Mesh.h"
#include "include/TransformComponent.h"
#include "include/MeshComponent.h"
#include "include/OrbitCamera.h"
#include <iostream>

OrbitGameObject::OrbitGameObject(Game* game, const std::string& name) :
	GameObject(game, name)
{
	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter9/RacingCar.gpmesh"));
	GameObject::GetTransform()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));

	mCamera = new OrbitCamera(this);
}

OrbitGameObject::~OrbitGameObject()
{
}

void OrbitGameObject::SetVisible(bool visible)
{
	mMeshComponent->SetVisible(visible);
}
