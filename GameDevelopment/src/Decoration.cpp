#include "include/Decoration.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/MeshComponent.h"
#include "include/BoxComponent.h"
#include "include/Mesh.h"

Decoration::Decoration(Game* game, const std::string& name) :
	GameObject(game, name)
{
	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter6/Plane.gpmesh"));

	mBoxComponent = new BoxComponent(this);
	mBoxComponent->SetObjectBox(mMeshComponent->GetMesh()->GetBox());
}

Decoration::~Decoration()
{
}
