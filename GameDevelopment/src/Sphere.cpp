#include "include/Sphere.h"
#include "include/Game.h"
#include "include/Mesh.h"
#include "include/Renderer.h"
#include "include/MeshComponent.h"
#include "include/TransformComponent.h"
#include "include/AudioComponent.h"
#include "include/SoundEvent.h"

Sphere::Sphere(Game* game, const std::string& name) : 
	GameObject(game, name)
{
	GameObject::GetTransform()->SetPosition(Vector3(100.0f, 0.0f, 0.0f));
	
	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter6/Sphere.gpmesh"));

	mAudioComponent = new AudioComponent(this);
	mGrassEvent = mAudioComponent->PlayEvent("event:/FireLoop");

	game->GetInputSystem()->AddInputObserver(this);
}

Sphere::~Sphere()
{
	GameObject::GetGame()->GetInputSystem()->RemoveInputObserver(this);
}

void Sphere::UpdateGameObject(float deltaTime)
{
	float scale = 1000.0f;
	float time = SDL_GetTicks() / scale;
	Vector3 position = GameObject::GetTransform()->GetPosition();
	GameObject::GetTransform()->SetPosition(Vector3(position.x + std::sin(time), 0.0f, 0.0f));
}

void Sphere::OnNotify(ControllerState* controller, InputObserver::Event inputEvent)
{
}
