#pragma once

#include<vector>
#include<string>
#include<memory>
#include"CustomMath.h"

class GameObject
{
public:
	enum class State {
		EActive,
		EDeactive,
		EPaused,
		EDead,
	};
	std::string name;

	GameObject();
	GameObject(class Game* game, std::string name = "");
	virtual ~GameObject();
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	void ProcessInput(const uint8_t* keyState);
	virtual void UpdateGameObject(float deltaTime);
	virtual void ProcessGameObjectInput(const uint8_t* keyState);
	// Add component in sorted order based-on its update order
	void AddComponent(class Component* component);	
	void RemoveComponent(class Component* component);
	virtual void RemoveGameObjectComponent(class Component* component);
	State GetState() const;
	void SetState(State state);
	class Component* GetComponent(const std::string& name);
	Vector2 GetForward() const;
	class Game* GetGame() const;
	class TransformComponent *pTransform;
private:
	void AddDefaultComponents();
	State mState;
	std::vector<class Component*> mpComponents;
protected:
	class Game *mGame;
};

