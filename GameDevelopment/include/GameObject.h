#pragma once

#include<vector>
#include<string>
#include"CustomMath.h"

class GameObject
{
public:
	enum class State {
		EActive,
		EPaused,
		EDead,
	};
	std::string mName;

	GameObject(class Game* game, std::string name = "");
	virtual ~GameObject();
	
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateGameObject(float deltaTime);
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	State GetState() const;
	class TransformComponent* GetTransform() const;
	class Component* GetComponent(std::string name);
	Vector2 GetForward() const;
	class Game* GetGame() const;
private:
	State mState;
	std::vector<class Component*> mComponents;
	class Game* mGame;
	class TransformComponent* mTransform;

	void AddDefaultComponents();
};

