#pragma once

#include<include/CustomMath.h>
#include<include/TransformComponent.h>
#include<vector>

class GameObject
{
public:
	enum class State {
		EActive,
		EPaused,
		EDead,
	};
	GameObject(class Game* game);
	virtual ~GameObject();
	
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateGameObject(float deltaTime);
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	State GetState() const { return mState; }
	TransformComponent* GetTransform() const { return mTransform; }
	class Component* GetComponent(std::string name);
	Vector2 GetForward() const { return Vector2(Math::Cos(mTransform->mRotation), -Math::Sin(mTransform->mRotation)); }
	class Game* GetGame() { return mGame; }
private:
	State mState;
	std::vector<class Component*> mComponents;
	class Game* mGame;
	TransformComponent* mTransform;

	void AddTransformComponent();
};

