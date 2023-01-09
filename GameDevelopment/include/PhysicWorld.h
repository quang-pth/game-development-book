#pragma once

#include"include/Collision.h"
#include"include/CustomMath.h"
#include<vector>
#include<functional>

class Game;
class GameObject;
class BoxComponent;

struct CollisionInfo {
	Vector3 mPoint;
	Vector3 mNormal;
	BoxComponent* mBox;
	GameObject* mOwner;
};

class PhysicWorld
{
public:
	PhysicWorld(Game* game);
	~PhysicWorld();
	void AddBox(BoxComponent* box);
	void Remove(BoxComponent* box);
	void TestPairWise(std::function<void(GameObject*, GameObject*)> function);
	void TestSweepAndPrune(std::function<void(GameObject*, GameObject*)> function);
	bool SegmentCast(const LineSegment& l, CollisionInfo& outCollision);
	Game* GetGame() const { return mGame; }
private:
	Game* mGame;
	std::vector<BoxComponent*> mBoxes;
};

