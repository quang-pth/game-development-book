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

void OrbitGameObject::ProcessGameObjectInput(const InputState& inputState)
{
	GameObject::ProcessGameObjectInput(inputState);
	
	RelativeMouse mouseInfo = GameObject::GetGame()->GetInputSystem()->GetRelativeMouse();
	float yawSpeed = 0.0f;
	float pitchSpeed = 0.0f;
	
	if (mouseInfo.Buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		static int maxMouseSpeed = 500;
		static float maxOrbitSpeed = Math::Pi * 8;

		if (mouseInfo.Position.x != 0)
		{
			// Convert to ~[-1.0, 1.0]
			yawSpeed = static_cast<float>(mouseInfo.Position.x) / maxMouseSpeed;
			// Multiply by rotation/sec
			yawSpeed *= maxOrbitSpeed;
		}
		
		if (mouseInfo.Position.y != 0)
		{
			pitchSpeed = static_cast<float>(mouseInfo.Position.y) / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
	}
	
	mCamera->SetYawSpeed(-yawSpeed);
	mCamera->SetPitchSpeed(pitchSpeed);
}

void OrbitGameObject::SetVisible(bool visible)
{
	mMeshComponent->SetVisible(visible);
}
