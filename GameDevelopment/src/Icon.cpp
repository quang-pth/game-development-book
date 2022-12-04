#include "include/Icon.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/SpriteComponent.h"

Icon::Icon(Game* game, const std::string& name) :
	GameObject(game, name),
	mTexture()
{
	spriteComponent = new SpriteComponent(this);
}

Icon::~Icon()
{
}

void Icon::SetTexture(Texture* texture)
{
	spriteComponent->SetTexture(texture);
}
