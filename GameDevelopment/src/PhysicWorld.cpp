#include "include/PhysicWorld.h"
#include "include/GameObject.h"
#include "include/BoxComponent.h"

PhysicWorld::PhysicWorld(Game* game) : 
	mGame(game), mBoxes()
{
}

PhysicWorld::~PhysicWorld()
{
}

void PhysicWorld::AddBox(BoxComponent* box)
{
	if (box != nullptr) {
		mBoxes.emplace_back(box);
	}
}

void PhysicWorld::Remove(BoxComponent* box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end()) {
		mBoxes.erase(iter);
	}
}

void PhysicWorld::TestPairWise(std::function<void(GameObject*, GameObject*)> function)
{
	// Time complexity in total: O(n^2)
	for (size_t i = 0; i < mBoxes.size() - 1; i++) {
		for (size_t j = i + 1; j < mBoxes.size(); j++) {
			if (Collision::Intersect(mBoxes[i]->GetWorldBox(), mBoxes[j]->GetWorldBox())) {
				function(mBoxes[i]->GetOwner(), mBoxes[j]->GetOwner());
			}
		}
	}
}

void PhysicWorld::TestSweepAndPrune(std::function<void(GameObject*, GameObject*)> function)
{
	// Time complexity in total: O(nlogn)
	std::sort(mBoxes.begin(), mBoxes.end(), [](BoxComponent* a, BoxComponent* b) {
		return a->GetWorldBox().mMin.x < b->GetWorldBox().mMax.x;
	});

	for (size_t i = 0; i < mBoxes.size() - 1; i++) {
		BoxComponent* a = mBoxes[i];
		float maxX = a->GetWorldBox().mMax.x;

		for (size_t j = i + 1; j < mBoxes.size(); j++) {
			BoxComponent* b = mBoxes[j];
			
			if (b->GetWorldBox().mMin.x > maxX) break;

			if (Collision::Intersect(a->GetWorldBox(), b->GetWorldBox())) {
				function(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

bool PhysicWorld::SegmentCast(const LineSegment& l, CollisionInfo& outCollision)
{
	float minT = Math::Infinity;
	Vector3 normal;
	float t;
	bool collided = false;

	for (BoxComponent* box : mBoxes) {
		if (Collision::Intersect(l, box->GetWorldBox(), t, normal)) {
			if (t < minT) {
				minT = t;
				outCollision.mPoint = l.PointOnSegment(t);
				outCollision.mNormal = normal;
				outCollision.mBox = box;
				outCollision.mOwner = box->GetOwner();
				collided = true;
			}
		}
	}

	return collided;
}
