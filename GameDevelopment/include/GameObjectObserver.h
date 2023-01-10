#pragma once

#include"include/Observer.h"
#include"include/GameObject.h"

class GameObjectObserver : public Observer
{
	friend class GameObjectSubject;
public:
	GameObjectObserver();
	~GameObjectObserver() = default;
	virtual void OnFireNotifyHandler(GameObject* gameObject, const Vector3& fireDirection) = 0;
	virtual Observer* GetNext() const override { return mNext; }
	virtual Observer* GetPrev() const override { return mPrev; }
	virtual void SetNext(Observer* next) override { mNext = dynamic_cast<GameObjectObserver*>(next); };
	virtual void SetPrev(Observer* prev) override { mPrev = dynamic_cast<GameObjectObserver*>(prev); };
protected:
	GameObjectObserver* mPrev;
	GameObjectObserver* mNext;
};

