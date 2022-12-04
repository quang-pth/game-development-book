#include "include/Decoration.h"
#include "include/Game.h"
#include "include/MeshComponent.h"

Decoration::Decoration(Game* game, const std::string& name) :
	GameObject(game, name)
{
	mMeshComponent = new MeshComponent(this);
}

Decoration::~Decoration()
{
}
