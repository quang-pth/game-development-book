#pragma once

#include<vector>
#include<include/CustomMath.h>

class GameObject
{
public:
	enum State {
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
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	const Vector2& GetPosition() const { return mTransform; }
	void SetPosition(Vector2 position) { mTransform.x = position.x; mTransform.y = position.y; }
	class Game* GetGame() { return mGame; }
private:
	State mState;
	Vector2 mTransform; // Center point of the actor
	float mScale; // Scale factor
	float mRotation; // Rotation angle in radians
	std::vector<class Component*> mComponents;
	class Game* mGame;
};

