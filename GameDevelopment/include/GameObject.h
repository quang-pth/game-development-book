#pragma once

#include<vector>
#include<string>
#include"include/CustomMath.h"
#include"include/InputSystem.h"

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
	GameObject(class Game* game, const std::string& name = "");
	virtual ~GameObject();
	
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	void ProcessInput(const InputState& inputState);
	virtual void UpdateGameObject(float deltaTime);
	virtual void ProcessGameObjectInput(const InputState& inputState);
	// Add component in sorted order based-on its update order
	void AddComponent(class Component* component);	
	void RemoveComponent(class Component* component);
	State GetState() const;
	void SetState(State state);
	class TransformComponent* GetTransform() const;
	class Component* GetComponent(std::string name);
	std::vector<class Component*> GetComponents() const;
	Vector3 GetForward() const;
	Vector3 GetRight() const;
	class Game* GetGame() const;
private:
	void AddDefaultComponents();
	State mState;
	std::vector<class Component*> mComponents;
	class Game* mGame;
	class TransformComponent* mTransform;
};

