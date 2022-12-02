#include "include/Cube.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/MeshComponent.h"
#include "include/Mesh.h"
#include "include/TransformComponent.h"

Cube::Cube(Game* game, const std::string& name) :
	GameObject(game, name)
{
	GameObject::GetTransform()->SetPosition(Vector3(25.0f, 10.0f, 0.0f));
	GameObject::GetTransform()->SetScale(10.0f);
	mMesh = new MeshComponent(this);
	mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter6/Cube.gpmesh"));
}

Cube::~Cube()
{
}

void Cube::UpdateGameObject(float deltaTime)
{
	GameObject::GetTransform()->SetRotation(
		Quaternion::Concatenate(
			Quaternion(Vector3::UnitY, deltaTime), 
			GameObject::GetTransform()->GetRotation())
	);
}
