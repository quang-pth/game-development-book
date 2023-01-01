#include "include/OrbitGameObject.h"

#include "include/Game.h"
#include "include/Renderer.h"
#include "include/InputSystem.h"
#include "include/Mesh.h"
#include "include/TransformComponent.h"
#include "include/MeshComponent.h"
#include "include/OrbitCamera.h"

OrbitGameObject::OrbitGameObject(Game* game, const std::string& name) :
	GameObject(game, name)
{
	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter9/RacingCar.gpmesh"));

	mCamera = new OrbitCamera(this);
}

OrbitGameObject::~OrbitGameObject()
{
}

void OrbitGameObject::ProcessGameObjectInput(const InputState& inputState)
{
	GameObject::ProcessGameObjectInput(inputState);

	RelativeMouseInfo mouseInfo = GameObject::GetGame()->GetInputSystem()->GetRelativeMouseInfo();
	if (mouseInfo.Buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		// Assume mouse movement is usually between -500 and +500
		const int maxMouseSpeed = 500;
		// Rotation/sec at maximum speed
		const float maxOrbitSpeed = Math::Pi * 8;
		float yawSpeed = 0.0f;
		if (mouseInfo.Position.x != 0)
		{
			// Convert to ~[-1.0, 1.0]
			yawSpeed = static_cast<float>(mouseInfo.Position.x) / maxMouseSpeed;
			// Multiply by rotation/sec
			yawSpeed *= maxOrbitSpeed;
		}
		mCamera->SetYawSpeed(-yawSpeed);

		// Compute pitch
		float pitchSpeed = 0.0f;
		if (mouseInfo.Position.y != 0)
		{
			// Convert to ~[-1.0, 1.0]
			pitchSpeed = static_cast<float>(mouseInfo.Position.y) / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
		mCamera->SetPitchSpeed(pitchSpeed);
	}
}

void OrbitGameObject::SetVisible(bool visible)
{
	mMeshComponent->SetVisible(visible);
}
