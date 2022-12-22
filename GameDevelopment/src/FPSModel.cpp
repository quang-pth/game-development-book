#include "include/FPSModel.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/MeshComponent.h"
#include "include/Mesh.h"

FPSModel::FPSModel(Game* game, const std::string& name) :
	GameObject(game, name)
{
	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter9/Rifle.gpmesh"));
}

FPSModel::~FPSModel()
{
}
