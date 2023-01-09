#include "include/Level.h"
#include "include/Game.h"
#include "include/Decoration.h"
#include "include/Renderer.h"
#include "include/Mesh.h"
#include "include/MeshComponent.h"
#include "include/TransformComponent.h"
#include "include/CustomMath.h"

Level::Level(Game* game, const std::string& name) :
	GameObject(game, name),
	mDecorations()
{
	this->Init();
}

Level::~Level()
{
}

void Level::Init()
{
	Vector3 positions[] = {
		Vector3(0.0f, 0.0f, -100.0f), // Ground
		Vector3(1000.0f, 0.0f, 50.0f), // Forward Wall
		Vector3(-1000.0f, 0.0f, 50.0f), // Back Wall
		Vector3(0.0f, -1000.0f, 50.0f), // Left Wall
		Vector3(0.0f, 1000.0f, 50.0f), // Right Wall
	};
	Quaternion rotations[] = {
		Quaternion::Identity, // Ground
		Quaternion(Vector3::UnitY, Math::ToRadians(90.0f)), // Forward Wall
		Quaternion(Vector3::UnitY, Math::ToRadians(90.0f)), // Back Wall
		Quaternion(Vector3::UnitX, Math::ToRadians(90.0f)), // Left Wall
		Quaternion(Vector3::UnitX, Math::ToRadians(90.0f)), // Right Wall
	};
	for (std::uint8_t i = 0; i < sizeof(positions) / sizeof(Vector3); i++) {
		Decoration* decoration = new Decoration(GameObject::GetGame());
		decoration->GetTransform()->SetPosition(positions[i]);
		decoration->GetTransform()->SetScale(20.0f);
		decoration->GetTransform()->SetRotation(rotations[i]);
		
		mDecorations.emplace_back(decoration);
	}
}
