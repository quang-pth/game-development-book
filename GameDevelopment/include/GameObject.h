#pragma once

#include<vector>
#include<string>
#include<memory>
#include"CustomMath.h"

enum class State {
	EActive,
	EDeactive,
	EPaused,
	EDead,
};

class GameObject
{
public:
	std::string name;
public:
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
	virtual void SetState(State state);
	void Activate();
	void Deactivate();
	class Component* GetComponent(const std::string& name);
	Vector2 GetForward() const;
	class Game* GetGame() const;
	class TransformComponent *pTransform;
	bool IsActive() const;
protected:
	class Game *mGame;
protected:
	virtual void ActivateGameObject();
	virtual void DeactivateGameObject();
private:
	void AddDefaultComponents();
	State mState;
	std::vector<class Component*> mpComponents;
};

